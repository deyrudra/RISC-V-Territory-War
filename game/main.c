#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "inputhandler.h"
#include "loadAssets.c"
#include "movementhandler.h"
#include "objecthandler.h"

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320
#define NUM_CHARACTERS_PER_TEAM 1  // Chnage to 3

// Global Variables
// --------------------------------------------------------------------

// Buffer Register and Pixel Buffer Start
volatile int* buffer_register = (int*)0xFF203020;
volatile int pixel_buffer_start;

// Front and Back Buffers of size SCREEN_HEIGHT rows, SCREEN_WIDTH columns
// (SCREEN_WIDTHxSCREEN_HEIGHT)
short int Buffer1[480][640];
short int Buffer2[480][640];

// global pointers to memory mapped IO
volatile int* ps2_ptr = (int*)PS2_BASE;

struct GameState {
  char team_turn;
  int character_turn_team_a;
  int character_turn_team_b;
  bool game_running;
};

// Game logic objects
struct Character* team_a[NUM_CHARACTERS_PER_TEAM];
struct Character* team_b[NUM_CHARACTERS_PER_TEAM];
struct GameState* game_state_ptr;

// Keyboard Input Polling Bytes
uint8_t byte1 = 0, byte2 = 0, byte3 = 0;
int ps2_data, RVALID;

// Global Game Objects
GameObject* leftMovementObj;
GameObject* rightMovementObj;
GameObject* backgroundObj;
GameObject* mainMenuTitleObj;
GameObject* platformObj;
GameObject* skyObj;
GameObject* moveOrStayBannerObj;

// Global Game Controls
const char* gameControls[] = {
    "Move_Left", // 0
    "Move_Right", // 1
    "Move_Jump", // 2
    "Move_Left_Stop", // 3
    "Move_Right_Stop", // 4
    "Move_Jump_Stop", // 5

    // ...
};

//---------------------------------------------------------------------------------------

// Function Declarations
// ----------------------------------------------------------------

// Screen Functions
void clear_screen();
void wait_for_vsync();
void draw_solid_sky();

// Drawing Functions
void plot_pixel(int x, int y, short int line_color);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void draw_6x6_box(int x0, int y0, short int box_color);

// Helper Functions
void swap(int* num1, int* num2);

// Game Logic Functions
void initializeGame();
int getCharacterIndexForNextTurn(
    struct Character* team_array[NUM_CHARACTERS_PER_TEAM],
    int current_character_turn_index);
char checkWinCondition();

//----------------------------------------------------------------------------------------

