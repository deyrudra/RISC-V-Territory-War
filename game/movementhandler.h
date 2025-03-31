#ifndef MOVEMENTHANDLER_H
#define MOVEMENTHANDLER_H

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32

#define DELTATIME 0.02
#define GRAVITY 9.81

#define X_ACCELERATION 1.2 // For x movement walking.

#include <stdlib.h>
#include <stddef.h>
#include "objectHandler.h"
#include "inputhandler.h"
#include "loadassets.h"
#include "platformhandler.h"
#include "renderhandler.h"
#include "barhandler.h"


// PS/2 Keyboard related variables
extern volatile int* ps2_ptr;
extern int ps2_data;
extern int RVALID;
extern uint8_t byte1, byte2, byte3;
extern const char* gameControls[];

extern int move_right_released;
extern int move_left_released;

typedef enum { IDLE, LEFTMOVEMENT, RIGHTMOVEMENT, GUN, GRENADE, BOOT, JUMPINGLEFT, JUMPINGRIGHT, DEAD} CharacterState;
// Define character structure
typedef struct Character{
    GameObject *idleCharacter; // GameObject for the character
    GameObject *walkLeftCharacter; // GameObject for the character
    GameObject *walkRightCharacter; // GameObject for the character
    GameObject *leftJumpingCharacter; // GameObject for the character
    GameObject *rightJumpingCharacter; // GameObject for the character
    GameObject *leftBootCharacter; // GameObject for the character
    GameObject *rightBootCharacter; // GameObject for the character
    GameObject *deadCharacter; // GameObject for the character
    int *x, *y; // Position
    double *velocityX, *velocityY; // Velocity
    int *collidable; // 1 for collidable,  0 for non-collidable
    CharacterState state;
    CharacterState prevState;
    int isGroundedBool; // 1 for grounded, 0 for not grounded
    int* health;
    int width;
    int height;
    int numJumps;
    RenderView characterView;
    Bar* healthBar;
    CharacterState lastMovementMade;
    int withinBlastRadiusBool;
    int id;
} Character;

double abs_double(double value);
int abs_int(int value);


// Function prototypes
void initializeCharacter(Character *character, int x, int y, short int *idleCharAsset, short int *walkLeftCharAsset, short int *walkRightCharAsset, short int *leftJumpCharAsset, short int *rightJumpCharAsset, char team, int id);

void drawInitialHealthBar(Character *character);

void updateHealthBar(Character* character);

void moveCharacter(Character *character, char* direction, int* displacement);

void drawCharacter(Character *character, bool firstRun);

void destroyCharacter(Character *character);

void removeCharacter(Character *character);

void resolveCollision_CharacterObject(Character *a, GameObject *b);

int checkCollision_Characters(Character *a, Character *b);

int checkCollision_CharacterObject(Character *a, GameObject *b);

void checkGrounded(Character *character);

void resetArrowKeyReleaseFlags();

void knockbackCharacter(Character* character, bool characterLeft);

#endif // MOVEMENTHANDLER_H