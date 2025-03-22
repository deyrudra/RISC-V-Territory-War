#ifndef MOVEMENTHANDLER_H
#define MOVEMENTHANDLER_H

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32

#define DELTATIME 0.016
#define GRAVITY -5
#define AIRDRAG -2


#include "objecthandler.h" // Include the GameObject definitions
#include <string.h>

extern const char* gameControls[];

typedef enum { IDLE, LEFTMOVEMENT, RIGHTMOVEMENT, GUN, GRENADE, BOOT, JUMPING, DEAD, UNKNOWN } CharacterState;

// Define character structure
typedef struct {
    GameObject *idleCharacter; // GameObject for the character
    GameObject *walkLeftCharacter; // GameObject for the character
    GameObject *walkRightCharacter; // GameObject for the character
    GameObject *jumpingCharacter; // GameObject for the character
    GameObject *leftBootCharacter; // GameObject for the character
    GameObject *rightBootCharacter; // GameObject for the character
    GameObject *jumpCharacter; // GameObject for the character
    GameObject *deadCharacter; // GameObject for the character
    int *x, *y; // Position
    double *velocityX, *velocityY; // Velocity
    int *collidable; // 1 for collidable,  0 for non-collidable
    CharacterState state;
    CharacterState prevState;
} Character;

// Function prototypes
void initializeCharacter(Character *character, int *idleCharAsset, int *walkLeftCharAsset, int *walkRightCharAsset, int *jumpCharAsset, int *idlePrevData, int *walkLeftPrevData, int *walkRightPrevData, int *jumpPrevData);


void moveCharacter(Character *character, char* direction);

void drawCharacter(Character *character);

void gravityCharacter(Character *character);

void airdragCharacter(Character *character);

#endif // MOVEMENTHANDLER_H