int main(void) {
  /* set front pixel buffer to Buffer 1 */
  *(buffer_register + 1) =
      (int)&Buffer1;  // first store the address in the  back buffer
  /* now, swap the front/back buffers, to set the front buffer location */
  wait_for_vsync();
  // after this functin the back_buffer register content,
  // has swapped with the front_buffer register content

  /* initialize a pointer to the pixel buffer, used by drawing functions */
  pixel_buffer_start = *buffer_register;
  clear_screen();  // pixel_buffer_start points to the pixel buffer

  /* set back pixel buffer to Buffer 2 */
  *(buffer_register + 1) = (int)&Buffer2;
  // *(buffer_register + 1) = (int) &Buffer1; // Making it one buffer only.
  pixel_buffer_start = *(buffer_register + 1);  // we draw on the back buffer
  clear_screen();  // pixel_buffer_start points to the pixel buffer

  // Setting Some Initial Object Data.
  // leftMovementObj = (GameObject *)malloc(sizeof(GameObject));
  // int leftmovementPrevData[LEFTMOVEMENT_HEIGHT][LEFTMOVEMENT_WIDTH];
  // leftMovementObj->x = 80;
  // leftMovementObj->y = 80;
  // leftMovementObj->asset = &leftmovement;
  // leftMovementObj->collidable = 0;
  // leftMovementObj->height = LEFTMOVEMENT_HEIGHT;
  // leftMovementObj->width = LEFTMOVEMENT_WIDTH;
  // leftMovementObj->prevPixelData = &leftmovementPrevData;

  // rightMovementObj = (GameObject *)malloc(sizeof(GameObject));
  // int rightmovementPrevData[RIGHTMOVEMENT_HEIGHT][RIGHTMOVEMENT_WIDTH];
  // rightMovementObj->x = 20;
  // rightMovementObj->y = 50;
  // rightMovementObj->asset = &rightmovement;
  // rightMovementObj->collidable = 0;
  // rightMovementObj->height = RIGHTMOVEMENT_HEIGHT;
  // rightMovementObj->width = RIGHTMOVEMENT_WIDTH;
  // rightMovementObj->prevPixelData = &rightmovementPrevData;

  initializeGame();

  // 40x40 brick wall,
  backgroundObj = (GameObject*)malloc(sizeof(GameObject));
  int backgroundPrevData[BACKGROUND_HEIGHT][BACKGROUND_WIDTH];
  backgroundObj->asset = &background;
  backgroundObj->collidable = 0;
  backgroundObj->height = BACKGROUND_HEIGHT;
  backgroundObj->width = BACKGROUND_WIDTH;
  backgroundObj->prevPixelData = &backgroundPrevData;

  // 40x40 sky block
  skyObj = (GameObject*)malloc(sizeof(GameObject));
  int skyPrevData[SKY_HEIGHT][SKY_WIDTH];
  skyObj->asset = &sky;
  skyObj->collidable = 0;
  skyObj->height = SKY_HEIGHT;
  skyObj->width = SKY_WIDTH;
  skyObj->prevPixelData = &skyPrevData;

  // 320 x 40 move or stay banner
  moveOrStayBannerObj = (GameObject*)malloc(sizeof(GameObject));
  int moveOrStayBannerPrevData[BANNER_HEIGHT][BANNER_WIDTH];
  moveOrStayBannerObj->asset = &moveorstaybanner;
  moveOrStayBannerObj->x = &(int){0};  // casting to addr since x and y as ptrs
  moveOrStayBannerObj->y = &(int){SCREEN_HEIGHT - BANNER_HEIGHT};   
  moveOrStayBannerObj->collidable = 0;
  moveOrStayBannerObj->height = BANNER_HEIGHT;
  moveOrStayBannerObj->width = BANNER_WIDTH;
  moveOrStayBannerObj->prevPixelData = &moveOrStayBannerPrevData;

  // game title screen
  mainMenuTitleObj = (GameObject*)malloc(sizeof(GameObject));
  int mainMenuTitlePrevData[MAIN_MENU_TITLE_HEIGHT][MAIN_MENU_TITLE_WIDTH];
  mainMenuTitleObj->x = &(int){SCREEN_WIDTH - MAIN_MENU_TITLE_WIDTH -
                               40};  // casting to addr since x and y as ptrs
  mainMenuTitleObj->y = &(int){10};
  mainMenuTitleObj->asset = &main_menu_title;
  mainMenuTitleObj->collidable = 0;
  mainMenuTitleObj->height = MAIN_MENU_TITLE_HEIGHT;
  mainMenuTitleObj->width = MAIN_MENU_TITLE_WIDTH;
  mainMenuTitleObj->prevPixelData =
      &mainMenuTitlePrevData;  // prev data for keeping track of background

  // initialize platform
  int platformPrev[PLATFORM_HEIGHT][PLATFORM_WIDTH];
  platformObj = (GameObject*)malloc(sizeof(GameObject));
  int platformPrevData[PLATFORM_HEIGHT][PLATFORM_WIDTH];
  platformObj->x =
      &(int){SCREEN_WIDTH / 2};  // casting to addr since x and y as ptrs
  platformObj->y = &(int){SCREEN_HEIGHT - 90};
  platformObj->asset = &platform;
  platformObj->collidable = 1;
  platformObj->height = PLATFORM_HEIGHT;
  platformObj->width = PLATFORM_WIDTH;
  platformObj->prevPixelData = &platformPrevData;  // prev data for keeping track of background

  // pass in assets and prev backgrounds


  //----- RENDER IN START SCREEN AND INITIALIZE GAME

  // Rendering Background
  for (int ypos = 0; ypos < SCREEN_HEIGHT; ypos += 40) {
    for (int xpos = 0; xpos < SCREEN_WIDTH; xpos += 40) {
      backgroundObj->x = &xpos;
      backgroundObj->y = &ypos;
      renderIn(backgroundObj);
    }
  }

  // Rendering Main Menu Title
  renderIn(mainMenuTitleObj);

  //--

  // Create characters
  Character player_a0, player_b0;

  int leftmovementPrev[LEFTMOVEMENT_HEIGHT]
                      [LEFTMOVEMENT_WIDTH];  // set to -1 when we wanna render
                                             // something
  int rightmovementPrev[RIGHTMOVEMENT_HEIGHT][RIGHTMOVEMENT_WIDTH];
  int backgroundPrev[BACKGROUND_HEIGHT][BACKGROUND_WIDTH];
  int skyPrev[SKY_HEIGHT][SKY_WIDTH];
  int main_menu_titlePrev[MAIN_MENU_TITLE_HEIGHT][MAIN_MENU_TITLE_WIDTH];
  int idlePrev[IDLE_HEIGHT][IDLE_WIDTH];
  int leftbootPrev[LEFTBOOT_HEIGHT][LEFTBOOT_WIDTH];
  int rightbootPrev[LEFTBOOT_HEIGHT][LEFTBOOT_WIDTH];
  int jumpPrev[JUMP_HEIGHT][JUMP_WIDTH];
  int deadPrev[DEAD_HEIGHT][DEAD_WIDTH];
  initializeCharacter(&player_a0, 20 + PLAYER_WIDTH,
                      SCREEN_HEIGHT - 40 - PLAYER_HEIGHT, &idle, &leftmovement,
                      &rightmovement, &jump, &idlePrev, &leftmovementPrev,
                      &rightmovementPrev, &jumpPrev);

  int leftmovementPrev2[LEFTMOVEMENT_HEIGHT]
                       [LEFTMOVEMENT_WIDTH];  // set to -1 when we wanna render
                                              // something
  int rightmovementPrev2[RIGHTMOVEMENT_HEIGHT][RIGHTMOVEMENT_WIDTH];
  int backgroundPrev2[BACKGROUND_HEIGHT][BACKGROUND_WIDTH];
  int main_menu_titlePrev2[MAIN_MENU_TITLE_HEIGHT][MAIN_MENU_TITLE_WIDTH];
  int idlePrev2[IDLE_HEIGHT][IDLE_WIDTH];
  int leftbootPrev2[LEFTBOOT_HEIGHT][LEFTBOOT_WIDTH];
  int rightbootPrev2[LEFTBOOT_HEIGHT][LEFTBOOT_WIDTH];
  int jumpPrev2[JUMP_HEIGHT][JUMP_WIDTH];
  int deadPrev2[DEAD_HEIGHT][DEAD_WIDTH];
  initializeCharacter(&player_b0, SCREEN_WIDTH - 20 - PLAYER_WIDTH,
                      SCREEN_HEIGHT - 40 - PLAYER_HEIGHT, &idle, &leftmovement,
                      &rightmovement, &jump, &idlePrev2, &leftmovementPrev2,
                      &rightmovementPrev2, &jumpPrev2);

  initializeGame();

  // Add characters to teams
  team_a[0] = &player_a0;
  team_b[0] = &player_b0;

  // Wait for user to hit enter to start game
  poll_start_input();
  game_state_ptr->game_running = true;

  // Render out title screen
  renderOut(mainMenuTitleObj);


  // Render in initial game map, players, and objects in layers

  // Layer 1 bakcground
  for (int ypos = 0; ypos < SCREEN_HEIGHT - 40; ypos += 40) {
    for (int xpos = 0; xpos < SCREEN_WIDTH; xpos += 40) {
      skyObj->x = &xpos;
      skyObj->y = &ypos;
      renderIn(skyObj);
    }
  }

  // Layer 2 map objects and banners
  renderIn(platformObj);
  renderIn(moveOrStayBannerObj);

  // Layer 3 characters
  drawCharacter(&player_a0);
  drawCharacter(&player_b0);

  int count = 0;
  // Game Logic Loop
  // ----------------------------------------------------------------------
  while (game_state_ptr->game_running) {
    bool end_turn = false;

    // Team A's Turn
    if (game_state_ptr->team_turn == 'a') {
      printf("Team A's Turn\n");
      printf("Character %d's turn: Press 1 to move or 2 to stay\n",
             game_state_ptr->character_turn_team_a);

      //-----------------------Stage 1 of turn, draw bottom bar here
      while (1) {
        ps2_data = *ps2_ptr;
        RVALID = ps2_data & 0x8000;

        if (RVALID) {
          byte1 = byte2;
          byte2 = byte3;
          byte3 = ps2_data & 0xFF;
        }

        if (byte3 == 0x16) {  // User pressed 1
          if (byte2 == 0xF0) {
            printf("You selected move\n");
            break;
          }
        } else if (byte3 == 0x1E) {  // User pressed 2
          if (byte2 == 0xF0) {
            printf("You selected stay\n");
            end_turn = true;
            break;
          }
        }
      }
      byte1 = byte2 = byte3 = 0;

      if (!end_turn) {
        // Input handler logic for moving controls
        int distance_travelled = 0;
        while (distance_travelled < 15) {
          char* control = single_poll_input();

          if (control != NULL) {
            printf("%s\n", control);
          }

          moveCharacter(team_a[game_state_ptr->character_turn_team_a], control,
                        &distance_travelled);
          drawCharacter(team_a[game_state_ptr->character_turn_team_a]);

          wait_for_vsync();  // swap front and back buffers on VGA vertical sync
          pixel_buffer_start = *(buffer_register + 1);  // new back buffer
        }

        //----------Stage 2 of turn, output bar for weapon or stay
        printf("Character %d's turn: Press 1 to throw a grenade or 2 to stay\n",
               game_state_ptr->character_turn_team_a);

        while (1) {
          ps2_data = *ps2_ptr;
          RVALID = ps2_data & 0x8000;

          if (RVALID) {
            byte1 = byte2;
            byte2 = byte3;
            byte3 = ps2_data & 0xFF;
          }

          if (byte3 == 0x16) {  // User pressed 1
            if (byte2 == 0xF0) {
              printf("You selected throw grenade\n");
              break;
            }
          } else if (byte3 == 0x1E) {  // User pressed 2
            if (byte2 == 0xF0) {
              printf("You selected stay\n");
              end_turn = true;
              break;
            }
          }
        }
        byte1 = byte2 = byte3 = 0;
      }

      if (!end_turn) {
        // grenade logic
        printf("call grenade logic controls!\n");
      }

      // END TURN LOGIC
      //  Give turn to other team and if we just controlled character 2,
      //  next turn will be controlling character 0
      game_state_ptr->character_turn_team_a = getCharacterIndexForNextTurn(
          team_a, game_state_ptr->character_turn_team_a);
      game_state_ptr->team_turn = 'b';

      char game_result = checkWinCondition();
      printf("\nCurrent game result is %c\n", game_result);
    }

    // Team B's Turn
    else {
      printf("Team B's Turn\n");
      printf("Character %d's turn: Press 1 to move or 2 to stay\n",
             game_state_ptr->character_turn_team_b);

      //-----------------------Stage 1 of turn, draw bottom bar here
      while (1) {
        ps2_data = *ps2_ptr;
        RVALID = ps2_data & 0x8000;

        if (RVALID) {
          byte1 = byte2;
          byte2 = byte3;
          byte3 = ps2_data & 0xFF;
        }

        if (byte3 == 0x16) {  // User pressed 1
          if (byte2 == 0xF0) {
            printf("You selected move\n");
            break;
          }
        } else if (byte3 == 0x1E) {  // User pressed 2
          if (byte2 == 0xF0) {
            printf("You selected stay\n");
            end_turn = true;
            break;
          }
        }
      }
      byte1 = byte2 = byte3 = 0;

      if (!end_turn) {
        // Input handler logic for moving controls
        int distance_travelled = 0;
        while (distance_travelled < 15) {
          char* control = single_poll_input();

          if (control != NULL) {
            printf("%s\n", control);
          }

          moveCharacter(team_b[game_state_ptr->character_turn_team_b], control,
                        &distance_travelled);
          drawCharacter(team_b[game_state_ptr->character_turn_team_b]);

          wait_for_vsync();  // swap front and back buffers on VGA vertical sync
          pixel_buffer_start = *(buffer_register + 1);  // new back buffer
        }

        //----------Stage 2 of turn, output bar for weapon or stay
        printf("Character %d's turn: Press 1 to throw a grenade or 2 to stay\n",
               game_state_ptr->character_turn_team_a);

        while (1) {
          ps2_data = *ps2_ptr;
          RVALID = ps2_data & 0x8000;

          if (RVALID) {
            byte1 = byte2;
            byte2 = byte3;
            byte3 = ps2_data & 0xFF;
          }

          if (byte3 == 0x16) {  // User pressed 1
            if (byte2 == 0xF0) {
              printf("You selected throw grenade\n");
              break;
            }
          } else if (byte3 == 0x1E) {  // User pressed 2
            if (byte2 == 0xF0) {
              printf("You selected stay\n");
              end_turn = true;
              break;
            }
          }
        }
        byte1 = byte2 = byte3 = 0;
      }

      if (!end_turn) {
        // grenade logic
        printf("call grenade logic controls\n");
      }

      // END TURN LOGIC (occurs after user attacks or decides to stay)
      //  Give turn to other team and if we just controlled character 2,
      //  next turn will be controlling character 0
      game_state_ptr->character_turn_team_b = getCharacterIndexForNextTurn(
          team_b, game_state_ptr->character_turn_team_b);
      game_state_ptr->team_turn = 'a';

      char game_result = checkWinCondition();
      printf("\nCurrent game result is %c\n", game_result);
    }

    // renderIn(player.idleCharacter);
    // renderIn(player.walkLeftCharacter);
    // renderIn(player.walkRightCharacter);

    // renderIn(leftMovementObj);

    // count++;

    // if (count % 100) {
    //     // rightMovementObj->x += 5;
    //     renderOut(rightMovementObj);
    //     renderIn(rightMovementObj);

    // }

    // if (count % 200) {
    //     // leftMovementObj->x += 5;
    //     // leftMovementObj->y += 5;
    //     renderOut(leftMovementObj);
    //     renderIn(leftMovementObj);

    // }
  }

  free(leftMovementObj);
  free(rightMovementObj);
}

