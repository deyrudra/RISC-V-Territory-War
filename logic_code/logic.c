#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LED_BASE 0xFF200000
#define LEDR_BASE 0xFF200000
#define HEX3_HEX0_BASE 0xFF200020
#define HEX5_HEX4_BASE 0xFF200030
#define SW_BASE 0xFF200040
#define KEY_BASE 0xFF200050
#define JP1_BASE 0xFF200060
#define JP2_BASE 0xFF200070
#define PS2_BASE 0xFF200100
#define PS2_DUAL_BASE 0xFF200108
#define JTAG_UART_BASE 0xFF201000
#define IrDA_BASE 0xFF201020
#define TIMER_BASE 0xFF202000
#define TIMER_2_BASE 0xFF202020
#define AV_CONFIG_BASE 0xFF203000
#define RGB_RESAMPLER_BASE 0xFF203010
#define PIXEL_BUF_CTRL_BASE 0xFF203020
#define CHAR_BUF_CTRL_BASE 0xFF203030
#define AUDIO_BASE 0xFF203040
#define VIDEO_IN_BASE 0xFF203060
#define EDGE_DETECT_CTRL_BASE 0xFF203070
#define ADC_BASE 0xFF204000
#define MTIME_BASE 0xFF202100

#define MAP_BOUNDS 0
#define PIXELS_IN_1_METER 1
#define SCREEN_PIXEL_WIDTH 640
#define SCREEN_PIXEL_HEIGHT 480
#define NUM_CHARACTERS_PER_TEAM 3

typedef enum { IDLE, MOVING, GUN, GRENADE, BOOT, JUMPING, DEAD } CharacterState;

struct Character {
  int pos_x, pos_y;
  int prev_x, prev_y;
  bool is_alive;
  int health;
  CharacterState state;
};

struct GameState {
  char team_turn;
  int character_turn_team_a;
  int character_turn_team_b;
  bool game_running;
};

// Global pointers
struct Character* team_a[NUM_CHARACTERS_PER_TEAM];
struct Character* team_b[NUM_CHARACTERS_PER_TEAM];
struct GameState* game_state_ptr;

// global pointers to memory mapped IO
volatile int* ps2_ptr = (int*)PS2_BASE;

// Function declarations
void initializeGame();
int getCharacterIndexForNextTurn(struct Character* team_array[3],
                                 int current_character_turn_index);
char checkWinCondition();

int main() {
  initializeGame();
  // call function to draw start screen

  printf("Welcome to Territory War!\n");
  printf("Press Enter to Start\n");

  int ps2_data, RVALID;
  uint8_t byte1 = 0, byte2 = 0, byte3 = 0;

  // Poll user to hit enter key
  while (1) {
    ps2_data = *ps2_ptr;
    RVALID = ps2_data & 0x8000;

    if (RVALID) {
      byte1 = byte2;
      byte2 = byte3;
      byte3 = ps2_data & 0xFF;
    }

    if (byte2 == 0xF0) {
      if (byte3 == 0x5A) {
        break;
      }
    }
  }
  byte1 = byte2 = byte3 = 0;

  printf("Game started!\n\n");


  game_state_ptr->game_running = true;

  //-----------------------------------------

  // main game loop
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
        // logic for moving controls
        //-------------

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
        // logic for moving controls
        //-------------

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
  }

  return 0;
}

void initializeGame() {
  game_state_ptr->team_turn = 'a';  //'a' for team A, 'b' for team B
  game_state_ptr->character_turn_team_a = 0;
  game_state_ptr->character_turn_team_b = 0;
  game_state_ptr->game_running = false;

  for (int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++) {
    team_a[i]->is_alive = true;
    team_a[i]->health = 100;
    team_a[i]->state = IDLE;
    // init xy positions
  }

  for (int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++) {
    team_b[i]->is_alive = true;
    team_b[i]->health = 100;
    team_b[i]->state = IDLE;
    // init xy positions
  }
}

int getCharacterIndexForNextTurn(struct Character* team_array[3],
                                 int current_character_turn_index) {
  int next_idx;
  for (int i = 1; i <= NUM_CHARACTERS_PER_TEAM; i++) {
    next_idx = (current_character_turn_index + i) % NUM_CHARACTERS_PER_TEAM;

    if (team_array[next_idx]->is_alive) {
      return next_idx;
    }
  }

  return next_idx;
}

char checkWinCondition() {
  int dead_count_a = 0;
  int dead_count_b = 0;

  for (int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++) {
    if (!team_a[i]->is_alive) {
      dead_count_a++;
    }

    if (!team_b[i]->is_alive) {
      dead_count_b++;
    }
  }

  if (dead_count_a < 3 && dead_count_b < 3) {
    return 'i';
  } else if (dead_count_a == 3 && dead_count_b == 3) {
    return 't';
  } else if (dead_count_a == 3) {
    return 'l';  // 'l' means team A lost
  } else if (dead_count_b == 3) {
    return 'w';  // 'w' means team A won
  } else {
    return 'x';  // Unexpected case
  }
}