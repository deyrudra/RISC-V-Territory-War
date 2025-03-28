#ifndef BACKGROUNDHANDLER_H
#define BACKGROUNDHANDLER_H

#include <stdlib.h>
#include <stddef.h>
#include "objectHandler.h"
#include "renderHandler.h"


// Define Platform structure
typedef struct Background{
    GameObject **backgroundObjects; // GameObject for the character
    int* backgroundPrevData;
    int *x, *y; // Position
    int *collidable; // 1 for collidable,  0 for non-collidable
    int width;
    int height;
    int rows;
    int cols;
} Background;

// Global Background Objects
extern Background menuBackground;
extern Background skyBackground;

// Function prototypes
void initializeBackground(Background *background, short int *asset, int width, int height);

void placeBackground(Background *background);

void removeBackground(Background *background);

void destroyBackground(Background *background);


#endif