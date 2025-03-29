#include "grenadehandler.h"

rotate_up_grenade_released = 1; // 1 means the key has been released
rotate_down_grenade_released = 1;
throw_grenade_released = 1;


void initializeGrenade(Grenade* grenade, int x, int y, short int* asset){

    // grenade->x = malloc(sizeof(int));
    // grenade->y = malloc(sizeof(int));
    // grenade->velocityX = malloc(sizeof(double));
    // grenade->velocityY = malloc(sizeof(double));
    // grenade->collidable = malloc(sizeof(int));
    // grenade->isGroundedBool = 0;
    // grenade->isExplodedBool = 0;
    // grenade->width = GRENADE_WIDTH;
    // grenade->height = GRENADE_HEIGHT;

    grenade->grenadeObj = malloc(sizeof(Grenade));
    grenade->grenadeObj->x = malloc(sizeof(int));
    grenade->grenadeObj->y = malloc(sizeof(int));
    grenade->grenadeObj->velocityX = malloc(sizeof(double));
    grenade->grenadeObj->velocityY = malloc(sizeof(double));
    grenade->grenadeObj->collidable = malloc(sizeof(int));
    grenade->grenadeObj->width = GRENADE_WIDTH;
    grenade->grenadeObj->height = GRENADE_HEIGHT;
    grenade->grenadeObj->asset = asset;
    grenade->grenadeObj->prevPixelData = malloc(GRENADE_HEIGHT * GRENADE_WIDTH * sizeof(short int));
    
    grenade->angle = malloc(sizeof(double));
    grenade->power = malloc(sizeof(double));

    // Populate gameObject data
    *(grenade->grenadeObj->x) = x;
    *(grenade->grenadeObj->y) = y;
    *(grenade->grenadeObj->velocityX) = 0;
    *(grenade->grenadeObj->velocityY) = 0;
    *(grenade->grenadeObj->collidable) = 1;

    // Populate Grenade extra Grenade struct fields
    grenade->isExplodedBool = 0;
    grenade->isGroundedBool = 0;
    *(grenade->angle) = 0;
    *(grenade->power) = 0;


    if (x < SCREEN_WIDTH) {
        grenade->grenadeView = LEFTVIEW;
    }
    else if ((SCREEN_WIDTH <= x) && (x < SCREEN_WIDTH*2)) {
        grenade->grenadeView = MIDDLEVIEW;
    }
    else if (SCREEN_WIDTH*2 <= x) {
        grenade->grenadeView = RIGHTVIEW;
    }
}

void destroyGrenade(Grenade* grenade){
    free(grenade->grenadeObj->x);
    free(grenade->grenadeObj->y);
    free(grenade->grenadeObj->velocityX);
    free(grenade->grenadeObj->velocityY);
    free(grenade->grenadeObj->collidable);
    free(grenade->grenadeObj->prevPixelData);

    free(grenade->angle);
    free(grenade->power);

    free(grenade->grenadeObj);
}   

