#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "inputhandler.h"
#include "movementhandler.h"
#include "loadassets.h"
#include <stdbool.h>
#include "renderhandler.h"
#include "platformhandler.h"
#include "backgroundhandler.h"
#include "barhandler.h"
#include "grenadehandler.h"
#include <stdio.h>

#define NUM_CHARACTERS_PER_TEAM 3
#define DISPLACEMENT_LIMIT 320
#define MAX_NUM_CHARACTER_COLLISION_LISTS NUM_CHARACTERS_PER_TEAM


// Global Game Objects
extern GameObject* mainMenuTitleObj;
extern GameObject* main_menu_enterObj;
extern GameObject* main_menu_background_1Obj;
extern GameObject* main_menu_background_2Obj;
extern GameObject* main_menu_background_3Obj;
extern GameObject* main_menu_background_4Obj;
extern GameObject* platformObj;
extern GameObject* moveOrStayBannerObj1;
extern GameObject* emptyBannerObj1;
extern GameObject* grenadeOrStayBannerObj1;
extern GameObject* movementControlBannerObj1;
extern GameObject* moveOrStayBannerObj2;
extern GameObject* emptyBannerObj2;
extern GameObject* grenadeOrStayBannerObj2;
extern GameObject* movementControlBannerObj2;
extern GameObject* moveOrStayBannerObj3;
extern GameObject* emptyBannerObj3;
extern GameObject* grenadeOrStayBannerObj3;
extern GameObject* movementControlBannerObj3;
extern GameObject* grenadeControlBannerObj1;
extern GameObject* grenadeControlBannerObj2;
extern GameObject* grenadeControlBannerObj3;



// Game state structure
typedef struct GameState {
    char team_turn; // 'a' for team A, 'b' for team B
    int character_turn_team_a;
    int character_turn_team_b;
    bool game_running;
} GameState;

// Global game objects
extern Character player_a0;
extern Character player_a1;
extern Character player_a2;
extern Character player_b0;
extern Character player_b1;
extern Character player_b2;

extern Platform platform1;

// Global game state
extern GameState* game_state_ptr;
extern Character* team_a[NUM_CHARACTERS_PER_TEAM];
extern Character* team_b[NUM_CHARACTERS_PER_TEAM];

// Function declarations
void startGame();
void handle_team_turn();
void initializeGame();
int getCharacterIndexForNextTurn(struct Character* team_array[NUM_CHARACTERS_PER_TEAM], 
                                int current_character_turn_index);
char checkWinCondition();

void updateScreenView();
//void initializeBar(GameObject*** barObj, int* asset, int width, int height, int num_partitions, int start_x, int start_y);
// void drawBar(GameObject** bar_obj);

#endif // GAMELOGIC_H