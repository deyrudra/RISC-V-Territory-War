#ifndef PLATFORMHANDLER_H
#define PLATFORMHANDLER_H

#include <stdlib.h>
#include <stddef.h>
#include "objectHandler.h"

typedef struct BoundingBox {
    int x1, y1, x2, y2;
    struct BoundingBox *next; // Pointer to next box
} BoundingBox;

// Define Platform structure
typedef struct Platform{
    GameObject *platformObject; // GameObject for the character
    int *x, *y; // Position
    double *velocityX, *velocityY; // Velocity
    int *collidable; // 1 for collidable,  0 for non-collidable
    int width;
    int height;
} Platform;

extern BoundingBox *groundBoxHead;

// Function prototypes
void initializePlatform(Platform *platform, short int *asset, int x, int y, int width, int height);

void placePlatform(Platform *platform);

void removePlatform(Platform *platform);

// Adds a box to an array which determines which areas are considred ground.
// Each box will have (x1, y1) and (x2, y2) determined by the width and height
// of the platform along with it's x and y position.
void addGroundingBox(Platform *platform); 

void printGroundBoxes();

void removeGroundingBox(int x1, int y1, int x2, int y2);

void destroyPlatform(Platform* platform);

#endif // PLATFORMHANDLER_H