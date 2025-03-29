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

int abs_int(int value) {
    if (value >= 0) {
        return value;
    }
    else {
        return -value;
    }
}

void initializeCharacter(Character *character, int x, int y, short int *idleCharAsset, short int *walkLeftCharAsset, short int *walkRightCharAsset, short int *jumpLeftCharAsset, short int *jumpRightCharAsset, char team) {
    // Replace all local array declarations with malloc calls
    short int* walkLeftPrevData = malloc(sizeof(short int) * LEFTMOVEMENT_WIDTH * LEFTMOVEMENT_HEIGHT);
    short int* walkRightPrevData = malloc(sizeof(short int) * RIGHTMOVEMENT_WIDTH * RIGHTMOVEMENT_HEIGHT);
    short int* jumpLeftPrevData = malloc(sizeof(short int) * JUMP_WIDTH * JUMP_HEIGHT);
    short int* jumpRightPrevData = malloc(sizeof(short int) * JUMP_WIDTH * JUMP_HEIGHT);
    short int* idlePrevData = malloc(sizeof(short int) * IDLE_WIDTH * IDLE_HEIGHT);
    short int* leftbootPrev = malloc(sizeof(short int) * LEFTBOOT_WIDTH * LEFTBOOT_HEIGHT);
    short int* rightbootPrev = malloc(sizeof(short int) * LEFTBOOT_WIDTH * LEFTBOOT_HEIGHT);
    short int* deadPrev = malloc(sizeof(short int) * DEAD_WIDTH * DEAD_HEIGHT);
    
    
    character->x = malloc(sizeof(int));
    character->y = malloc(sizeof(int));
    character->velocityX = malloc(sizeof(double));
    character->velocityY = malloc(sizeof(double));
    character->collidable = malloc(sizeof(int));
    character->health = malloc(sizeof(int));
    character->state = IDLE;
    character->lastMovementMade = LEFTMOVEMENT;
    character->isGroundedBool = 0;
    character->width = PLAYER_WIDTH;
    character->height = PLAYER_HEIGHT;
    character->healthBar = malloc(sizeof(Bar));

    if (x < SCREEN_WIDTH) {
        character->characterView = LEFTVIEW;
    }
    else if ((SCREEN_WIDTH <= x) && (x < SCREEN_WIDTH*2)) {
        character->characterView = MIDDLEVIEW;
    }
    else if (SCREEN_WIDTH*2 <= x) {
        character->characterView = RIGHTVIEW;
    }
            
    *(character->collidable) = 1;
    *(character->x) = x;
    *(character->y) = y;
    *(character->velocityX) = 0;
    *(character->velocityY) = 0;
    *(character->health) = 100;

    if(team == 'a'){
        initializeBar(character->healthBar, &redhealthbarpartition, HEALTHBARPARTITION_WIDTH, HEALTHBARPARTITION_HEIGHT, NUM_HEALTH_BAR_PARTITIONS, x+3, y-3, NUM_HEALTH_BAR_PARTITIONS);
    } else {
        initializeBar(character->healthBar, &bluehealthbarpartition, HEALTHBARPARTITION_WIDTH, HEALTHBARPARTITION_HEIGHT, NUM_HEALTH_BAR_PARTITIONS, x+3, y-3, NUM_HEALTH_BAR_PARTITIONS);
    }


    
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
    
    GameObject * leftJumpingCharacterObj = (GameObject *)malloc(sizeof(GameObject));
    character->leftJumpingCharacter = leftJumpingCharacterObj;
    character->leftJumpingCharacter->asset = jumpLeftCharAsset;
    character->leftJumpingCharacter->height = PLAYER_HEIGHT;
    character->leftJumpingCharacter->width = PLAYER_WIDTH;
    character->leftJumpingCharacter->prevPixelData = jumpLeftPrevData;
    character->leftJumpingCharacter->x = malloc(sizeof(int));  // Allocate memory
    character->leftJumpingCharacter->y = malloc(sizeof(int));  // Allocate memory
    character->leftJumpingCharacter->velocityX = malloc(sizeof(double));  // Allocate memory
    character->leftJumpingCharacter->velocityY = malloc(sizeof(double));  // Allocate memory
    character->leftJumpingCharacter->collidable = malloc(sizeof(int));  // Allocate memory
    
    GameObject * rightJumpingCharacterObj = (GameObject *)malloc(sizeof(GameObject));
    character->rightJumpingCharacter = rightJumpingCharacterObj;
    character->rightJumpingCharacter->asset = jumpRightCharAsset;
    character->rightJumpingCharacter->height = PLAYER_HEIGHT;
    character->rightJumpingCharacter->width = PLAYER_WIDTH;
    character->rightJumpingCharacter->prevPixelData = jumpRightPrevData;
    character->rightJumpingCharacter->x = malloc(sizeof(int));  // Allocate memory
    character->rightJumpingCharacter->y = malloc(sizeof(int));  // Allocate memory
    character->rightJumpingCharacter->velocityX = malloc(sizeof(double));  // Allocate memory
    character->rightJumpingCharacter->velocityY = malloc(sizeof(double));  // Allocate memory
    character->rightJumpingCharacter->collidable = malloc(sizeof(int));  // Allocate memory
    
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
    character->leftJumpingCharacter->x = character->x;
    character->leftJumpingCharacter->y = character->y;
    character->leftJumpingCharacter->velocityX = character->velocityX;
    character->leftJumpingCharacter->velocityY = character->velocityY;
    character->leftJumpingCharacter->collidable = character->collidable;
    character->rightJumpingCharacter->x = character->x;
    character->rightJumpingCharacter->y = character->y;
    character->rightJumpingCharacter->velocityX = character->velocityX;
    character->rightJumpingCharacter->velocityY = character->velocityY;
    character->rightJumpingCharacter->collidable = character->collidable;
}

