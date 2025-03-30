#include "backgroundhandler.h"

// Global Backgrounds
Background menuBackground;
Background skyBackground;

// Function prototypes
void initializeBackground(Background *background, short int *asset, int width, int height) {
    background->cols = (WORLD_WIDTH / width) + (WORLD_WIDTH % width != 0); // Ceiling division
    background->rows = (WORLD_HEIGHT / height) + (WORLD_HEIGHT % height != 0); // Ceiling division
    
    background->backgroundPrevData = malloc(sizeof(int) * width * height);
    background->x = malloc(sizeof(int));
    background->y = malloc(sizeof(int));
    background->collidable = malloc(sizeof(int));
    background->width = width;
    background->height = height;

    *(background->collidable) = 0;

    // Allocate array of GameObject pointers
    background->backgroundObjects = malloc((background->cols * background->rows) * sizeof(GameObject*));

    for (int row = 0; row < background->rows; row++) {
        for (int col = 0; col < background->cols; col++) {
            int index = row * background->cols + col; // Use background->cols for index calculation
            
            GameObject *obj = malloc(sizeof(GameObject));
            obj->asset = asset;
            obj->height = height;
            obj->width = width;
            obj->prevPixelData = background->backgroundPrevData;
            obj->x = malloc(sizeof(int));
            obj->y = malloc(sizeof(int));
            obj->velocityX = malloc(sizeof(double));
            obj->velocityY = malloc(sizeof(double));
            obj->collidable = malloc(sizeof(int));
            
            // Set initial values
            *(obj->x) = col * width;
            *(obj->y) = row * height;
            *(obj->velocityX) = 0;
            *(obj->velocityY) = 0;
            *(obj->collidable) = 0;
            
            background->backgroundObjects[index] = obj;
        }
    }
}

void placeBackground(Background *background) {
    for (int row = 0; row < background->rows; row++) {
        for (int col = 0; col < background->cols; col++) {
            int index = row * background->cols + col; // Use background->cols for index calculation
            renderIn(background->backgroundObjects[index]);
        }
    }
}

void removeBackground(Background *background) {
    for (int row = 0; row < background->rows; row++) {
        for (int col = 0; col < background->cols; col++) {
            int index = row * background->cols + col; // Use background->cols for index calculation
            renderOut(background->backgroundObjects[index]);
        }
    }
}

void destroyBackground(Background *background) {
    // Free each GameObject inside background->backgroundObjects
    for (int row = 0; row < background->rows; row++) {
        for (int col = 0; col < background->cols; col++) {
            int index = row * background->cols + col; // Use background->cols for index calculation

            if (background->backgroundObjects[index]) {
                // Free dynamically allocated members of GameObject
                free(background->backgroundObjects[index]->x);
                free(background->backgroundObjects[index]->y);
                free(background->backgroundObjects[index]->velocityX);
                free(background->backgroundObjects[index]->velocityY);
                free(background->backgroundObjects[index]->collidable);

                // Free the GameObject itself
                free(background->backgroundObjects[index]);
            }
        }
    }
    
    // Free the array of GameObject pointers
    free(background->backgroundObjects);
    
    // Free backgroundPrevData (only once, since all GameObjects share it)
    free(background->backgroundPrevData);

    // Free other dynamically allocated members of background
    free(background->x);
    free(background->y);
    free(background->collidable);
}