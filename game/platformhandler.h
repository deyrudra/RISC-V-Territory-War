#ifndef MOVEMENTHANDLER_H
#define MOVEMENTHANDLER_H

#include <stdlib.h>
#include <stddef.h>
#include "objectHandler.h"

// Define character structure
typedef struct Platform{
    GameObject *asset; // GameObject for the character
    int *x, *y; // Position
    double *velocityX, *velocityY; // Velocity
    int *collidable; // 1 for collidable,  0 for non-collidable
    int width;
    int height;
} Platform;

// Function prototypes
void initializePlatform(Platform *platform, int *asset, int x, int y, int width, int height);

#endif // MOVEMENTHANDLER_H