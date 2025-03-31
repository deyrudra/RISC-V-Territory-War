#include "gamelogic.h"

int ceil_custom(double x) {
    int i = (int)x;
    return (x > i) ? (i + 1) : i;
}

GameObject* mainMenuTitleObj;
GameObject* main_menu_enterObj;
GameObject* main_menu_background_1Obj;
GameObject* main_menu_background_2Obj;
GameObject* main_menu_background_3Obj;
GameObject* main_menu_background_4Obj;
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
Bar displacementBarLeft;
Bar displacementBarMiddle;
Bar displacementBarRight;

Bar powerBar;
Grenade grenade;
GameObject* explosion;

// Bar powerBarLeft;
// Bar powerBarMiddle;
// Bar powerBarRight;




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

GameObject* grenade_angle_arrow;


GameState* game_state_ptr;
Character* team_a[NUM_CHARACTERS_PER_TEAM];
Character* team_b[NUM_CHARACTERS_PER_TEAM];

void startGame() {
    initializeCharacter(&player_a0, 100 + PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_a0_idle, &player_a0_leftmovement,
                        &player_a0_rightmovement, &player_a0_jump_left, &player_a0_jump_right, 'a', 0);
    initializeCharacter(&player_a1, 150 + PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_a1_idle, &player_a1_leftmovement,
                        &player_a1_rightmovement, &player_a1_jump_left, &player_a1_jump_right, 'a', 1);
    initializeCharacter(&player_a2, 200 + PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_a2_idle, &player_a2_leftmovement,
                        &player_a2_rightmovement, &player_a2_jump_left, &player_a2_jump_right, 'a', 2);

    initializeCharacter(&player_b0, WORLD_WIDTH - 20 - PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_b0_idle, &player_b0_leftmovement,
                        &player_b0_rightmovement, &player_b0_jump_left, &player_b0_jump_right, 'b', 3);
    initializeCharacter(&player_b1, WORLD_WIDTH - 70 - PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_b1_idle, &player_b1_leftmovement,
                        &player_b1_rightmovement, &player_b1_jump_left, &player_b1_jump_right, 'b', 4);
    initializeCharacter(&player_b2, WORLD_WIDTH - 120 - PLAYER_WIDTH,
                        SCREEN_HEIGHT - BANNER_HEIGHT - PLAYER_HEIGHT - GROUND_HEIGHT, &player_b2_idle, &player_b2_leftmovement,
                        &player_b2_rightmovement, &player_b2_jump_left, &player_b2_jump_right, 'b', 5);

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

        //inital view setup
        currentView = team_a[game_state_ptr->character_turn_team_a]->characterView;
        updateScreenView();

        GameObject* jump_right1;
        GameObject* jump_right2;
        GameObject* jump_right3;
        if (game_state_ptr->character_turn_team_a == 0) {
            initializeGeneralObject(&jump_right1, player_a0_jump_right, 0, SCREEN_WIDTH-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right2, player_a0_jump_right, 0, SCREEN_WIDTH*2-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right3, player_a0_jump_right, 0, SCREEN_WIDTH*3-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else if (game_state_ptr->character_turn_team_a == 1) {
            initializeGeneralObject(&jump_right1, player_a1_jump_right, 0, SCREEN_WIDTH-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right2, player_a1_jump_right, 0, SCREEN_WIDTH*2-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right3, player_a1_jump_right, 0, SCREEN_WIDTH*3-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else if (game_state_ptr->character_turn_team_a == 2) {
            initializeGeneralObject(&jump_right1, player_a2_jump_right, 0, SCREEN_WIDTH-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right2, player_a2_jump_right, 0, SCREEN_WIDTH*2-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right3, player_a2_jump_right, 0, SCREEN_WIDTH*3-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }

        //-----------------------Stage 1 of turn, draw bottom bar here
        renderIn(moveOrStayBannerObj1);
        renderIn(moveOrStayBannerObj2);
        renderIn(moveOrStayBannerObj3);
        renderIn(jump_right1);
        renderIn(jump_right2);
        renderIn(jump_right3);
        printf("Team A's Turn\n");
        printf("Character %c%d's turn: Press 1 to move or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_a);
        end_turn = poll_move_or_stay_input();
        //-----------------------------



        if (!end_turn) {
            // Input handler logic for moving controls
            renderIn(movementControlBannerObj1);
            renderIn(movementControlBannerObj2);
            renderIn(movementControlBannerObj3);

            renderIn(jump_right1);
            renderIn(jump_right2);
            renderIn(jump_right3);

            //initializeBar(&displacementBarObj, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22);
            printf("Before initialize displacemetn bar\n");

            initializeBar(&displacementBarLeft, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22, 0);
            initializeBar(&displacementBarMiddle, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, SCREEN_WIDTH + 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22, 0);
            initializeBar(&displacementBarRight, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, SCREEN_WIDTH*2 + 202, SCREEN_HEIGHT - BANNER_HEIGHT + 22, 0);
            
            printf("After initialize displacemetn bar\n");
            int displacement = 0;
            int starting_x = *(team_a[game_state_ptr->character_turn_team_a]->x);
            bool character_fell_off_map = false;
            while (abs_double(displacement) < DISPLACEMENT_LIMIT) {
                bool flipped = false;
                char* control = single_poll_input();

                if(control == gameControls[6]){
                    break; //user pressed stay
                }

                moveCharacter(team_a[game_state_ptr->character_turn_team_a], control, NULL);

                //if characer falls off the map kill them
                if(*(team_a[game_state_ptr->character_turn_team_a]->y) > SCREEN_HEIGHT + 45){
                    team_a[game_state_ptr->character_turn_team_a]->prevState = team_a[game_state_ptr->character_turn_team_a]->state;
                    team_a[game_state_ptr->character_turn_team_a]->state = DEAD;
                    end_turn = true;
                    character_fell_off_map = true;
                    break;
                }

                    
                displacement = *(team_a[game_state_ptr->character_turn_team_a]->x) - starting_x;

                int currentCollisionArray[NUM_CHARACTERS_PER_TEAM * 2] = {0, 0, 0, 0, 0, 0};
                int ifCollision = 0;
                for (int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++) {
                    // Team A Consideration
                    if (team_a[game_state_ptr->character_turn_team_a] != team_a[i]) { // Shouldn't collide with itself
                        if (checkCollision_Characters(team_a[game_state_ptr->character_turn_team_a], team_a[i])) {
                            ifCollision = 1;
                            currentCollisionArray[i] = 1;
                            
                        }
                    }
                    // Team B Consideration
                    if (checkCollision_Characters(team_a[game_state_ptr->character_turn_team_a], team_b[i])) {
                        ifCollision = 1;
                        currentCollisionArray[i + NUM_CHARACTERS_PER_TEAM] = 1;
                        
                    }    
                }

                if (ifCollision == 0) {
                    // Remove all instances within the linked lists
                    drawCharacter(team_a[game_state_ptr->character_turn_team_a], false);
                }
                else {
                    // currentCollisionArray[game_state_ptr->character_turn_team_a] = 1;
                    for (int j = NUM_CHARACTERS_PER_TEAM*2 - 1; j >= 0 ; j--) {
                        if (j < NUM_CHARACTERS_PER_TEAM) {
                            if (currentCollisionArray[j]) {
                                for(int i = 0; i < team_a[j]->healthBar->lastRenderedPartition; i++){
                                    // printf("render out idx: %d\n", i);
                                    renderOut(team_a[j]->healthBar->barObj[i]);
                                }
                                removeCharacter(team_a[j]);
                            }
                        }
                        else {
                            if (currentCollisionArray[j]) {
                                for(int i = 0; i < team_b[j-3]->healthBar->lastRenderedPartition; i++){
                                    // printf("render out idx: %d\n", i);
                                    renderOut(team_b[j-3]->healthBar->barObj[i]);
                                }
                                removeCharacter(team_b[j-3]);
                            }
                        }
                    }

                    drawCharacter(team_a[game_state_ptr->character_turn_team_a], false);

                    for (int j = 0; j < NUM_CHARACTERS_PER_TEAM*2; j++) {
                        if (j < NUM_CHARACTERS_PER_TEAM) {
                            if (currentCollisionArray[j]) {
                                drawCharacter(team_a[j], false);
                            }
                        }
                        else {
                            if (currentCollisionArray[j]) {
                                drawCharacter(team_b[j-3], false);
                            }
                        }
                    }
                    
                }

                currentView = team_a[game_state_ptr->character_turn_team_a]->characterView;

                if(displacement < 0){
                    displacement *=-1;
                    flipped = true;
                }
                
                double ratio = (double) displacement / DISPLACEMENT_LIMIT;
                
                if(ratio > 1) ratio = 1;
                
                int num_partitions_filled = ratio * (double)NUM_DISPLACEMENT_BAR_PARTITIONS;
                
                
                
                if(num_partitions_filled < displacementBarLeft.lastRenderedPartition){
                    for(int i = displacementBarLeft.lastRenderedPartition; i >= num_partitions_filled; i--){
                        renderOut(displacementBarLeft.barObj[i]);
                        renderOut(displacementBarMiddle.barObj[i]);
                        renderOut(displacementBarRight.barObj[i]);
                    }
                }
                else if(num_partitions_filled > displacementBarLeft.lastRenderedPartition){
                    for(int i = displacementBarLeft.lastRenderedPartition; i < num_partitions_filled; i++){
                        renderIn(displacementBarLeft.barObj[i]);
                        renderIn(displacementBarMiddle.barObj[i]);
                        renderIn(displacementBarRight.barObj[i]);
                    }

                } 
                
                setLastRenderedPartition(&displacementBarLeft, num_partitions_filled);

                // Restore negative displacement
                if(flipped){
                    displacement*=-1;
                }
                
                
                wait_for_vsync();  // swap front and back buffers on VGA vertical sync
                
                
                updateScreenView();
            }

            // printf("Last partition rendered is: %d\n", displacementBar.lastRenderedPartition);
            resetBar(&displacementBarLeft, displacementBarLeft.lastRenderedPartition-1);
            resetBar(&displacementBarMiddle, displacementBarLeft.lastRenderedPartition-1);
            resetBar(&displacementBarRight, displacementBarLeft.lastRenderedPartition-1);

            resetArrowKeyReleaseFlags();
            byte1 = byte2 = byte3 = 0;
            //CURRENTLY just rendering on top of prev banner and displacememt bar

            if(!character_fell_off_map){
                //----------Stage 2 of turn, output bar for weapon or stay
                // updateHealthBar(team_a[game_state_ptr->character_turn_team_a]);
                printf("Character %c%d's turn: Press 1 to throw a grenade or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_a);
                renderIn(grenadeOrStayBannerObj1);
                renderIn(grenadeOrStayBannerObj2);
                renderIn(grenadeOrStayBannerObj3);

                renderIn(jump_right1);
                renderIn(jump_right2);
                renderIn(jump_right3);

                end_turn = poll_grenade_or_stay_input();
            }
            
        }

        if (!end_turn) {
            renderIn(grenadeControlBannerObj1);
            renderIn(grenadeControlBannerObj2);
            renderIn(grenadeControlBannerObj3);

            // MIGHT NEED TO CHANGE THIS HOW THE DISPLACEMENT BAR WORKS OF INTIALIZING THREE BARS AT ONCE
            if(currentView == LEFTVIEW){
                printf("LEFTVIEW\n");
                initializeBar(&powerBar, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 258, SCREEN_HEIGHT - BANNER_HEIGHT + 21, 0);
            } else if (currentView == MIDDLEVIEW){
                printf("MIDDLEVIEW\n");
                initializeBar(&powerBar, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 258 + SCREEN_WIDTH, SCREEN_HEIGHT - BANNER_HEIGHT + 21, 0);
            } else if (currentView == RIGHTVIEW){
                printf("RIGHTVIEW\n");
                initializeBar(&powerBar, &displacementbarpartition, DISPLACEMENTBARPARTITION_WIDTH, DISPLACEMENTBARPARTITION_HEIGHT, NUM_DISPLACEMENT_BAR_PARTITIONS, 258 + SCREEN_WIDTH*2, SCREEN_HEIGHT - BANNER_HEIGHT + 21, 0);
            }

            // grenade logic
            printf("call grenade logic controls!\n");
            bool grenadeLaunched = false;


            grenade_user_angle = 0;
            grenade_user_power = 0;
            double prev_grenade_user_angle = 0;

            int lookingRightBool = 1;

            // ADD LOGIC HERE
            if (team_a[game_state_ptr->character_turn_team_a]->state == RIGHTMOVEMENT || team_a[game_state_ptr->character_turn_team_a]->state == JUMPINGRIGHT) {
                lookingRightBool = 1;
            }
            else if (team_a[game_state_ptr->character_turn_team_a]->state == LEFTMOVEMENT || team_a[game_state_ptr->character_turn_team_a]->state == JUMPINGLEFT) {
                lookingRightBool = 0;                
            }
            
            else if (team_a[game_state_ptr->character_turn_team_a]->prevState == RIGHTMOVEMENT || team_a[game_state_ptr->character_turn_team_a]->prevState == JUMPINGRIGHT) {
                lookingRightBool = 1;
            }
            else if (team_a[game_state_ptr->character_turn_team_a]->prevState == RIGHTMOVEMENT || team_a[game_state_ptr->character_turn_team_a]->prevState == JUMPINGLEFT) {
                lookingRightBool = 0;                
            }
            else {
                lookingRightBool = 1; // Default to looking right
            }

            if (grenade_user_angle == 0) {
                initializeGeneralObject(&grenade_angle_arrow, &arrow_0, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                renderIn(grenade_angle_arrow);
            }

            while(!grenadeLaunched){
                char* control = grenade_control_input();
                //printf("%s\n", control);
                
                //NEED TO PUT logic for drawing arrow in this while loop
                if (prev_grenade_user_angle != grenade_user_angle) {
                    prev_grenade_user_angle = grenade_user_angle;
                    if (grenade_user_angle == 0) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_0, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_180, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                    }
                    else if (grenade_user_angle == 10) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_10, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_170, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                    }
                    else if (grenade_user_angle == 20) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_20, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_160, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);

                        }
                    }
                    else if (grenade_user_angle == 30) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_30, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_150, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                            
                        }
                    }
                    else if (grenade_user_angle == 40) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_40, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_140, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                    }
                    else if (grenade_user_angle == 50) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_50, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_130, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                            
                        }
                    }
                    else if (grenade_user_angle == 60) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_60, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_120, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                    }
                    else if (grenade_user_angle == 70) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_70, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_110, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                    }
                    else if (grenade_user_angle == 80) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        if (lookingRightBool == 1) {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_80, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                        else {
                            initializeGeneralObject(&grenade_angle_arrow, &arrow_100, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                        }
                    }
                    else if (grenade_user_angle == 90) {
                        renderOut(grenade_angle_arrow);
                        destroyGeneralObject(grenade_angle_arrow);
                        initializeGeneralObject(&grenade_angle_arrow, &arrow_90, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                    }
                    renderIn(grenade_angle_arrow);
                }

                if(control == gameControls[10]){ //if they released up grenade
                    if(grenade_user_angle != 90){
                        grenade_user_angle += 10;
                        printf("INPUT ANGLE: %lf\n", grenade_user_angle);
                        
                    }
                }
                else if(control == gameControls[12]){ // if they released down grenade
                    if(grenade_user_angle != 0){
                        grenade_user_angle -=10;
                        printf("INPUT ANGLE: %lf\n", grenade_user_angle);
                        

                    }
                }
                else if(control == gameControls[7]){
                    grenade_user_angle = 0; //reset angle when side switches
                    printf("logic to face right\n");
                    renderOut(grenade_angle_arrow);
                    destroyGeneralObject(grenade_angle_arrow);
                    initializeGeneralObject(&grenade_angle_arrow, &arrow_0, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                    renderIn(grenade_angle_arrow);
                    // team_a[game_state_ptr->character_turn_team_a]->state = RIGHTMOVEMENT;
                    // drawCharacter(team_a[game_state_ptr->character_turn_team_a], false);
                    lookingRightBool = 1;
                    
                }
                else if(control == gameControls[8]){
                    grenade_user_angle = 0; //reset angle when side switches
                    renderOut(grenade_angle_arrow);
                    destroyGeneralObject(grenade_angle_arrow);
                    initializeGeneralObject(&grenade_angle_arrow, &arrow_180, 0, *(team_a[game_state_ptr->character_turn_team_a]->x) - (PLAYER_WIDTH / 2), *(team_a[game_state_ptr->character_turn_team_a]->y), ARROW_WIDTH, ARROW_HEIGHT);
                    renderIn(grenade_angle_arrow);
                    printf("logic to face left\n");
                    lookingRightBool = 0;

                    
                }
                else if(control == gameControls[14]){ // User releases space bar to launch grenade
                    printf("The final grenade user power is: %lf\n", grenade_user_power);
                    grenade_user_power = 4;
                    printf("using ower of 4: %lf\n", grenade_user_power);
                    initializeGrenade(&grenade, *(team_a[game_state_ptr->character_turn_team_a]->x) + PLAYER_WIDTH/2, *(team_a[game_state_ptr->character_turn_team_a]->y) + PLATFORM_HEIGHT/2, &grenadeasset, grenade_user_angle, grenade_user_power, lookingRightBool);
                    resetBar(&powerBar, powerBar.lastRenderedPartition-1);
                    grenadeLaunched = true;
                    renderIn(grenade.grenadeObj); //initial render in
                    renderOut(grenade_angle_arrow);
                    destroyGeneralObject(grenade_angle_arrow);
                }

                if(!grenadeLaunched){
                    double ratio = grenade_user_power / NUM_DISPLACEMENT_BAR_PARTITIONS;
                    if(ratio > 1) ratio = 1;
                    int num_partitions_filled = ratio * (double)NUM_DISPLACEMENT_BAR_PARTITIONS;


                    
                    if(num_partitions_filled < powerBar.lastRenderedPartition){
                        for(int i = powerBar.lastRenderedPartition; i >= num_partitions_filled; i--){
                            renderOut(powerBar.barObj[i]);
                        }
                    }
                    else if(num_partitions_filled > powerBar.lastRenderedPartition){
                        for(int i = powerBar.lastRenderedPartition; i < num_partitions_filled; i++){
                            renderIn(powerBar.barObj[i]);
                        }

                    } 
                    setLastRenderedPartition(&powerBar, num_partitions_filled);
                }
            }
            byte1 = byte2 = byte3 = 0;

            //rendering loop for grenade once user controls are done
            // bool grenadeExploded = false;
            int grenade_explosion_count = 0;
            bool wentOffScreen = false;
            num_bounces = 0;
            while(grenade_explosion_count < GRENADE_EXPLOSION_COUNT_LIMIT && num_bounces < 3){
                renderOut(grenade.grenadeObj);
                updateGrenadePosition(&grenade);
                checkGrenadeGrounded(&grenade);

                if(*(grenade.grenadeObj->x) < -10 || *(grenade.grenadeObj->x) > WORLD_WIDTH + 10){
                    wentOffScreen = true;
                    break;
                }


                grenade_explosion_count +=1;
                // printf("---------\nX: %d\nY: %d\nVelocityX: %lf\nVelocityY: %lf\n--------\n\n", *(grenade.grenadeObj->x), *(grenade.grenadeObj->y), *(grenade.grenadeObj->velocityX), *(grenade.grenadeObj->velocityY));
                renderIn(grenade.grenadeObj);
                
                currentView = grenade.grenadeView;
                updateScreenView();

                wait_for_vsync();  // swap front and back buffers on VGA vertical sync
            }
            
            if(!wentOffScreen){

                printf("GRENADE EXPLOSION START\n");

                renderOut(grenade.grenadeObj);
                
                //logic for explosion animation and damage check logic
                initializeGeneralObject(&explosion, &explosionasset, 0, *(grenade.grenadeObj->x) - EXPLOSION_WIDTH/2.0, *(grenade.grenadeObj->y) - EXPLOSION_HEIGHT/2.0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT);
                renderIn(explosion);

                wait_for_vsync();
                
                int explosion_delay_count = 0;
                while(1){
                    renderOut(explosion);
                    if(explosion_delay_count > 10){
                        wait_for_vsync();
                        break;
                    }
                    renderIn(explosion);
                    wait_for_vsync();
                    explosion_delay_count++;
                }


                destroyGeneralObject(explosion);

                printf("GRENADE EXPLOSION DESTROYED\n");


                //logic for damage
                checkWithinBlastRadiusAndApplyDamage(&grenade, team_a, team_b);

                checkCharacterDeaths(); //set characters with 0 health to dead

                int numAffected = getNumAffectedByCollision();

                printf("NUM AFFECTED IS: %d\n", numAffected);

                //render out dead characters who were just affected by collision
                for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
                    if(team_a[i]->state == DEAD && team_a[i]->withinBlastRadiusBool == 1){
                        // do stuff
                        removeCharacter(team_a[i]);
                    }

                    if(team_b[i]->state == DEAD && team_b[i]->withinBlastRadiusBool == 1){
                        // do stuff
                        removeCharacter(team_b[i]);
                    }
                }


                // int knockback_count = 0;
                int count = 0;
                while(count != numAffected){ //if num affected == 0 it should never enter loop
                    count = 0;
                    for(int curr = 0; curr < NUM_CHARACTERS_PER_TEAM; curr++){
                        if(team_a[curr]->withinBlastRadiusBool == 1){
                            printf("A%d within radius and health is %d\n", curr, *(team_a[curr]->health));
                            
                            printf("A%d isGroundedBool is initially: %d\n", curr, team_a[curr]->isGroundedBool);
                            //if(team_a[curr]->isGroundedBool != 1){
                                checkGrounded(team_a[curr]);
                            //}
                            printf("A%d isGroundedBool afterwards is: %d\n", curr, team_a[curr]->isGroundedBool);

                            if(team_a[curr]->state == DEAD || (team_a[curr]->isGroundedBool == 1 && team_a[curr]->explosionDisplacement >= MAX_X_EXPLOSION_DISPLACEMENT)){
                                printf("breaking condition displacement is: %d\n", team_a[curr]->explosionDisplacement);
                                count +=1;
                            }
                            else{
                                bool characterLeft = isCharacterLeftOfGrenade(&grenade, team_a[curr]);
                                knockbackCharacter(team_a[curr], characterLeft, team_a[curr]->isGroundedBool);
                                printf("current displacement is: %d\n", team_a[curr]->explosionDisplacement);

                                //check if fell off map
                                if(*(team_a[curr]->y) > SCREEN_HEIGHT + 45){
                                    team_a[curr]->prevState = team_a[curr]->state;
                                    team_a[curr]->state = DEAD;
                                }



                            }


                            int currentCollisionArray[NUM_CHARACTERS_PER_TEAM * 2] = {0, 0, 0, 0, 0, 0};
                            int ifCollision = 0;
                            for (int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++) {
                                // Team A Consideration
                                if (team_a[curr] != team_a[i]) { // Shouldn't collide with itself
                                    if (checkCollision_Characters(team_a[curr], team_a[i])) {
                                        ifCollision = 1;
                                        currentCollisionArray[i] = 1;
                                        
                                    }
                                }
                                // Team B Consideration
                                if (checkCollision_Characters(team_a[curr], team_b[i])) {
                                    ifCollision = 1;
                                    currentCollisionArray[i + NUM_CHARACTERS_PER_TEAM] = 1;
                                    
                                }    
                            }

                            if (ifCollision == 0) {
                                // Remove all instances within the linked lists
                                drawCharacter(team_a[curr], false);
                            }
                            else {
                                // currentCollisionArray[game_state_ptr->character_turn_team_a] = 1;
                                for (int j = NUM_CHARACTERS_PER_TEAM*2 - 1; j >= 0 ; j--) {
                                    if (j < NUM_CHARACTERS_PER_TEAM) {
                                        if (currentCollisionArray[j]) {
                                            for(int i = 0; i < team_a[j]->healthBar->lastRenderedPartition; i++){
                                                // printf("render out idx: %d\n", i);
                                                renderOut(team_a[j]->healthBar->barObj[i]);
                                            }
                                            removeCharacter(team_a[j]);
                                        }
                                    }
                                    else {
                                        if (currentCollisionArray[j]) {
                                            for(int i = 0; i < team_b[j-3]->healthBar->lastRenderedPartition; i++){
                                                // printf("render out idx: %d\n", i);
                                                renderOut(team_b[j-3]->healthBar->barObj[i]);
                                            }
                                            removeCharacter(team_b[j-3]);
                                        }
                                    }
                                }

                                drawCharacter(team_a[curr], false);

                                for (int j = 0; j < NUM_CHARACTERS_PER_TEAM*2; j++) {
                                    if (j < NUM_CHARACTERS_PER_TEAM) {
                                        if (currentCollisionArray[j]) {
                                            drawCharacter(team_a[j], false);
                                        }
                                    }
                                    else {
                                        if (currentCollisionArray[j]) {
                                            drawCharacter(team_b[j-3], false);
                                        }
                                    }
                                }
                                
                            }
                        }
                    } // End of for loop to iterate through team a

                
                    for(int curr = 0; curr < NUM_CHARACTERS_PER_TEAM; curr++){
                        if(team_b[curr]->withinBlastRadiusBool == 1){
                            printf("B%d within radius and health is %d\n", curr, *(team_b[curr]->health));

                            if(team_b[curr]->isGroundedBool != 1){
                                checkGrounded(team_b[curr]);
                            }
                            if(team_b[curr]->state == DEAD || (team_b[curr]->isGroundedBool == 1 && team_b[curr]->explosionDisplacement >= MAX_X_EXPLOSION_DISPLACEMENT)){
                                count +=1;
                            }
                            else{
                                bool characterLeft = isCharacterLeftOfGrenade(&grenade, team_b[curr]);
                                knockbackCharacter(team_b[curr], characterLeft, team_b[curr]->isGroundedBool);

                                //check if fell off map
                                if(*(team_b[curr]->y) > SCREEN_HEIGHT + 45){
                                    team_b[curr]->prevState = team_b[curr]->state;
                                    team_b[curr]->state = DEAD;
                                }

                            }

                            // bool characterLeft = isCharacterLeftOfGrenade(&grenade, team_b[curr]);
                            // knockbackCharacter(team_b[curr], characterLeft);

                            int currentCollisionArray[NUM_CHARACTERS_PER_TEAM * 2] = {0, 0, 0, 0, 0, 0};
                            int ifCollision = 0;
                            for (int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++) {
                                // Team A Consideration
                                if (checkCollision_Characters(team_b[curr], team_a[i])) {
                                    ifCollision = 1;
                                    currentCollisionArray[i] = 1;
                                }

                                // Team B Consideration
                                if (team_b[curr] != team_b[i]) { // Shouldn't collide with itself
                                    if (checkCollision_Characters(team_b[curr], team_b[i])) {
                                        ifCollision = 1;
                                        currentCollisionArray[i + NUM_CHARACTERS_PER_TEAM] = 1;
                                    }
                                }
                            }
                            if (ifCollision == 0) {
                                // Remove all instances within the linked lists
                                drawCharacter(team_b[curr], false);
                            }
                            else {
                                // currentCollisionArray[game_state_ptr->character_turn_team_a] = 1;
                                for (int j = NUM_CHARACTERS_PER_TEAM*2 - 1; j >= 0 ; j--) {
                                    if (j < NUM_CHARACTERS_PER_TEAM) {
                                        if (currentCollisionArray[j]) {
                                            for(int i = 0; i < team_a[j]->healthBar->lastRenderedPartition; i++){
                                                // printf("render out idx: %d\n", i);
                                                renderOut(team_a[j]->healthBar->barObj[i]);
                                            }
                                            removeCharacter(team_a[j]);
                                        }
                                    }
                                    else {
                                        if (currentCollisionArray[j]) {
                                            for(int i = 0; i < team_b[j-3]->healthBar->lastRenderedPartition; i++){
                                                // printf("render out idx: %d\n", i);
                                                renderOut(team_b[j-3]->healthBar->barObj[i]);
                                            }
                                            removeCharacter(team_b[j-3]);
                                        }
                                    }
                                }

                                drawCharacter(team_b[curr], false);


                                for (int j = 0; j < NUM_CHARACTERS_PER_TEAM*2; j++) {
                                    if (j < NUM_CHARACTERS_PER_TEAM) {
                                        if (currentCollisionArray[j]) {
                                            drawCharacter(team_a[j], false);
                                        }
                                    }
                                    else {
                                        if (currentCollisionArray[j]) {
                                            drawCharacter(team_b[j-3], false);
                                        }
                                    }
                                }
                                
                            }
                        }
                    } //end of for loop to iterate through team b

                    // knockback_count++;
                    wait_for_vsync();
                }



                destroyGrenade(&grenade);

                //reset within radius bool values and velocities from knockback
                for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
                    if(team_a[i]->withinBlastRadiusBool == 1){
                        team_a[i]->withinBlastRadiusBool = 0;
                        *(team_a[i]->velocityX) = 0;
                        team_a[i]->explosionDisplacement = 0;
                    }

                    if(team_b[i]->withinBlastRadiusBool == 1){
                        team_b[i]->withinBlastRadiusBool = 0;
                        *(team_b[i]->velocityX) = 0;
                        team_b[i]->explosionDisplacement = 0;
                    }
                }


            }
            else{ //if the grenade went off the screen
                printf("GRENADE WENT OFF SCREEN!\n");
                wait_for_vsync();
                destroyGrenade(&grenade);
            }


            


        }

        // END TURN LOGIC
        game_state_ptr->character_turn_team_a = getCharacterIndexForNextTurn(team_a, game_state_ptr->character_turn_team_a);
        game_state_ptr->team_turn = 'b';

        for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
            if(team_a[i]->state == DEAD){
                printf("A%d is DEAD\n", i);
            }
            else{
                printf("A%d is ALIVE\n", i);
            }
        }

        for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
            if(team_b[i]->state == DEAD){
                printf("B%d is DEAD\n", i);
            }
            else{
                printf("B%d is ALIVE\n", i);
            }
        }

        char game_result = checkWinCondition();
        printf("\nCurrent game result is %c\n", game_result);
    }
    // Team B's Turn (DISPLACEMENT BAR DOES NOT WORK FOR TEAM B CHARACER YET, WILL FIX IT TMRW)
    else {
        //inital view setup
        currentView = team_b[game_state_ptr->character_turn_team_b]->characterView;
        updateScreenView();
        
        GameObject* jump_right1;
        GameObject* jump_right2;
        GameObject* jump_right3;
        if (game_state_ptr->character_turn_team_b == 0) {
            initializeGeneralObject(&jump_right1, player_b0_jump_right, 0, SCREEN_WIDTH-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right2, player_b0_jump_right, 0, SCREEN_WIDTH*2-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right3, player_b0_jump_right, 0, SCREEN_WIDTH*3-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else if (game_state_ptr->character_turn_team_b == 1) {
            initializeGeneralObject(&jump_right1, player_b1_jump_right, 0, SCREEN_WIDTH-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right2, player_b1_jump_right, 0, SCREEN_WIDTH*2-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right3, player_b1_jump_right, 0, SCREEN_WIDTH*3-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        else if (game_state_ptr->character_turn_team_b == 2) {
            initializeGeneralObject(&jump_right1, player_b2_jump_right, 0, SCREEN_WIDTH-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right2, player_b2_jump_right, 0, SCREEN_WIDTH*2-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
            initializeGeneralObject(&jump_right3, player_b2_jump_right, 0, SCREEN_WIDTH*3-10 - PLAYER_WIDTH, SCREEN_HEIGHT - 5 - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
        }
        //-----------------------Stage 1 of turn, draw bottom bar here
        renderIn(moveOrStayBannerObj1);
        renderIn(moveOrStayBannerObj2);
        renderIn(moveOrStayBannerObj3);
        renderIn(jump_right1);
        renderIn(jump_right2);
        renderIn(jump_right3);
        printf("Team B's Turn\n");
        printf("Character %c%d's turn: Press 1 to move or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_b);
        end_turn = poll_move_or_stay_input();
        //-----------------------------



        if (!end_turn) {
            // Input handler logic for moving controls
            renderIn(movementControlBannerObj1);
            renderIn(movementControlBannerObj2);
            renderIn(movementControlBannerObj3);
            renderIn(jump_right1);
            renderIn(jump_right2);
            renderIn(jump_right3);
            
            int displacement = 0;
            int starting_x = *(team_b[game_state_ptr->character_turn_team_b]->x);
            while (abs_double(displacement) < DISPLACEMENT_LIMIT) {
                bool flipped = false;
                char* control = single_poll_input();

                if(control == gameControls[6]){
                    break; //user pressed stay
                }

                moveCharacter(team_b[game_state_ptr->character_turn_team_b], control,
                            NULL);
                
                displacement = *(team_b[game_state_ptr->character_turn_team_b]->x) - starting_x;

    
                int currentCollisionArray[NUM_CHARACTERS_PER_TEAM * 2] = {0, 0, 0, 0, 0, 0};
                int ifCollision = 0;
                for (int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++) {
                    // Team A Consideration
                    if (checkCollision_Characters(team_b[game_state_ptr->character_turn_team_b], team_a[i])) {
                        ifCollision = 1;
                        currentCollisionArray[i] = 1;
                    }

                    // Team B Consideration
                    if (team_b[game_state_ptr->character_turn_team_b] != team_b[i]) { // Shouldn't collide with itself
                        if (checkCollision_Characters(team_b[game_state_ptr->character_turn_team_b], team_b[i])) {
                            ifCollision = 1;
                            currentCollisionArray[i + NUM_CHARACTERS_PER_TEAM] = 1;
                        }
                    }
                }
                if (ifCollision == 0) {
                    // Remove all instances within the linked lists
                    drawCharacter(team_b[game_state_ptr->character_turn_team_b], false);
                }
                else {
                    // currentCollisionArray[game_state_ptr->character_turn_team_a] = 1;
                    for (int j = NUM_CHARACTERS_PER_TEAM*2 - 1; j >= 0 ; j--) {
                        if (j < NUM_CHARACTERS_PER_TEAM) {
                            if (currentCollisionArray[j]) {
                                for(int i = 0; i < team_a[j]->healthBar->lastRenderedPartition; i++){
                                    // printf("render out idx: %d\n", i);
                                    renderOut(team_a[j]->healthBar->barObj[i]);
                                }
                                removeCharacter(team_a[j]);
                            }
                        }
                        else {
                            if (currentCollisionArray[j]) {
                                for(int i = 0; i < team_b[j-3]->healthBar->lastRenderedPartition; i++){
                                    // printf("render out idx: %d\n", i);
                                    renderOut(team_b[j-3]->healthBar->barObj[i]);
                                }
                                removeCharacter(team_b[j-3]);
                            }
                        }
                    }

                    drawCharacter(team_b[game_state_ptr->character_turn_team_b], false);


                    for (int j = 0; j < NUM_CHARACTERS_PER_TEAM*2; j++) {
                        if (j < NUM_CHARACTERS_PER_TEAM) {
                            if (currentCollisionArray[j]) {
                                drawCharacter(team_a[j], false);
                            }
                        }
                        else {
                            if (currentCollisionArray[j]) {
                                drawCharacter(team_b[j-3], false);
                            }
                        }
                    }
                    
                }

                currentView = team_b[game_state_ptr->character_turn_team_b]->characterView;

                if(displacement < 0){
                    displacement *=-1;
                    flipped = true;
                }

                double ratio = (double)displacement / DISPLACEMENT_LIMIT;

                if(ratio > 1) ratio = 1;

                int num_partitions_filled = ratio * (double)NUM_DISPLACEMENT_BAR_PARTITIONS;

                
                if(num_partitions_filled < displacementBarLeft.lastRenderedPartition){
                    for(int i = displacementBarLeft.lastRenderedPartition; i >= num_partitions_filled; i--){
                        renderOut(displacementBarLeft.barObj[i]);
                        renderOut(displacementBarMiddle.barObj[i]);
                        renderOut(displacementBarRight.barObj[i]);
                    }
                }
                else if(num_partitions_filled > displacementBarLeft.lastRenderedPartition){
                    for(int i = displacementBarLeft.lastRenderedPartition; i < num_partitions_filled; i++){
                            renderIn(displacementBarLeft.barObj[i]);
                            renderIn(displacementBarMiddle.barObj[i]);
                            renderIn(displacementBarRight.barObj[i]);
                    }

                } 

                setLastRenderedPartition(&displacementBarLeft, num_partitions_filled);

                // Restore negative displacement
                if(flipped){
                    displacement*=-1;
                }

                
                
                wait_for_vsync();  // swap front and back buffers on VGA vertical sync
                
                updateScreenView();

            }
            

            resetBar(&displacementBarLeft, displacementBarLeft.lastRenderedPartition-1);
            resetBar(&displacementBarMiddle, displacementBarLeft.lastRenderedPartition-1);
            resetBar(&displacementBarRight, displacementBarLeft.lastRenderedPartition-1);
            resetArrowKeyReleaseFlags();
            byte1 = byte2 = byte3 = 0;
            //CURRENTLY just rendering on top of prev banner and displacememt bar

            //----------Stage 2 of turn, output bar for weapon or stay
            printf("Character %c%d's turn: Press 1 to throw a grenade or 2 to stay\n", game_state_ptr->team_turn, game_state_ptr->character_turn_team_b);
            renderIn(grenadeOrStayBannerObj1);
            renderIn(grenadeOrStayBannerObj2);
            renderIn(grenadeOrStayBannerObj3);
            renderIn(jump_right1);
            renderIn(jump_right2);
            renderIn(jump_right3);
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
  
int getCharacterIndexForNextTurn(struct Character* team_array[NUM_CHARACTERS_PER_TEAM], int current_character_turn_index) {
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
      if (team_a[i]->state == DEAD) {
        dead_count_a++;
      }
  
      if (team_b[i]->state == DEAD) {
        dead_count_b++;
      }
    }
  
    if (dead_count_a < NUM_CHARACTERS_PER_TEAM &&
        dead_count_b < NUM_CHARACTERS_PER_TEAM) {
      return 'i';
    } else if (dead_count_a == NUM_CHARACTERS_PER_TEAM && dead_count_b == NUM_CHARACTERS_PER_TEAM) {  
        game_state_ptr->game_running = false;
        return 't';
    } else if (dead_count_a == NUM_CHARACTERS_PER_TEAM) {
        game_state_ptr->game_running = false;
        return 'l';  // 'l' means team A lost
    } else if (dead_count_b == NUM_CHARACTERS_PER_TEAM) {
        game_state_ptr->game_running = false;
        return 'w';  // 'w' means team A won
    } else {
      return 'x';  // Unexpected case
    }
  }
  
void updateScreenView(){
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

void checkCharacterDeaths(){
    for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
        if(team_a[i]->state == DEAD){
            continue;
        }
        else{
            if(*(team_a[i]->health) <= 0){
                team_a[i]->prevState = team_a[i]->state;
                team_a[i]->state = DEAD;
            }
        }
    }

    for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
        if(team_b[i]->state == DEAD){
            continue;
        }
        else{
            if(*(team_b[i]->health) <= 0){
                team_b[i]->prevState = team_b[i]->state;
                team_b[i]->state = DEAD;
            }
        }
    }
}

int getNumAffectedByCollision(){
    //includes dead characters
    int count = 0;
    for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
        if(team_a[i]->withinBlastRadiusBool == 1){
            count+=1;
        }
        if(team_b[i]->withinBlastRadiusBool == 1){
            count+=1;
        }
    }

    return count;

}