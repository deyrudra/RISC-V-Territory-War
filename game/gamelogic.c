#include "gamelogic.h"

GameObject* mainMenuTitleObj;
GameObject* platformObj;
GameObject* moveOrStayBannerObj1;
GameObject* grenadeOrStayBannerObj1;
GameObject* movementControlBannerObj1;
GameObject* grenadeControlBannerObj1;

GameObject* moveOrStayBannerObj2;
GameObject* grenadeOrStayBannerObj2;
GameObject* movementControlBannerObj2;
GameObject* grenadeControlBannerObj2;

GameObject* moveOrStayBannerObj3;
GameObject* grenadeOrStayBannerObj3;
GameObject* movementControlBannerObj3;
GameObject* grenadeControlBannerObj3;

GameObject* groundObj;

// GameObject** displacementBarObj;
Bar displacementBar;


Character player_a0;
Character player_a1;
Character player_a2;
Character player_b0;
Character player_b1;
Character player_b2;

Platform platform1;
Platform platform_ground;

// Background objects, assets, and platforms
GameObject* ballAsset;
GameObject* coolerAsset;
GameObject* groundAsset;
GameObject* lifeguardAsset;
GameObject* netAsset1;
GameObject* netAsset2;
GameObject* netAsset3;
GameObject* sandcastleAsset;
GameObject* tressureAsset;
GameObject* umbrellaAsset;

Platform ballPlatform;
Platform chestPlatform;
Platform coolerPlatform;
Platform groundPlatform1;
Platform groundPlatform2;
Platform groundPlatform3;
Platform groundPlatform4;
Platform lifeguardPlatform1;
Platform lifeguardPlatform2;
Platform lifeguardPlatform3;
Platform lifeguardPlatform4;
Platform lifeguardPlatform5;
Platform lifeguardPlatform6;
Platform netPlatform;
Platform umbrellaPlatform;




GameState* game_state_ptr;
Character* team_a[NUM_CHARACTERS_PER_TEAM];
Character* team_b[NUM_CHARACTERS_PER_TEAM];



