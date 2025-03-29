#ifndef GRENADEHANDLER_H
#define GRENADEHANDLER_H

#include <stdlib.h>
#include <stddef.h>
#include "objectHandler.h"
#include "renderHandler.h"

#define GRENADE_WIDTH 10
#define GRENADE_HEIGHT 10

extern int rotate_up_grenade_released;
extern int rotate_down_grenade_released;
extern int throw_grenade_released;

// Define Platform structure
typedef struct Grenade{
    GameObject *grenadeObj; // GameObject for the character
    int isGroundedBool; // 1 for grounded, 0 for not grounded
    int isExplodedBool; // 1 for exploded, 0 for not exploded
    RenderView grenadeView;
    double* angle;
    double* power;
} Grenade;

// Function prototypes
void initializeGrenade(Grenade* grenade, int x, int y,short int* asset);

void updateGrenadePosition(Grenade* grenade);

void destroyGrenade(Grenade* grenade);

#endif