// Functions
// ------------------------------------------------------------------------------

// Screen Functions
void clear_screen() {
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      // 0x0000 represents:
      // 0 red (3rd hex digit)
      // 0 green (2nd hex )
      // 0 blue (binary 0 to 4)
      plot_pixel(x, y, 0x0000);
    }
  }
}

void draw_solid_sky() {
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    for (int y = 0; y < SCREEN_HEIGHT - 40; y++) {
      plot_pixel(x, y, 0x68abde);
    }
  }
}

void wait_for_vsync() {
  // Store 1 into buffer register to enable swaps
  volatile int* buffer_register = (int*)0xFF203020;
  *buffer_register = 1;

  // obtaining value stored in status register
  // if 1 then swap is ongoing, if 0 then swap completed
  volatile int* status_register = (buffer_register + 3);
  int status_register_value = *(status_register);

  // Poll for the S bit in status register until it becomes 0.
  // When it becomes 0, then finish function, otherwise hold it there.
  while ((status_register_value & 0x1) != 0) {
    status_register_value = *(status_register);  // Polling
  }
}

void draw_line(int x0, int y0, int x1, int y1, short int line_color) {
  // If is_steep then we want to use
  bool is_steep = abs(y1 - y0) > abs(x1 - x0);

  // Basically flips the algorithm such that the x-axis and y-axis are swapped
  // but only if it is steep.
  if (is_steep) {
    swap(&x0, &y0);
    swap(&x1, &y1);
  }

  // Makes sure x1 is the greater value
  // If swap needs to occur to ensure this, then we must swap the corresponding
  // y values as well.
  if (x0 > x1) {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }

  int y_step;
  // Don't need abs here, because above be made sure that x1 > x0
  int deltax = x1 - x0;
  int deltay = abs(y1 - y0);
  // The formula for error E =
  int error = -(deltax / 2);
  int y = y0;

  // If y1 > y0, step is positive (going up)
  if (y0 < y1) {
    y_step = 1;
  } else {  // If y0 > y1, step is negative (going down)
    y_step = -1;
  }

  // For all x values from x0 to x1 (inclusive)
  for (int x = x0; x <= x1; x++) {
    if (is_steep) {
      // Here is where we correct orient it such that we flip back
      // the (x,y) variables due to the intial swap if is_steep = true.
      plot_pixel(y, x, line_color);
    } else {
      plot_pixel(x, y, line_color);
    }

    // Calculating the error for the current pixel.
    // With the calculation we will determine if we want to increase our
    // y-value (if the line is closer to the diagonal pixel) or keep it
    // the same (if the line is closer to the horizontal pixel)
    error = error + deltay;
    // error > 0, if the line is closer to the diagonal pixel
    if (error > 0) {
      y += y_step;
      error -= deltax;
    }
  }
}