void startGame() {
    initializeCharacter(&player_a0, 100 + PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_a0_idle, &player_a0_leftmovement,
                        &player_a0_rightmovement, &player_a0_jump, 'a');
    initializeCharacter(&player_a1, 150 + PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_a1_idle, &player_a1_leftmovement,
                        &player_a1_rightmovement, &player_a1_jump, 'a');
    initializeCharacter(&player_a2, 200 + PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_a2_idle, &player_a2_leftmovement,
                        &player_a2_rightmovement, &player_a2_jump, 'a');

    initializeCharacter(&player_b0, WORLD_WIDTH - 20 - PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_b0_idle, &player_b0_leftmovement,
                        &player_b0_rightmovement, &player_b0_jump, 'b');
    initializeCharacter(&player_b1, WORLD_WIDTH - 70 - PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_b1_idle, &player_b1_leftmovement,
                        &player_b1_rightmovement, &player_b1_jump, 'b');
    initializeCharacter(&player_b2, WORLD_WIDTH - 120 - PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_b2_idle, &player_b2_leftmovement,
                        &player_b2_rightmovement, &player_b2_jump, 'b');

    initializeGame();
    
    // Add characters to teams
    team_a[0] = &player_a0;
    team_a[1] = &player_a1;
    team_a[2] = &player_a2;
    team_b[0] = &player_b0;
    team_b[1] = &player_b1;
    team_b[2] = &player_b2;

    poll_start_input();
    game_state_ptr->game_running = true;

    // Delete the memory taken up for the menu background.
    destroyBackground(&menuBackground);

    // Render out title screen
    renderOut(mainMenuTitleObj);


    // Render in initial game map, players, and objects in layers


    // Layer 1 Background Data
    // Initializations and Renderings of background objects, assets, and platforms
    initializeBackground(&skyBackground, &sky, SKY_WIDTH, SKY_HEIGHT);
    placeBackground(&skyBackground);
    destroyBackground(&skyBackground);

    initializeGeneralObject(&ballAsset, &ballAsset282_39, 1, 282, 39, BALLASSET282_39_WIDTH, BALLASSET282_39_HEIGHT);
    renderIn(ballAsset);
    destroyGeneralObject(ballAsset);

    initializeGeneralObject(&coolerAsset, &coolerAsset75_140, 1, 75, 140, COOLERASSET75_140_WIDTH, COOLERASSET75_140_HEIGHT);
    renderIn(coolerAsset);
    destroyGeneralObject(coolerAsset);

    initializeGeneralObject(&groundAsset, &groundAsset0_173, 1, 0, 173, GROUNDASSET0_173_WIDTH, GROUNDASSET0_173_HEIGHT);
    renderIn(groundAsset);
    destroyGeneralObject(groundAsset);

    initializeGeneralObject(&lifeguardAsset, &lifeguardAsset652_11, 1, 652, 11, LIFEGUARDASSET652_11_WIDTH, LIFEGUARDASSET652_11_HEIGHT);
    renderIn(lifeguardAsset);
    destroyGeneralObject(lifeguardAsset);

    initializeGeneralObject(&umbrellaAsset, &umbrellaAsset137_88, 1, 137, 88, UMBRELLAASSET137_88_WIDTH, UMBRELLAASSET137_88_HEIGHT);
    renderIn(umbrellaAsset);
    destroyGeneralObject(umbrellaAsset);
    
    initializeGeneralObject(&sandcastleAsset, &sandcastleAsset774_130, 1, 774, 130, SANDCASTLEASSET774_130_WIDTH, SANDCASTLEASSET774_130_HEIGHT);
    renderIn(sandcastleAsset);
    destroyGeneralObject(sandcastleAsset);

    initializeGeneralObject(&tressureAsset, &tressureAsset522_153, 1, 522, 153, TRESSUREASSET522_153_WIDTH, TRESSUREASSET522_153_HEIGHT);
    renderIn(tressureAsset);
    destroyGeneralObject(tressureAsset);

    initializeGeneralObject(&netAsset1, &netAsset1_349_29, 1, 349, 29, NETASSET1_349_29_WIDTH, NETASSET1_349_29_HEIGHT);
    renderIn(netAsset1);
    destroyGeneralObject(netAsset1);

    initializeGeneralObject(&netAsset2, &netAsset2_336_95, 1, 336, 95, NETASSET2_336_95_WIDTH, NETASSET2_336_95_HEIGHT);
    renderIn(netAsset2);
    destroyGeneralObject(netAsset2);

    initializeGeneralObject(&netAsset3, &netAsset3_617_95, 1, 617, 95, NETASSET3_617_95_WIDTH, NETASSET3_617_95_HEIGHT);
    renderIn(netAsset3);
    destroyGeneralObject(netAsset3);


    // Rendering of background objects, assets, and platforms


    // Layer 2 Map objects, Platforms, and banners
    initializePlatform(&ballPlatform, &ballPlatform282_45, 282, 45, BALLPLATFORM282_45_WIDTH, BALLPLATFORM282_45_HEIGHT);
    placePlatform(&ballPlatform);
    initializePlatform(&chestPlatform, &chestPlatform522_153, 522, 153, CHESTPLATFORM522_153_WIDTH, CHESTPLATFORM522_153_HEIGHT);
    placePlatform(&chestPlatform);
    initializePlatform(&coolerPlatform, &coolerPlatform78_154, 78, 154, COOLERPLATFORM78_154_WIDTH, COOLERPLATFORM78_154_HEIGHT);
    placePlatform(&coolerPlatform);
    initializePlatform(&groundPlatform1, &groundPlatform1_0_173, 0, 173, GROUNDPLATFORM1_0_173_WIDTH, GROUNDPLATFORM1_0_173_HEIGHT);
    placePlatform(&groundPlatform1);
    initializePlatform(&groundPlatform2, &groundPlatform2_610_173, 610, 173, GROUNDPLATFORM2_610_173_WIDTH, GROUNDPLATFORM2_610_173_HEIGHT);
    placePlatform(&groundPlatform2);
    initializePlatform(&groundPlatform3, &groundPlatform3_316_178, 316, 178, GROUNDPLATFORM3_316_178_WIDTH, GROUNDPLATFORM3_316_178_HEIGHT);
    placePlatform(&groundPlatform3);
    initializePlatform(&groundPlatform4, &groundPlatform4_501_178, 501, 178, GROUNDPLATFORM4_501_178_WIDTH, GROUNDPLATFORM4_501_178_HEIGHT);
    placePlatform(&groundPlatform4);
    initializePlatform(&lifeguardPlatform1, &lifeguardPlatform1_650_67, 650, 67, LIFEGUARDPLATFORM1_650_67_WIDTH, LIFEGUARDPLATFORM1_650_67_HEIGHT);
    placePlatform(&lifeguardPlatform1);
    initializePlatform(&lifeguardPlatform2, &lifeguardPlatform2_684_79, 684, 79, LIFEGUARDPLATFORM2_684_79_WIDTH, LIFEGUARDPLATFORM2_684_79_HEIGHT);
    placePlatform(&lifeguardPlatform2);
    initializePlatform(&lifeguardPlatform3, &lifeguardPlatform3_684_97, 684, 97, LIFEGUARDPLATFORM3_684_97_WIDTH, LIFEGUARDPLATFORM3_684_97_HEIGHT);
    placePlatform(&lifeguardPlatform3);
    initializePlatform(&lifeguardPlatform4, &lifeguardPlatform4_683_115, 683, 115, LIFEGUARDPLATFORM4_683_115_WIDTH, LIFEGUARDPLATFORM4_683_115_HEIGHT);
    placePlatform(&lifeguardPlatform4);
    initializePlatform(&lifeguardPlatform5, &lifeguardPlatform5_682_131, 682, 131, LIFEGUARDPLATFORM5_682_131_WIDTH, LIFEGUARDPLATFORM5_682_131_HEIGHT);
    placePlatform(&lifeguardPlatform5);
    initializePlatform(&lifeguardPlatform6, &lifeguardPlatform6_682_150, 682, 150, LIFEGUARDPLATFORM6_682_150_WIDTH, LIFEGUARDPLATFORM6_682_150_HEIGHT);
    placePlatform(&lifeguardPlatform6);
    initializePlatform(&netPlatform, &netPlatform356_29, 356, 29, NETPLATFORM356_29_WIDTH, NETPLATFORM356_29_HEIGHT);
    placePlatform(&netPlatform);
    initializePlatform(&umbrellaPlatform, &umbrellaPlatform148_97, 148, 97, UMBRELLAPLATFORM148_97_WIDTH, UMBRELLAPLATFORM148_97_HEIGHT);
    placePlatform(&umbrellaPlatform);

    // initializePlatform(&platform1, &platform, 100, 50, PLATFORM_WIDTH, PLATFORM_HEIGHT);
    // placePlatform(&platform1);

    // initializePlatform(&platform_ground, &ground, 0, SCREEN_HEIGHT - BANNER_HEIGHT - GROUND_HEIGHT, GROUND_WIDTH, GROUND_HEIGHT);
    // placePlatform(&platform_ground);
   
    // Layer 3 Characters

    

    drawCharacter(&player_a0, true);
    drawCharacter(&player_a1, true);
    drawCharacter(&player_a2, true);
    drawCharacter(&player_b0, true);
    drawCharacter(&player_b1, true);
    drawCharacter(&player_b2, true);

    drawInitialHealthBar(&player_a0);
    drawInitialHealthBar(&player_a1);
    drawInitialHealthBar(&player_a2);
    drawInitialHealthBar(&player_b0);
    drawInitialHealthBar(&player_b1);
    drawInitialHealthBar(&player_b2);

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
        renderIn(moveOrStayBannerObj1);
        renderIn(moveOrStayBannerObj2);
        renderIn(moveOrStayBannerObj3);
        printf("Team A's Turn\n");
        printf("Character %c%d's turn: Press 1 to move or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_a);
        end_turn = poll_move_or_stay_input();
        //-----------------------------

        if (!end_turn) {
            // Input handler logic for moving controls
            renderIn(movementControlBannerObj1);
            renderIn(movementControlBannerObj2);
            renderIn(movementControlBannerObj3);
            //initializeBar(&displacementBarObj, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22);
            printf("Before initialize displacemetn bar\n");

            initializeBar(&displacementBar, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22, 0);
            
            printf("After initialize displacemetn bar\n");
            int displacement = 0;
            while (abs_int(displacement) < DISPLACEMENT_LIMIT) {
                bool flipped = false;
                char* control = single_poll_input();

                if(control == gameControls[6]){
                    break; //user pressed stay
                }

                moveCharacter(team_a[game_state_ptr->character_turn_team_a], control,
                            &displacement);
                drawCharacter(team_a[game_state_ptr->character_turn_team_a], false);
                currentView = team_a[game_state_ptr->character_turn_team_a]->characterView;

                if(displacement < 0){
                    displacement *=-1;
                    flipped = true;
                }

                double ratio = (double)displacement / DISPLACEMENT_LIMIT;

                if(ratio > 1) ratio = 1;

                int num_partitions_filled = ratio * (double)NUM_DISPLACEMENT_BAR_PARTITIONS;

                if(num_partitions_filled > displacementBar.lastRenderedPartition){
                    for(int i = displacementBar.lastRenderedPartition; i < num_partitions_filled; i++){
                        renderIn(displacementBar.barObj[i]);
                    }

                } else if(num_partitions_filled < displacementBar.lastRenderedPartition){
                    for(int i = displacementBar.lastRenderedPartition; i >= num_partitions_filled; i--){
                        renderOut(displacementBar.barObj[i]);
                    }
                }
                
                setLastRenderedPartition(&displacementBar, num_partitions_filled);

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

            // printf("Last partition rendered is: %d\n", displacementBar.lastRenderedPartition);
            resetBar(&displacementBar, displacementBar.lastRenderedPartition-1);
            resetArrowKeyReleaseFlags();
            byte1 = byte2 = byte3 = 0;
            //CURRENTLY just rendering on top of prev banner and displacememt bar

            //----------Stage 2 of turn, output bar for weapon or stay
            // updateHealthBar(team_a[game_state_ptr->character_turn_team_a]);
            printf("Character %c%d's turn: Press 1 to throw a grenade or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_a);
            renderIn(grenadeOrStayBannerObj1);
            renderIn(grenadeOrStayBannerObj2);
            renderIn(grenadeOrStayBannerObj3);

            end_turn = poll_grenade_or_stay_input();
        }

        if (!end_turn) {
            renderIn(grenadeControlBannerObj1);
            renderIn(grenadeControlBannerObj2);
            renderIn(grenadeControlBannerObj3);
            // grenade logic
            printf("call grenade logic controls!\n");
            while(1){
                char* control = grenade_control_input();
                printf("%s\n", control);
            }
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
        renderIn(moveOrStayBannerObj1);
        renderIn(moveOrStayBannerObj2);
        renderIn(moveOrStayBannerObj3);
        printf("Team B's Turn\n");
        printf("Character %c%d's turn: Press 1 to move or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_b);
        end_turn = poll_move_or_stay_input();
        //-----------------------------

        if (!end_turn) {
            // Input handler logic for moving controls
            renderIn(movementControlBannerObj1);
            renderIn(movementControlBannerObj2);
            renderIn(movementControlBannerObj3);
            
            int displacement = 0;
            while (abs_int(displacement) < DISPLACEMENT_LIMIT) {
                bool flipped = false;
                char* control = single_poll_input();

                if(control == gameControls[6]){
                    break; //user pressed stay
                }

                moveCharacter(team_b[game_state_ptr->character_turn_team_b], control,
                            &displacement);
                drawCharacter(team_b[game_state_ptr->character_turn_team_b], false);
                currentView = team_b[game_state_ptr->character_turn_team_b]->characterView;

                if(displacement < 0){
                    displacement *=-1;
                    flipped = true;
                }

                double ratio = (double)displacement / DISPLACEMENT_LIMIT;

                if(ratio > 1) ratio = 1;

                int num_partitions_filled = ratio * (double)NUM_DISPLACEMENT_BAR_PARTITIONS;

                if(num_partitions_filled > displacementBar.lastRenderedPartition){
                    for(int i = displacementBar.lastRenderedPartition; i < num_partitions_filled; i++){
                        renderIn(displacementBar.barObj[i]);
                    }

                } else if(num_partitions_filled < displacementBar.lastRenderedPartition){
                    for(int i = displacementBar.lastRenderedPartition; i >= num_partitions_filled; i--){
                        renderOut(displacementBar.barObj[i]);
                    }
                }

                setLastRenderedPartition(&displacementBar, num_partitions_filled);

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
            

            resetBar(&displacementBar, displacementBar.lastRenderedPartition-1);
            resetArrowKeyReleaseFlags();
            byte1 = byte2 = byte3 = 0;
            //CURRENTLY just rendering on top of prev banner and displacememt bar

            //----------Stage 2 of turn, output bar for weapon or stay
            printf("Character %c%d's turn: Press 1 to throw a grenade or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_b);
            renderIn(grenadeOrStayBannerObj1);
            renderIn(grenadeOrStayBannerObj2);
            renderIn(grenadeOrStayBannerObj3);
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