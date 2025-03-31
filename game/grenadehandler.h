#ifndef GRENADEHANDLER_H
#define GRENADEHANDLER_H

#include <stdlib.h>
#include <stddef.h>
#include "objectHandler.h"
#include "renderHandler.h"
#include "gamelogic.h"
#include <stdbool.h>

//BLAST RADIUS CONSTANTS
#define BLAST_RADIUS 30
#define GRENADE_EXPLOSION_COUNT_LIMIT 200

#define COS_0 1.0000
#define COS_10 0.9848
#define COS_20 0.9397
#define COS_30 0.8660
#define COS_40 0.7660
#define COS_50 0.6428
#define COS_60 0.5000
#define COS_70 0.3420
#define COS_80 0.1736
#define COS_90 0.0000

#define SIN_0 0.0000
#define SIN_10 0.1736
#define SIN_20 0.3420
#define SIN_30 0.5000
#define SIN_40 0.6428
#define SIN_50 0.7660
#define SIN_60 0.8660
#define SIN_70 0.9397
#define SIN_80 0.9848
#define SIN_90 1.0000

extern int rotate_up_grenade_released;
extern int rotate_down_grenade_released;
extern int throw_grenade_released;
extern int num_bounces;

extern double grenade_user_angle;
extern double grenade_user_power;

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
void initializeGrenade(Grenade* grenade, int x, int y,short int* asset, double angle, double power, int lookingRightBool);
void updateGrenadePosition(Grenade* grenade);

double getCosRatio(int angle);
double getSinRatio(int angle);

void destroyGrenade(Grenade* grenade);

void checkGrenadeGrounded(Grenade* grenade);

void checkWithinBlastRadiusAndApplyDamage(Grenade* grenade, Character** team_a, Character** team_b);

bool isCharacterLeftOfGrenade(Grenade* grenade, Character* character);


#endif