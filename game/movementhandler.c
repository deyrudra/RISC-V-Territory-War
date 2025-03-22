#include "objecthandler.h"
#include "movementhandler.h"
#include <stdio.h>

void initializeCharacter(Character *character, int *idleCharAsset, int *walkLeftCharAsset, int *walkRightCharAsset, int *jumpCharAsset, int *idlePrevData, int *walkLeftPrevData, int *walkRightPrevData, int *jumpPrevData) {
    character->x = malloc(sizeof(int));
    character->y = malloc(sizeof(int));
    character->velocityX = malloc(sizeof(double));
    character->velocityY = malloc(sizeof(double));
    character->collidable = malloc(sizeof(int));
    character->state = IDLE;
    character->prevState = UNKNOWN;
    
    *(character->collidable) = 1;
    *(character->x) = SCREEN_WIDTH/2 - PLAYER_WIDTH;
    *(character->y) = SCREEN_HEIGHT/2 - PLAYER_HEIGHT;
    *(character->velocityX) = 0;
    *(character->velocityY) = 0;
    
    GameObject * idleCharacterObj = (GameObject *)malloc(sizeof(GameObject));
    character->idleCharacter = idleCharacterObj;
    character->idleCharacter->asset = idleCharAsset;
    character->idleCharacter->height = PLAYER_HEIGHT;
    character->idleCharacter->width = PLAYER_WIDTH;
    character->idleCharacter->prevPixelData = idlePrevData;
    character->idleCharacter->x = malloc(sizeof(int));  // Allocate memory
    character->idleCharacter->y = malloc(sizeof(int));  // Allocate memory
    character->idleCharacter->velocityX = malloc(sizeof(double));  // Allocate memory
    character->idleCharacter->velocityY = malloc(sizeof(double));  // Allocate memory
    character->idleCharacter->collidable = malloc(sizeof(int));  // Allocate memory

    GameObject * walkLeftCharacterObj = (GameObject *)malloc(sizeof(GameObject));
    character->walkLeftCharacter = walkLeftCharacterObj;
    character->walkLeftCharacter->asset = walkLeftCharAsset;
    character->walkLeftCharacter->height = PLAYER_HEIGHT;
    character->walkLeftCharacter->width = PLAYER_WIDTH;
    character->walkLeftCharacter->prevPixelData = walkLeftPrevData;
    character->walkLeftCharacter->x = malloc(sizeof(int));  // Allocate memory
    character->walkLeftCharacter->y = malloc(sizeof(int));  // Allocate memory
    character->walkLeftCharacter->velocityX = malloc(sizeof(double));  // Allocate memory
    character->walkLeftCharacter->velocityY = malloc(sizeof(double));  // Allocate memory
    character->walkLeftCharacter->collidable = malloc(sizeof(int));  // Allocate memory
    
    GameObject * walkRightCharacterObj = (GameObject *)malloc(sizeof(GameObject));
    character->walkRightCharacter = walkRightCharacterObj;
    character->walkRightCharacter->asset = walkRightCharAsset;
    character->walkRightCharacter->height = PLAYER_HEIGHT;
    character->walkRightCharacter->width = PLAYER_WIDTH;
    character->walkRightCharacter->prevPixelData = walkRightPrevData;
    character->walkRightCharacter->x = malloc(sizeof(int));  // Allocate memory
    character->walkRightCharacter->y = malloc(sizeof(int));  // Allocate memory
    character->walkRightCharacter->velocityX = malloc(sizeof(double));  // Allocate memory
    character->walkRightCharacter->velocityY = malloc(sizeof(double));  // Allocate memory
    character->walkRightCharacter->collidable = malloc(sizeof(int));  // Allocate memory
    
    GameObject * jumpingCharacterObj = (GameObject *)malloc(sizeof(GameObject));
    character->jumpingCharacter = jumpingCharacterObj;
    character->jumpingCharacter->asset = jumpCharAsset;
    character->jumpingCharacter->height = PLAYER_HEIGHT;
    character->jumpingCharacter->width = PLAYER_WIDTH;
    character->jumpingCharacter->prevPixelData = jumpPrevData;
    character->jumpingCharacter->x = malloc(sizeof(int));  // Allocate memory
    character->jumpingCharacter->y = malloc(sizeof(int));  // Allocate memory
    character->jumpingCharacter->velocityX = malloc(sizeof(double));  // Allocate memory
    character->jumpingCharacter->velocityY = malloc(sizeof(double));  // Allocate memory
    character->jumpingCharacter->collidable = malloc(sizeof(int));  // Allocate memory
    
    // printf("Test: %d\n", *character->idleCharacter->x);
    character->idleCharacter->x = character->x;
    character->idleCharacter->y = character->y;
    character->idleCharacter->velocityX = character->velocityX;
    character->idleCharacter->velocityY = character->velocityY;
    character->idleCharacter->collidable = character->collidable;
    character->walkLeftCharacter->x = character->x;
    character->walkLeftCharacter->y = character->y;
    character->walkLeftCharacter->velocityX = character->velocityX;
    character->walkLeftCharacter->velocityY = character->velocityY;
    character->walkLeftCharacter->collidable = character->collidable;
    character->walkRightCharacter->x = character->x;
    character->walkRightCharacter->y = character->y;
    character->walkRightCharacter->velocityX = character->velocityX;
    character->walkRightCharacter->velocityY = character->velocityY;
    character->walkRightCharacter->collidable = character->collidable;
    character->jumpingCharacter->x = character->x;
    character->jumpingCharacter->y = character->y;
    character->jumpingCharacter->velocityX = character->velocityX;
    character->jumpingCharacter->velocityY = character->velocityY;
    character->jumpingCharacter->collidable = character->collidable;
}

