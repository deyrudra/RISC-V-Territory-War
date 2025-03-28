#include "barhandler.h"

void initializeBar(Bar* bar, int *asset, int partitionWidth, int partitionHeight, int numPartitions, int x, int y){

    bar->x = malloc(sizeof(int));
    bar->y = malloc(sizeof(int));
    bar->collidable = malloc(sizeof(int));
    bar->partitionWidth = partitionWidth;
    bar->partitionHeight = partitionHeight;
    bar->numPartitions = numPartitions;

    *(bar->collidable) = 0;


    bar->barObj = malloc((numPartitions) * sizeof(GameObject*));


    for(int i = 0; i < numPartitions; i++){
        bar->barObj[i] = malloc(sizeof(GameObject));

        bar->barObj[i]->asset = asset;
        bar->barObj[i]->height = partitionHeight;
        bar->barObj[i]->width = partitionWidth;
        bar->barObj[i]->prevPixelData = malloc(partitionWidth * partitionHeight * sizeof(int));
        bar->barObj[i]->x = malloc(sizeof(int));
        bar->barObj[i]->y = malloc(sizeof(int));
        bar->barObj[i]->velocityX = malloc(sizeof(double));
        bar->barObj[i]->velocityY = malloc(sizeof(double));
        bar->barObj[i]->collidable = malloc(sizeof(int));


        //Set values (decide how to deal with setting velocity and x and y for moving health bars)
        *(bar->barObj[i]->x) = x + i*partitionWidth;
        *(bar->barObj[i]->y) = y;
        *(bar->barObj[i]->velocityX) = 0;
        *(bar->barObj[i]->velocityY) = 0;
       *(bar->barObj[i]->collidable) = 0;
    }
}


void resetBar(Bar* bar, int lastRenderedIdx){
    for(int i = lastRenderedIdx; i >= 0; i--){
        renderOut(bar->barObj[i]);
    }
}



void placeBar(Bar *bar);

void removeBar(Bar *bar);

void destroyBar(Bar *bar);