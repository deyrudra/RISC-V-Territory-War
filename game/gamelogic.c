// gamelogic.c
#include "gamelogic.h"

GameObject* backgroundObj;
GameObject* mainMenuTitleObj;
GameObject* platformObj;
GameObject* skyObj;
GameObject* moveOrStayBannerObj;
GameObject* grenadeOrStayBannerObj;
GameObject* groundObj;

Character player_a0;
Character player_b0;

Platform platform1;
Platform platform_ground;

GameState* game_state_ptr;
Character* team_a[NUM_CHARACTERS_PER_TEAM];
Character* team_b[NUM_CHARACTERS_PER_TEAM];

void startGame() {
    initializeCharacter(&player_a0, 20 + PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &idle, &leftmovement,
                        &rightmovement, &jump);

    initializeCharacter(&player_b0, SCREEN_WIDTH - 20 - PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &idle, &leftmovement,
                        &rightmovement, &jump);

    initializeGame();
    
    // Add characters to teams
    team_a[0] = &player_a0;
    team_b[0] = &player_b0;

    poll_start_input();
    game_state_ptr->game_running = true;

    // Render out title screen
    renderOut(mainMenuTitleObj);


    // Render in initial game map, players, and objects in layers

    // Layer 1 background
    for (int ypos = 0; ypos < SCREEN_HEIGHT - 40; ypos += 40) {
    for (int xpos = 0; xpos < SCREEN_WIDTH; xpos += 40) {
        skyObj->x = &xpos;
        skyObj->y = &ypos;
        renderIn(skyObj);
    }
    }

    // Layer 2 map objects and banners

    initializePlatform(&platform1, &platform, 100, 50, PLATFORM_WIDTH, PLATFORM_HEIGHT);
    placePlatform(&platform1);

    initializePlatform(&platform_ground, &ground, 0, SCREEN_HEIGHT - BANNER_HEIGHT - GROUND_HEIGHT, GROUND_WIDTH, GROUND_HEIGHT);
    placePlatform(&platform_ground);
    // renderIn(platformObj);
    // renderIn(groundObj);
    renderIn(moveOrStayBannerObj);

    // Layer 3 characters
    drawCharacter(&player_a0);
    drawCharacter(&player_b0);

    int count = 0;

    handle_team_turn();
}

void handle_team_turn() {
    bool end_turn = false;
    volatile int* ps2_ptr = (int*)PS2_BASE;
    char byte1 = 0, byte2 = 0, byte3 = 0;

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
            while (distance_travelled < 200) {
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
            printf("Character %d's turn: Press 1 to throw a grenade or 2 to stay\n", game_state_ptr->character_turn_team_a);
            renderIn(grenadeOrStayBannerObj);

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
        game_state_ptr->character_turn_team_a = getCharacterIndexForNextTurn(
            team_a, game_state_ptr->character_turn_team_a);
        game_state_ptr->team_turn = 'b';

        char game_result = checkWinCondition();
        printf("\nCurrent game result is %c\n", game_result);
    }
    // Team B's Turn
    else {
        printf("Team B's Turn\n");
        printf("Character %d's turn: Press 1 to move or 2 to stay\n", game_state_ptr->character_turn_team_b);

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
                    
                printf("after vsync\n");
                distance_travelled++;
            }

            //----------Stage 2 of turn, output bar for weapon or stay
            printf("Character %d's turn: Press 1 to throw a grenade or 2 to stay\n", game_state_ptr->character_turn_team_b);
            renderIn(grenadeOrStayBannerObj);

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

        // END TURN LOGIC
        game_state_ptr->character_turn_team_b = getCharacterIndexForNextTurn(
            team_b, game_state_ptr->character_turn_team_b);
        game_state_ptr->team_turn = 'a';

        char game_result = checkWinCondition();
        printf("\nCurrent game result is %c\n", game_result);
    }
}

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
  