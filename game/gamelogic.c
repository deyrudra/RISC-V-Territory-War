#include "gamelogic.h"

GameObject* mainMenuTitleObj;
GameObject* platformObj;
GameObject* moveOrStayBannerObj;
GameObject* grenadeOrStayBannerObj;
GameObject* movementControlBannerObj;
GameObject* groundObj;

// GameObject** displacementBarObj;
Bar displacementBar;


Character player_a0;
Character player_b0;

Platform platform1;
Platform platform_ground;

GameState* game_state_ptr;
Character* team_a[NUM_CHARACTERS_PER_TEAM];
Character* team_b[NUM_CHARACTERS_PER_TEAM];

void startGame() {
    initializeCharacter(&player_a0, 100 + PLAYER_WIDTH,
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

    // Delete the memory taken up for the menu background.
    destroyBackground(&menuBackground);

    // Render out title screen
    renderOut(mainMenuTitleObj);


    // Render in initial game map, players, and objects in layers

    initializeBackground(&skyBackground, &sky, SKY_WIDTH, SKY_HEIGHT);
    placeBackground(&skyBackground);


    // Layer 2 map objects and banners

    initializePlatform(&platform1, &platform, 100, 50, PLATFORM_WIDTH, PLATFORM_HEIGHT);
    placePlatform(&platform1);

    initializePlatform(&platform_ground, &ground, 0, SCREEN_HEIGHT - BANNER_HEIGHT - GROUND_HEIGHT, GROUND_WIDTH, GROUND_HEIGHT);
    placePlatform(&platform_ground);
   
    // Layer 3 characters
    drawCharacter(&player_a0);
    drawCharacter(&player_b0);

    while(game_state_ptr->game_running){
        handle_team_turn();
    }
}

void handle_team_turn() {
    bool end_turn = false;
    volatile int* ps2_ptr = (int*)PS2_BASE;
    byte1 = 0, byte2 = 0, byte3 = 0;

    // Team A's Turn
    if (game_state_ptr->team_turn == 'a') {

        //-----------------------Stage 1 of turn, draw bottom bar here
        renderIn(moveOrStayBannerObj);
        printf("Team A's Turn\n");
        printf("Character %c%d's turn: Press 1 to move or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_a);
        end_turn = poll_move_or_stay_input();
        //-----------------------------

        if (!end_turn) {
            // Input handler logic for moving controls
            renderIn(movementControlBannerObj);
            //initializeBar(&displacementBarObj, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22);
            initializeBar(&displacementBar, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22);
            
            int displacement = 0;
            int lastPartitionRendered = 0;
            while (displacement < DISPLACEMENT_LIMIT) {
                bool flipped = false;
                char* control = single_poll_input();

                if(control == gameControls[6]){
                    break; //user pressed stay
                }

                moveCharacter(team_a[game_state_ptr->character_turn_team_a], control,
                            &displacement);
                drawCharacter(team_a[game_state_ptr->character_turn_team_a]);
                currentView = team_a[game_state_ptr->character_turn_team_a]->characterView;

                if(displacement < 0){
                    displacement *=-1;
                    flipped = true;
                }

                double ratio = (double)displacement / DISPLACEMENT_LIMIT;

                if(ratio > 1) ratio = 1;

                int num_partitions_filled = ratio * (double)NUM_DISPLACEMENT_BAR_PARTITIONS;

                if(num_partitions_filled > lastPartitionRendered){
                    for(int i = lastPartitionRendered; i < num_partitions_filled; i++){
                        renderIn(displacementBar.barObj[i]);
                    }

                } else if(num_partitions_filled < lastPartitionRendered){
                    for(int i = lastPartitionRendered; i >= num_partitions_filled; i--){
                        renderOut(displacementBar.barObj[i]);
                    }
                }

                lastPartitionRendered = num_partitions_filled;

                // Restore negative displacement
                if(flipped){
                    displacement*=-1;
                }

                wait_for_vsync();  // swap front and back buffers on VGA vertical sync
                
                if (currentView == LEFTVIEW) {
                    if (prevView == LEFTVIEW) {
                        // Do Nothing
                    }
                    else if (prevView == MIDDLEVIEW) {
                        saveMiddle();
                        renderLeft();
                    }
                    else if (prevView == RIGHTVIEW) {
                        saveRight();
                        renderLeft();
                    }
                    
                }
                else if (currentView == MIDDLEVIEW) {
                    if (prevView == LEFTVIEW) {
                        saveLeft();
                        renderMiddle();
                    }
                    else if (prevView == MIDDLEVIEW) {
                        // Do Nothing
                    }
                    else if (prevView == RIGHTVIEW) {
                        saveRight();
                        renderMiddle();
                    }
                    
                }
                else if (currentView == RIGHTVIEW) {
                    if (prevView == LEFTVIEW) {
                        saveLeft();
                        renderRight();
                    }
                    else if (prevView == MIDDLEVIEW) {
                        saveMiddle();
                        renderRight();
                    }
                    else if (prevView == RIGHTVIEW) {
                        // Do Nothing
                    }
                    
                }
                prevView = currentView;

            }

            // printf("Last partition rendered is: %d\n", lastPartitionRendered);
            resetBar(&displacementBar, lastPartitionRendered-1);
            resetArrowKeyReleaseFlags();
            byte1 = byte2 = byte3 = 0;
            //CURRENTLY just rendering on top of prev banner and displacememt bar

            //----------Stage 2 of turn, output bar for weapon or stay
            printf("Character %c%d's turn: Press 1 to throw a grenade or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_a);
            renderIn(grenadeOrStayBannerObj);

            end_turn = poll_grenade_or_stay_input();
        }

        if (!end_turn) {
            // grenade logic
            printf("call grenade logic controls!\n");
        }

        // END TURN LOGIC
        game_state_ptr->character_turn_team_a = getCharacterIndexForNextTurn(team_a, game_state_ptr->character_turn_team_a);
        game_state_ptr->team_turn = 'b';

        char game_result = checkWinCondition();
        printf("\nCurrent game result is %c\n", game_result);
    }
    // Team B's Turn (DISPLACEMENT BAR DOES NOT WORK FOR TEAM B CHARACER YET, WILL FIX IT TMRW)
    else {
        //-----------------------Stage 1 of turn, draw bottom bar here
        renderIn(moveOrStayBannerObj);
        printf("Team B's Turn\n");
        printf("Character %c%d's turn: Press 1 to move or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_b);
        end_turn = poll_move_or_stay_input();
        //-----------------------------

        if (!end_turn) {
            // Input handler logic for moving controls
            renderIn(movementControlBannerObj);
            //initializeBar(&displacementBarObj, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22);
            
            int displacement = 0;
            int lastPartitionRendered = 0;
            while (displacement < DISPLACEMENT_LIMIT) {
                bool flipped = false;
                char* control = single_poll_input();

                if(control == gameControls[6]){
                    break; //user pressed stay
                }

                moveCharacter(team_b[game_state_ptr->character_turn_team_b], control,
                            &displacement);
                drawCharacter(team_b[game_state_ptr->character_turn_team_b]);
                currentView = team_b[game_state_ptr->character_turn_team_b]->characterView;

                if(displacement < 0){
                    displacement *=-1;
                    flipped = true;
                }

                double ratio = (double)displacement / DISPLACEMENT_LIMIT;

                if(ratio > 1) ratio = 1;

                int num_partitions_filled = ratio * (double)NUM_DISPLACEMENT_BAR_PARTITIONS;

                if(num_partitions_filled > lastPartitionRendered){
                    for(int i = lastPartitionRendered; i < num_partitions_filled; i++){
                        renderIn(displacementBar.barObj[i]);
                    }

                } else if(num_partitions_filled < lastPartitionRendered){
                    for(int i = lastPartitionRendered; i >= num_partitions_filled; i--){
                        renderOut(displacementBar.barObj[i]);
                    }
                }

                lastPartitionRendered = num_partitions_filled;

                // Restore negative displacement
                if(flipped){
                    displacement*=-1;
                }

                wait_for_vsync();  // swap front and back buffers on VGA vertical sync
                
                if (currentView == LEFTVIEW) {
                    if (prevView == LEFTVIEW) {
                        // Do Nothing
                    }
                    else if (prevView == MIDDLEVIEW) {
                        saveMiddle();
                        renderLeft();
                    }
                    else if (prevView == RIGHTVIEW) {
                        saveRight();
                        renderLeft();
                    }
                    
                }
                else if (currentView == MIDDLEVIEW) {
                    if (prevView == LEFTVIEW) {
                        saveLeft();
                        renderMiddle();
                    }
                    else if (prevView == MIDDLEVIEW) {
                        // Do Nothing
                    }
                    else if (prevView == RIGHTVIEW) {
                        saveRight();
                        renderMiddle();
                    }
                    
                }
                else if (currentView == RIGHTVIEW) {
                    if (prevView == LEFTVIEW) {
                        saveLeft();
                        renderRight();
                    }
                    else if (prevView == MIDDLEVIEW) {
                        saveMiddle();
                        renderRight();
                    }
                    else if (prevView == RIGHTVIEW) {
                        // Do Nothing
                    }
                    
                }
                prevView = currentView;

            }
            

            resetBar(&displacementBar, lastPartitionRendered-1);
            resetArrowKeyReleaseFlags();
            byte1 = byte2 = byte3 = 0;
            //CURRENTLY just rendering on top of prev banner and displacememt bar

            //----------Stage 2 of turn, output bar for weapon or stay
            printf("Character %c%d's turn: Press 1 to throw a grenade or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_b);
            renderIn(grenadeOrStayBannerObj);
            end_turn = poll_grenade_or_stay_input();
        }

        if (!end_turn) {
            // grenade logic
            printf("call grenade logic controls!\n");
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
  
//   void initializeBar(GameObject*** barObj, int* asset, int width, int height, int num_partitions, int start_x, int start_y){

//     *barObj = malloc((num_partitions) * sizeof(GameObject*));


//     for(int i = 0; i < num_partitions; i++){
//         (*barObj)[i] = malloc(sizeof(GameObject));

//         (*barObj)[i]->asset = asset;
//         (*barObj)[i]->height = height;
//         (*barObj)[i]->width = width;
//         (*barObj)[i]->prevPixelData = malloc(width * height * sizeof(int));
//         (*barObj)[i]->x = malloc(sizeof(int));
//         (*barObj)[i]->y = malloc(sizeof(int));
//         (*barObj)[i]->velocityX = malloc(sizeof(double));
//         (*barObj)[i]->velocityY = malloc(sizeof(double));
//         (*barObj)[i]->collidable = malloc(sizeof(int));


//         //Set values (decide how to deal with setting velocity and x and y for moving health bars)
//         *((*barObj)[i]->x) = start_x + i*width;
//         *((*barObj)[i]->y) = start_y;
//         *((*barObj)[i]->velocityX) = 0;
//         *((*barObj)[i]->velocityY) = 0;
//         *((*barObj)[i]->collidable) = 0;
//     }

// };