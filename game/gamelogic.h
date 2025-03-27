#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "inputhandler.h"
#include "movementhandler.h"
#include "loadassets.h"
#include <stdbool.h>
#include "renderhandler.h"
#include "platformhandler.h"
#include "backgroundhandler.h"

#define NUM_CHARACTERS_PER_TEAM 3
#define DISPLACEMENT_LIMIT 100
#define NUM_DISPLACEMENT_BAR_PARTITIONS 25

// Global Game Objects
extern GameObject* mainMenuTitleObj;
extern GameObject* platformObj;
extern GameObject* moveOrStayBannerObj;
extern GameObject* grenadeOrStayBannerObj;
extern GameObject* movementControlBannerObj;

// Game state structure
typedef struct GameState {
    char team_turn; // 'a' for team A, 'b' for team B
    int character_turn_team_a;
    int character_turn_team_b;
    bool game_running;
} GameState;

// Global game objects
extern Character player_a0;
extern Character player_b0;
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
void initializeBar(GameObject*** barObj, int* asset, int width, int height, int num_partitions, int start_x, int start_y);
// void drawBar(GameObject** bar_obj);

#endif // GAMELOGIC_H