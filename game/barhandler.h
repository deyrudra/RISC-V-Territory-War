#ifndef BARHANDLER_H
#define BARHANDLER_H

#include <stdlib.h>
#include <stddef.h>
#include "objectHandler.h"
#include "renderHandler.h"


// Define Platform structure
typedef struct Bar{
    GameObject **barObj; // GameObject for the character
    int *x, *y; // Position
    int *collidable; // 1 for collidable,  0 for non-collidable
    int partitionWidth;
    int partitionHeight;
    int numPartitions;
} Bar;



// Function prototypes
void initializeBar(Bar* bar, int *asset, int partitionWidth, int partitionHeight, int numPartitions, int x, int y);

void resetBar(Bar* bar, int lastRenderedIdx);

void placeBar(Bar *bar);

void removeBar(Bar *bar);

void destroyBar(Bar *bar);


#endif