// Function to handle character movement
void moveCharacter(Character *character, char* direction, int* displacement){
    if (character == NULL) {
        printf("Character does not exist...\n");
    }
    else {
        //Test
        // Calling Gravity (y-friction) and Air Drag (x-friction) Functions
        // gravityCharacter(character);
        // airdragCharacter(character);

        // Saving Prevstate
        character->prevState = character->state;
        
        // Setting Character States (for assets) based on movement input.
        //Move left released 1 means released while 0 means it is being pressed (this is for the moving jump where we need sense of both controls at same time)
        if ((strcmp(direction, gameControls[0]) == 0) || (move_left_released == 0)) { // Checking for move_left
            move_left_released = 0; // tells us key is still being pressed in case next control is a jump
            character->state = LEFTMOVEMENT; //update state for drawing the correct asset 
            horizontalAcceleration(character, 0); //update the character's velocity
            *(character->x) = *(character->x) + *(character->velocityX); //update position based on new velocity
            *displacement += *character->velocityX; //update dist travelled for movement limit
            character->lastMovementMade = LEFTMOVEMENT;
        }
        if ((strcmp(direction, gameControls[1]) == 0) || (move_right_released == 0)) { // Checking for move_right
            move_right_released = 0;
            character->state = RIGHTMOVEMENT;
            horizontalAcceleration(character, 1);
            *(character->x) = *(character->x) + *(character->velocityX);
            *displacement += *character->velocityX; //update dist travelled for movement limit
            character->lastMovementMade = RIGHTMOVEMENT;
        }
        if ((strcmp(direction, gameControls[2]) == 0) && (character->numJumps < 2)) { // Checking for move_jump
            if(character->lastMovementMade == RIGHTMOVEMENT) {
                character->state = JUMPINGRIGHT;
            }
            else if (character->lastMovementMade == LEFTMOVEMENT) {
                character->state = JUMPINGLEFT;
            }
            *(character->velocityY) = -3.0;
            character->isGroundedBool = 0;
            character->numJumps++;
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

    // If character is jumping, as soon as we detect that they are grounded set their y velocity to 0 and update asset
    if ((int) *(character->velocityY) != 0) {
        if (character->isGroundedBool == 1) {
            *(character->velocityY) = 0;
            character->state = IDLE;
        }
        else {
            if(character->lastMovementMade == RIGHTMOVEMENT) {
                character->state = JUMPINGRIGHT;
            }
            else if (character->lastMovementMade == LEFTMOVEMENT) {
                character->state = JUMPINGLEFT;
            }
        }
    }

    // Y-Direction Logic (Gravity Affect on y-velocity, isGrounded poll, y-direction update)
    if (character->isGroundedBool == 0) { // Gravity Affect on Y-Velocity
        if(character->lastMovementMade == RIGHTMOVEMENT) {
            character->state = JUMPINGRIGHT;
        }
        else if (character->lastMovementMade == LEFTMOVEMENT) {
            character->state = JUMPINGLEFT;
        }
        // Update to velocity with constant acceleration
        *(character->velocityY) = *(character->velocityY) + (GRAVITY * DELTATIME);
        // Update to position with current velocity 
        *(character->y) = *(character->y) + *(character->velocityY);
    }
    else {
        character->numJumps = 0;
    }

    // Checking which screen the character is on.
    if (*(character->x) < SCREEN_WIDTH) {
        character->characterView = LEFTVIEW;
    }
    else if ((SCREEN_WIDTH <= *(character->x)) && (*(character->x) < SCREEN_WIDTH*2)) {
        character->characterView = MIDDLEVIEW;
    }
    else if (SCREEN_WIDTH*2 <= *(character->x)) {
        character->characterView = RIGHTVIEW;
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
        // printf("Top: %d, Bottom: %d, Right: %d, Left: %d\n", top_plat, bottom_plat, right_plat, left_plat);'

        // Character is between the platform, we check this b/c acceleration logic may skip pixels as it is double math
        if ((bottom_char >= top_plat) && (bottom_char <= bottom_plat)) { 
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

void removeCharacter(Character *character){

    //render out character based on current state
    if (character->prevState == IDLE) {
        renderOut(character->idleCharacter);
    }
    else if (character->prevState == LEFTMOVEMENT) {
        renderOut(character->walkLeftCharacter);
    }
    else if (character->prevState == RIGHTMOVEMENT) {
        renderOut(character->walkRightCharacter);
    }
    else if (character->prevState == JUMPINGLEFT) {
        renderOut(character->leftJumpingCharacter);
    }
    else if (character->prevState == JUMPINGRIGHT) {
        renderOut(character->rightJumpingCharacter);
    }
    else{
        printf("Unknown state\n");
    }
}

void destroyCharacter(Character *character){
    if (character == NULL) return;
    removeCharacter(character);



    free(character->idleCharacter->prevPixelData);
    free(character->walkLeftCharacter->prevPixelData);
    free(character->walkRightCharacter->prevPixelData);
    free(character->leftJumpingCharacter->prevPixelData);
    free(character->rightJumpingCharacter->prevPixelData);

    //uncomment when we add these states 
    // free(character->leftBootCharacter->prevPixelData);
    // free(character->rightBootCharacter->prevPixelData);
    // free(character->deadCharacter->prevPixelData);
    
    if (character->x != NULL) free(character->x);
    if (character->y != NULL) free(character->y);
    if (character->velocityX != NULL) free(character->velocityX);
    if (character->velocityY != NULL) free(character->velocityY);
    if (character->collidable != NULL) free(character->collidable);
    if (character->health != NULL) free(character->health);
}

void drawCharacter(Character *character, bool firstRun){
    // If character state didn't change, then don't do nothing.
    // Rendering out Old Asset
    if (!firstRun) {
        updateHealthBar(character);
    }

    if (character->prevState == IDLE) {
        renderOut(character->idleCharacter);
    }
    else if (character->prevState == LEFTMOVEMENT) {
        renderOut(character->walkLeftCharacter);
    }
    else if (character->prevState == RIGHTMOVEMENT) {
        renderOut(character->walkRightCharacter);
    }
    else if (character->prevState == JUMPINGLEFT) {
        renderOut(character->leftJumpingCharacter);
    }
    else if (character->prevState == JUMPINGRIGHT) {
        renderOut(character->rightJumpingCharacter);
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
    else if (character->state == JUMPINGLEFT) {
        renderIn(character->leftJumpingCharacter);
    }
    else if (character->state == JUMPINGRIGHT) {
        renderIn(character->rightJumpingCharacter);
    }
    
}


void drawInitialHealthBar(Character* character){
    for(int i = 0; i < NUM_HEALTH_BAR_PARTITIONS; i++){
        // printf("health idx%d\n", i);
        renderIn(character->healthBar->barObj[i]);
    }
    setLastRenderedPartition(character->healthBar, NUM_HEALTH_BAR_PARTITIONS);
}


void updateHealthBar(Character* character){
     // // This is for change!!! (num_parititons filled will never be > lastRendered since you cant gain health)

    //render out prev bar
    // printf("debug output 1\n");
    for(int i = 0; i < character->healthBar->lastRenderedPartition; i++){
        // printf("render out idx: %d\n", i);
        renderOut(character->healthBar->barObj[i]);
    }

    // printf("Rendered out old bar");

    //advanced updating of x and y positions
    *(character->healthBar->x) = *(character->x) + 3;
    *(character->healthBar->y) = *(character->y) - 3;

    for(int i = 0; i < NUM_HEALTH_BAR_PARTITIONS; i++){
        *(character->healthBar->barObj[i]->x) = *(character->healthBar->x) + i*character->healthBar->partitionWidth;
        *(character->healthBar->barObj[i]->y) = *(character->healthBar->y);
    }
    
    // printf("debug output 2\n");

    double ratio = *(character->health) / HEALTH_LIMIT;
    //printf("ratio: %lf\n", ratio);

    // if(ratio > 1) ratio = 1;

    int num_partitions_filled = ratio * NUM_HEALTH_BAR_PARTITIONS;
    // printf("num partitions filed: %d\n", num_partitions_filled);


    // printf("debug output 3\n");

    //render in new bar
    for(int i = 0; i < num_partitions_filled; i++){
        // printf("render in idx: %d\n", i);
        if (character->state == JUMPINGLEFT || character->prevState == JUMPINGLEFT || character->state == JUMPINGRIGHT || character->prevState == JUMPINGRIGHT) {
        
        }
        else {
            renderIn(character->healthBar->barObj[i]);
        }
    }

    // printf("debug output 4\n");

    setLastRenderedPartition(character->healthBar, num_partitions_filled);
}



void horizontalAcceleration(Character *character, int directionBool) {
    // if directionBool is equal to 1, then it's positive acceleration, otherwise negative acceleration
    if (directionBool == 1) {
        // velocity is bounded by 1 m/s and 4m/s and we update velocity by adding acceleration*dt
        if (*(character->velocityX) > 3) {
            *(character->velocityX) = 3;
        }
        else if (*(character->velocityX) < 0.8) {
            *(character->velocityX) = 0.8;
        }
        else {
            *(character->velocityX) = *(character->velocityX) + (X_ACCELERATION * DELTATIME);
        }

    }
    else {
        if (*(character->velocityX) < -3) {
            *(character->velocityX) = -3;
        }
        else if (*(character->velocityX) > -0.8) {
            *(character->velocityX) = -0.8;
        }
        else {
            *(character->velocityX) = *(character->velocityX) - (X_ACCELERATION * DELTATIME);
        }
    }
}

void resetArrowKeyReleaseFlags(){
    move_left_released = 1;
    move_right_released = 1;
}