void draw_6x6_box(int x0, int y0, short int box_color) {
  // draw a 2 2 pixel wide lines stacked
  for (int i = 0; i <= 3; i++) {
    draw_line(x0 - 3, y0 + i, x0 + 3, y0 + i, box_color);
  }
  for (int i = 1; i <= 3; i++) {
    draw_line(x0 - 3, y0 - i, x0 + 3, y0 - i, box_color);
  }
}

// Helper Swap Function
void swap(int* num1, int* num2) {
  int temp = *num1;
  *num1 = *num2;
  *num2 = temp;
}

//-----------------------------------------------------------------------------------------

// Drawing Functions
void plot_pixel(int x, int y, short int line_color) {
  if (line_color != -1) {
    volatile short int* one_pixel_address;
    one_pixel_address =
        (volatile short int*)pixel_buffer_start + (y << 9) + (x << 0);
    *one_pixel_address = line_color;
  }
}

//-----------------------------------------------------------------------------------------

// Game Logic Functions
void initializeGame() {
  game_state_ptr->team_turn = 'a';  //'a' for team A, 'b' for team B
  game_state_ptr->character_turn_team_a = 0;
  game_state_ptr->character_turn_team_b = 0;
  game_state_ptr->game_running = false;
}

int getCharacterIndexForNextTurn(
    struct Character* team_array[NUM_CHARACTERS_PER_TEAM],
    int current_character_turn_index) {
  int next_idx;
  for (int i = 1; i <= NUM_CHARACTERS_PER_TEAM; i++) {
    next_idx = (current_character_turn_index + i) % NUM_CHARACTERS_PER_TEAM;

    if (team_array[next_idx]->state != DEAD) {
      return next_idx;
    }
  }

  return next_idx;
}

char checkWinCondition() {
  int dead_count_a = 0;
  int dead_count_b = 0;

  for (int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++) {
    if (!team_a[i]->state == DEAD) {
      dead_count_a++;
    }

    if (!team_b[i]->state == DEAD) {
      dead_count_b++;
    }
  }

  if (dead_count_a < NUM_CHARACTERS_PER_TEAM &&
      dead_count_b < NUM_CHARACTERS_PER_TEAM) {
    return 'i';
  } else if (dead_count_a == NUM_CHARACTERS_PER_TEAM &&
             dead_count_b == NUM_CHARACTERS_PER_TEAM) {
    return 't';
  } else if (dead_count_a == NUM_CHARACTERS_PER_TEAM) {
    return 'l';  // 'l' means team A lost
  } else if (dead_count_b == NUM_CHARACTERS_PER_TEAM) {
    return 'w';  // 'w' means team A won
  } else {
    return 'x';  // Unexpected case
  }
}

// make new .c file platformhandler
// make GameObject* platform
// copy rudra code commented out testing __code_model_medium
// xy tracking top left
// once done in main

// go to while loop
// render in (GameObject* platform)