// Function to handle character movement
void moveCharacter(Character *character, char* direction){
    if (character == NULL) {
        printf("Character does not exist...\n");
    }
    else {
        // Calling Gravity (y-friction) and Air Drag (x-friction) Functions
        gravityCharacter(character);
        airdragCharacter(character);

        // Saving Prevstate
        character->prevState = character->state;
    
        // Setting Character States (for assets) based on movement input.
        if (strcmp(direction, gameControls[0]) == 0) { // Checking for move_left
            character->state = LEFTMOVEMENT;
        }
        else if (strcmp(direction, gameControls[1]) == 0) { // Checking for move_right
            character->state = RIGHTMOVEMENT;
        }
        else if (strcmp(direction, gameControls[2] == 0)) { // Checking for move_jump
            character->state = JUMPING;
            *(character->velocityY) = 10.0;
        }

        // // Setting Character States based on Velocity (for idle asset)
        // if (*(character->velocityX) == 0) {
        //     character->state = IDLE;
        // }
        // if (*(character->velocityY) != 0) {
        //     character->state = JUMPING;
        // }

    }
}

void drawCharacter(Character *character){
    // If character state didn't change, then don't do nothing.

    // Rendering out Old Asset
    if (character->prevState == IDLE) {
        renderOut(character->idleCharacter);
    }
    else if (character->prevState == LEFTMOVEMENT) {
        renderOut(character->walkLeftCharacter);
    }
    else if (character->prevState == RIGHTMOVEMENT) {
        renderOut(character->walkRightCharacter);
    }
    else if (character->prevState == JUMPING) {
        renderOut(character->jumpingCharacter);
    }

    // Rendering in New Asset
    if (character->state == IDLE) {
        renderIn(character->idleCharacter);
    }
    else if (character->state == LEFTMOVEMENT) {
        renderIn(character->walkLeftCharacter);
    }
    else if (character->state == RIGHTMOVEMENT) {
        renderIn(character->walkRightCharacter);
    }
    else if (character->prevState == JUMPING) {
        renderIn(character->jumpingCharacter);
    }



}

void gravityCharacter(Character *character) {
    // If grounded stop.
    *(character->velocityY) += GRAVITY * DELTATIME;
}

void airdragCharacter(Character *character) {
    // if ((*(character->velocityX) + AIRDRAG * DELTATIME) >= 0) {
    //     *(character->velocityX) += AIRDRAG * DELTATIME;
    // }
    // else {

    // }
}