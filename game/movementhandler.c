#include "movementhandler.h"

int move_right_released = 1;
int move_left_released = 1;

double abs_double(double value) {
    if (value >= 0) {
        return value;
    }
    else {
        return -value;
    }
}

void initializeCharacter(Character *character, int x, int y, int *idleCharAsset, int *walkLeftCharAsset, int *walkRightCharAsset, int *jumpCharAsset) {
    // Replace all local array declarations with malloc calls
    int* walkLeftPrevData = malloc(sizeof(int) * LEFTMOVEMENT_WIDTH * LEFTMOVEMENT_HEIGHT);
    int* walkRightPrevData = malloc(sizeof(int) * RIGHTMOVEMENT_WIDTH * RIGHTMOVEMENT_HEIGHT);
    int* jumpPrevData = malloc(sizeof(int) * JUMP_WIDTH * JUMP_HEIGHT);
    int* idlePrevData = malloc(sizeof(int) * IDLE_WIDTH * IDLE_HEIGHT);
    int* leftbootPrev = malloc(sizeof(int) * LEFTBOOT_WIDTH * LEFTBOOT_HEIGHT);
    int* rightbootPrev = malloc(sizeof(int) * LEFTBOOT_WIDTH * LEFTBOOT_HEIGHT);
    int* deadPrev = malloc(sizeof(int) * DEAD_WIDTH * DEAD_HEIGHT);
    
    character->x = malloc(sizeof(int));
    character->y = malloc(sizeof(int));
    character->velocityX = malloc(sizeof(double));
    character->velocityY = malloc(sizeof(double));
    character->collidable = malloc(sizeof(int));
    character->health = malloc(sizeof(int));
    character->state = IDLE;
    character->isGroundedBool = 0;
    character->width = PLAYER_WIDTH;
    character->height = PLAYER_HEIGHT;
            
    *(character->collidable) = 1;
    *(character->x) = x;
    *(character->y) = y;
    *(character->velocityX) = 0;
    *(character->velocityY) = 0;
    *(character->health) = 0;
    
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
void moveCharacter(Character *character, char* direction, int* distance_travelled){
    if (character == NULL) {
        printf("Character does not exist...\n");
    }
    else {
        //Test
        // Calling Gravity (y-friction) and Air Drag (x-friction) Functions
        // gravityCharacter(character);
        // airdragCharacter(character);

        printf("HEY\n");

        // Saving Prevstate
        character->prevState = character->state;
        
        // Setting Character States (for assets) based on movement input.
        if ((strcmp(direction, gameControls[0]) == 0) || (move_left_released == 0)) { // Checking for move_left
            move_left_released = 0;
            character->state = LEFTMOVEMENT;
            horizontalAcceleration(character, 0);
            *(character->x) = *(character->x) + *(character->velocityX);
            *distance_travelled += *character->velocityX;

        }
        if ((strcmp(direction, gameControls[1]) == 0) || (move_right_released == 0)) { // Checking for move_right
            move_right_released = 0;
            character->state = RIGHTMOVEMENT;
            horizontalAcceleration(character, 1);
            *(character->x) = *(character->x) + *(character->velocityX);
            *distance_travelled += *character->velocityX;

        }
        if (strcmp(direction, gameControls[2]) == 0) { // Checking for move_jump
            character->state = JUMPING;
            *(character->velocityY) = -3.0;
            character->isGroundedBool = 0;
            
        }
        if (strcmp(direction, gameControls[3]) == 0) { // Checking for move_left_stop
            *(character->velocityX) = 0;
            move_left_released = 1;
            
        }
        if (strcmp(direction, gameControls[4]) == 0) { // Checking for move_right_stop
            *(character->velocityX) = 0;
            move_right_released = 1;
            
        }

        
    }

    // Setting Character States based on Velocity (for idle asset)
    if ((((int) *(character->velocityX) == 0) && ((int) *(character->velocityY) == 0))) {
        character->state = IDLE;
    }

    if ((int) *(character->velocityY) != 0) {
        if (character->isGroundedBool == 1) {
            *(character->velocityY) = 0;
            character->state = IDLE;
        }
        else {
            character->state = JUMPING;
        }
    }

    // Y-Direction Logic (Gravity Affect on y-velocity, isGrounded poll, y-direction update)
    if (character->isGroundedBool == 0) { // Gravity Affect on Y-Velocity
        // Update to velocity with constant acceleration
        *(character->velocityY) = *(character->velocityY) + (GRAVITY * DELTATIME);
        // Update to position with current velocity 
        *(character->y) = *(character->y) + *(character->velocityY);
    }

    // Must call after we check isGroundedBool == 0.
    checkGrounded(character); // isGrounded poll
}

void checkGrounded(Character *character) {
    if (character == NULL) {
        printf("Character does not exist...\n");
    }
    int right_char = *(character->x) + character->width;
    int left_char = *(character->x);
    int top_char = *(character->y);
    int bottom_char = *(character->y)+ character->height;

    int top_plat;
    int bottom_plat;
    int right_plat;
    int left_plat;

    BoundingBox *boxNode = groundBoxHead;
    int index = 0;
    while (boxNode) {
        top_plat = boxNode->y1;
        bottom_plat = boxNode->y2;
        right_plat = boxNode->x2;
        left_plat = boxNode->x1;

        // printf("Top: %d, Bottom: %d, Right: %d, Left: %d\n", top_char, bottom_char, right_char, left_char);
        // printf("Top: %d, Bottom: %d, Right: %d, Left: %d\n", top_plat, bottom_plat, right_plat, left_plat);
        if ((bottom_char >= top_plat) && (bottom_char <= bottom_plat)) { // Character is between the platform
            if ((left_char <= right_plat) && (right_char >= left_plat)) {
                character->isGroundedBool = 1;
                *(character->velocityY) = 0.0;
                *(character->y) = top_plat - character->height;
                return;     
            }
        }
        
        // Otherwise
        boxNode = boxNode->next;
    }
    // If not on ground.
    character->isGroundedBool = 0;
    return;

}

int checkCollision_CharacterObject(Character *a, GameObject *b) {
    if (!(*a->collidable) || !(*b->collidable)) return 0; // Ignore non-collidable objects

    return (*(a->x) < *(b->x) + b->width &&
            *(a->x) + a->width > *(b->x) &&
            *(a->y) < *(b->y) + b->height &&
            *(a->y) + a->height > *(b->y));
}

void resolveCollision_CharacterObject(Character *a, GameObject *b) {
    if (*(a->x) < *(b->x)) *(a->x) -= 5;
    else *(a->x) += 5;
    
    if (*(a->y) < *(b->y)) *(a->y) -= 5;
    else *(a->y) += 5;
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
    else if (character->state == JUMPING) {
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

void jumpCharacter(Character *character) {


}


void horizontalAcceleration(Character *character, int directionBool) {
    // if directionBool is equal to 1, then it's positive acceleration, otherwise negative acceleration
    if (directionBool == 1) {
        if (*(character->velocityX) > 4) {
            *(character->velocityX) = 4;
        }
        else if (*(character->velocityX) < 1) {
            *(character->velocityX) = 1;
        }
        else {
            *(character->velocityX) = *(character->velocityX) + (X_ACCELERATION * DELTATIME);
        }

    }
    else {
        if (*(character->velocityX) < -4) {
            *(character->velocityX) = -4;
        }
        else if (*(character->velocityX) > -1) {
            *(character->velocityX) = -1;
        }
        else {
            *(character->velocityX) = *(character->velocityX) - (X_ACCELERATION * DELTATIME);
        }
    }
}