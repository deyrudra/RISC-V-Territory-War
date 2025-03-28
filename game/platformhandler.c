#include "platformhandler.h"

BoundingBox *groundBoxHead = NULL; // Head of linked list

void initializePlatform(Platform *platform, short int *asset, int x, int y, int width, int height) {
    short int* platformPrevData = malloc(sizeof(short int) * width * height);

    platform->x = malloc(sizeof(int));
    platform->y = malloc(sizeof(int));

    platform->velocityX = malloc(sizeof(double));
    platform->velocityY = malloc(sizeof(double));
    platform->collidable = malloc(sizeof(int));
    platform->width = width;
    platform->height = height;

    *(platform->collidable) = 1;
    *(platform->x) = x;
    *(platform->y) = y;
    *(platform->velocityX) = 0;
    *(platform->velocityY) = 0;

    GameObject * platformObj = (GameObject *)malloc(sizeof(GameObject));
    platform->platformObject = platformObj;
    platform->platformObject->asset = asset;
    platform->platformObject->height = platform->height;
    platform->platformObject->width = platform->width;
    platform->platformObject->prevPixelData = platformPrevData;
    platform->platformObject->x = malloc(sizeof(int));  // Allocate memory
    platform->platformObject->y = malloc(sizeof(int));  // Allocate memory
    platform->platformObject->velocityX = malloc(sizeof(double));  // Allocate memory
    platform->platformObject->velocityY = malloc(sizeof(double));  // Allocate memory
    platform->platformObject->collidable = malloc(sizeof(int));  // Allocate memory

    platform->platformObject->x = platform->x;
    platform->platformObject->y = platform->y;
    platform->platformObject->velocityX = platform->velocityX;
    platform->platformObject->velocityY = platform->velocityY;
    platform->platformObject->collidable = platform->collidable;

    
}

void placePlatform(Platform *platform) {
    renderIn(platform->platformObject);
    addGroundingBox(platform);
}

void removePlatform(Platform *platform) {
    renderOut(platform->platformObject);
    removeGroundingBox(*(platform->x), *(platform->y), *(platform->x) + platform->width, *(platform->y) + platform->height);
}


void addGroundingBox(Platform *platform) {
    if (platform == NULL) return;

    BoundingBox *newBox = (BoundingBox *)malloc(sizeof(BoundingBox));
    if (!newBox) {
        printf("Memory allocation failed!\n");
    }

    newBox->x1 = *(platform->x);
    newBox->y1 = *(platform->y);
    newBox->x2 = *(platform->x) + platform->width;
    if (platform->height < 10) {
        platform->height = 10;
    }
    newBox->y2 = *(platform->y) + platform->height;
    newBox->next = groundBoxHead;
    groundBoxHead = newBox;
}

void printGroundBoxes() {
    BoundingBox *current = groundBoxHead;
    int index = 0;
    while (current) {
        printf("Box %d: (%d, %d) to (%d, %d)\n", 
               index++, current->x1, current->y1, 
               current->x2, current->y2);
        current = current->next;
    }
}

void removeGroundingBox(int x1, int y1, int x2, int y2) {
    BoundingBox *current = groundBoxHead;
    BoundingBox *prev = NULL;

    while (current) {
        if (current->x1 == x1 && current->y1 == y1 &&
            current->x2 == x2 && current->y2 == y2) {
            // Found the box, remove it
            if (prev) {
                prev->next = current->next; // Bypass the current node
            } else {
                groundBoxHead = current->next; // Update head if first node
            }
            free(current);
            printf("Removed grounding box (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Box not found!\n");
}


void destroyPlatform(Platform* platform) { // Deallocates the memory for the platform, the objct no longer exists.
    if (platform == NULL) return;
    removePlatform(platform);

    // 1. Free the platform's GameObject (platformObj)
    free(platform->platformObject->prevPixelData);

    // 2. Free the individual fields (x, y, velocityX, velocityY, collidable)
    // (No need to free platformObj's copies since they point to the same memory)
    if (platform->x != NULL) free(platform->x);
    if (platform->y != NULL) free(platform->y);
    if (platform->velocityX != NULL) free(platform->velocityX);
    if (platform->velocityY != NULL) free(platform->velocityY);
    if (platform->collidable != NULL) free(platform->collidable);

    // 3. Finally, free the platform itself
    free(platform);
}