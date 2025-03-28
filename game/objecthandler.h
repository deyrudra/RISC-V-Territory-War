
#ifndef OBJECTHANDLER_H
#define OBJECTHANDLER_H

// Screen dimensions
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

#include "renderhandler.h"
#include <stddef.h>

// Global Variables
extern short int Buffer1[480][640];
extern short int Buffer2[480][640];
extern volatile int pixel_buffer_start;

// Define GameObject structure
typedef struct {
    int *x, *y; // Position
    int prevX, prevY; // Previous position
    int width, height; // Size
    int *collidable; // 1 for collidable, 0 for non-collidable
    double *velocityX, *velocityY; // Velocity for movement
    short int *asset; // Pointer to the asset (e.g., sprite data)
    short int *prevPixelData; // Pointer to store previous pixel data
    int currentlyRendered; // 1 if currently rendered, 0 otherwise
    int isGround;
} GameObject;


// Function prototypes

void initializeGeneralObject(GameObject **gameObject, short int *asset, int collidable, int x, int y, int width, int height);

void destroyGeneralObject(GameObject *obj);

void resetPrevPixelData(GameObject *obj);

void renderIn(GameObject *obj);

void renderOut(GameObject *obj);

int checkCollision(GameObject *a, GameObject *b);

void resolveCollision(GameObject *a, GameObject *b);


#endif // OBJECTHANDLER_H