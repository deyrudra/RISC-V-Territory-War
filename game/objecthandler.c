#include "objecthandler.h"

void resetPrevPixelData(GameObject *obj) {
    for (int y_pix = 0; y_pix < obj->height; y_pix++) {
        for (int x_pix = 0; x_pix < obj->width; x_pix++) {
            obj->prevPixelData[x_pix + y_pix * obj->width] = -1;
        }
    }
} //set asset of object everything -1

// records for the prev location of the asset for obj, and draws a obj 
void renderIn(GameObject *obj) {
    // Save previous position
    obj->prevX = *obj->x;
    obj->prevY = *obj->y;

    // Reset previous pixel data
    resetPrevPixelData(obj); //makes an array of all -1

    // Mark the object as currently rendered
    obj->currentlyRendered = 1;

    // Render current view if changed.

    // Render the object into the pixel buffer
    for (int y_pix = 0; y_pix < obj->height; y_pix++) {
        if (((*obj->y + y_pix) > SCREEN_HEIGHT) || ((*obj->y + y_pix) < 0) ){
            continue;
        }
        for (int x_pix = 0; x_pix < obj->width; x_pix++) {
            short int pixel = obj->asset[x_pix + y_pix * obj->width];
            // Other View Renderings
            if (((*obj->x + x_pix) > WORLD_WIDTH)){ // if object goes too right
                continue;
            }
            else if (((*obj->x + x_pix) < 0)) { // if object goes too left
                continue;
            }
            
            // Current View Rendering
            if (pixel != -1) {
                // Rendering new pixels onto buffer and onto other views.
                if (currentView == LEFTVIEW) {
                    if ((*obj->x + x_pix) < 0) {
                        continue;
                    }
                    if ((*obj->x + x_pix) >= SCREEN_WIDTH) {
                        // Save the previous pixel data
                        obj->prevPixelData[x_pix + y_pix * obj->width] = WORLD[(*obj->y + y_pix)][(*obj->x + x_pix)];
                        WORLD[(*obj->y + y_pix)][(*obj->x + x_pix)] = pixel;
                        continue;
                    }
                    // Calculate address for the pixel in the pixel buffer
                    volatile short int *one_pixel_address;
                    one_pixel_address = (volatile short int *)pixel_buffer_start + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix) << 0);
                    // Save the previous pixel data
                    obj->prevPixelData[x_pix + y_pix * obj->width] = *one_pixel_address; //takes whatever inside buffer and store in prev pixel data

                    // Write the new pixel data to Buffer1
                    volatile short int *buffer1_pixel_address;
                    buffer1_pixel_address = (volatile short int *)&Buffer1 + ((*obj->y + y_pix) << 9) + ((*obj->x + x_pix) << 0);
                    *buffer1_pixel_address = pixel;
                    
                    // Write the new pixel data to Buffer2
                    volatile short int *buffer2_pixel_address;
                    buffer2_pixel_address = (volatile short int *)&Buffer2 + ((*obj->y + y_pix) << 9) + ((*obj->x + x_pix) << 0);
                    *buffer2_pixel_address = pixel;
                }
                else if (currentView == MIDDLEVIEW) {
                    if ((*obj->x + x_pix) < SCREEN_WIDTH) {
                        // Save the previous pixel data
                        obj->prevPixelData[x_pix + y_pix * obj->width] = WORLD[(*obj->y + y_pix)][(*obj->x + x_pix)];
                        WORLD[(*obj->y + y_pix)][(*obj->x + x_pix)] = pixel;
                        continue;
                    }
                    if ((*obj->x + x_pix) >= SCREEN_WIDTH*2) {
                        // Save the previous pixel data
                        obj->prevPixelData[x_pix + y_pix * obj->width] = WORLD[(*obj->y + y_pix)][(*obj->x + x_pix)];
                        WORLD[(*obj->y + y_pix)][(*obj->x + x_pix)] = pixel;
                        continue;
                    }
                    // Calculate address for the pixel in the pixel buffer
                    volatile short int *one_pixel_address;
                    one_pixel_address = (volatile short int *)pixel_buffer_start + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix - SCREEN_WIDTH) << 0);
                    // Save the previous pixel data
                    obj->prevPixelData[x_pix + y_pix * obj->width] = *one_pixel_address; //takes whatever inside buffer and store in prev pixel data

                    // Write the new pixel data to Buffer1
                    volatile short int *buffer1_pixel_address;
                    buffer1_pixel_address = (volatile short int *)&Buffer1 + ((*obj->y + y_pix) << 9) + ((*obj->x + x_pix - SCREEN_WIDTH) << 0);
                    *buffer1_pixel_address = pixel;
                    
                    // Write the new pixel data to Buffer2
                    volatile short int *buffer2_pixel_address;
                    buffer2_pixel_address = (volatile short int *)&Buffer2 + ((*obj->y + y_pix) << 9) + ((*obj->x + x_pix - SCREEN_WIDTH) << 0);
                    *buffer2_pixel_address = pixel;
                    
                }
                else if (currentView == RIGHTVIEW) {
                    if ((*obj->x + x_pix) < SCREEN_WIDTH*2) {
                        // Save the previous pixel data
                        obj->prevPixelData[x_pix + y_pix * obj->width] = WORLD[(*obj->y + y_pix)][(*obj->x + x_pix)];
                        WORLD[(*obj->y + y_pix)][(*obj->x + x_pix)] = pixel;
                        continue;
                    }
                    if ((*obj->x + x_pix) >= SCREEN_WIDTH*3) {
                        continue;
                    }
                    // Calculate address for the pixel in the pixel buffer
                    volatile short int *one_pixel_address;
                    one_pixel_address = (volatile short int *)pixel_buffer_start + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix - SCREEN_WIDTH*2) << 0);
                    // Save the previous pixel data
                    obj->prevPixelData[x_pix + y_pix * obj->width] = *one_pixel_address; //takes whatever inside buffer and store in prev pixel data

                    // Write the new pixel data to Buffer1
                    volatile short int *buffer1_pixel_address;
                    buffer1_pixel_address = (volatile short int *)&Buffer1 + ((*obj->y + y_pix) << 9) + ((*obj->x + x_pix - SCREEN_WIDTH*2) << 0);
                    *buffer1_pixel_address = pixel;
                    
                    // Write the new pixel data to Buffer2
                    volatile short int *buffer2_pixel_address;
                    buffer2_pixel_address = (volatile short int *)&Buffer2 + ((*obj->y + y_pix) << 9) + ((*obj->x + x_pix - SCREEN_WIDTH*2) << 0);
                    *buffer2_pixel_address = pixel;
                    
                    
                }
            }
        }
    }
}

// rendering the prev data from the asset (renders yellow backgrround)
void renderOut(GameObject *obj) {
    if (obj->currentlyRendered == 1) {
        for (int y_pix = 0; y_pix < obj->height; y_pix++) {
            if (((obj->prevY + y_pix) > SCREEN_HEIGHT) || ((obj->prevY + y_pix) < 0) ){
                continue;
            }
            for (int x_pix = 0; x_pix < obj->width; x_pix++) {
                short int prevPixel = obj->prevPixelData[x_pix + y_pix * obj->width];
                if (prevPixel != -1) {
                    // Rendering new pixels onto buffer and onto other views.
                    if (currentView == LEFTVIEW) {
                        if ((obj->prevX + x_pix) < 0) {
                            continue;
                        }
                        if ((obj->prevX + x_pix) >= SCREEN_WIDTH) {
                            WORLD[(obj->prevY + y_pix)][(obj->prevX + x_pix)] = prevPixel;
                            continue;
                        }
                        // Write the new pixel data to Buffer1
                        volatile short int *buffer1_pixel_address;
                        buffer1_pixel_address = (volatile short int *)&Buffer1 + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix) << 0);
                        *buffer1_pixel_address = prevPixel;

                        // Write the new pixel data to Buffer2
                        volatile short int *buffer2_pixel_address;
                        buffer2_pixel_address = (volatile short int *)&Buffer2 + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix) << 0);
                        *buffer2_pixel_address = prevPixel;

                    }
                    else if (currentView == MIDDLEVIEW) {
                        if ((obj->prevX + x_pix) < SCREEN_WIDTH) {
                            WORLD[(obj->prevY + y_pix)][(obj->prevX + x_pix)] = prevPixel;
                            continue;
                        }
                        if ((obj->prevX + x_pix) >= SCREEN_WIDTH*2) {
                            WORLD[(obj->prevY + y_pix)][(obj->prevX + x_pix)] = prevPixel;
                            continue;
                        }
                        // Write the new pixel data to Buffer1
                        volatile short int *buffer1_pixel_address;
                        buffer1_pixel_address = (volatile short int *)&Buffer1 + ((obj->prevY + y_pix) << 9) + (((obj->prevX + x_pix) - SCREEN_WIDTH) << 0);
                        *buffer1_pixel_address = prevPixel;

                        // Write the new pixel data to Buffer2
                        volatile short int *buffer2_pixel_address;
                        buffer2_pixel_address = (volatile short int *)&Buffer2 + ((obj->prevY + y_pix) << 9) + (((obj->prevX + x_pix) - SCREEN_WIDTH) << 0);
                        *buffer2_pixel_address = prevPixel;

                    }
                    else if (currentView == RIGHTVIEW) {
                        if ((obj->prevX + x_pix) < SCREEN_WIDTH*2) {
                            WORLD[(obj->prevY + y_pix)][(obj->prevX + x_pix)] = prevPixel;
                            continue;
                        }
                        if ((obj->prevX + x_pix) >= SCREEN_WIDTH*3) {
                            continue;
                        }
                        // Write the new pixel data to Buffer1
                        volatile short int *buffer1_pixel_address;
                        buffer1_pixel_address = (volatile short int *)&Buffer1 + ((obj->prevY + y_pix) << 9) + (((obj->prevX + x_pix) - SCREEN_WIDTH*2) << 0);
                        *buffer1_pixel_address = prevPixel;

                        // Write the new pixel data to Buffer2
                        volatile short int *buffer2_pixel_address;
                        buffer2_pixel_address = (volatile short int *)&Buffer2 + ((obj->prevY + y_pix) << 9) + (((obj->prevX + x_pix) - SCREEN_WIDTH*2) << 0);
                        *buffer2_pixel_address = prevPixel;

                    }



                    // // Restore the previous pixel data in Buffer1
                    // volatile short int *buffer1_pixel_address;
                    // buffer1_pixel_address = (volatile short int *)&Buffer1 + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix) << 0);
                    // *buffer1_pixel_address = prevPixel;

                    // // Restore the previous pixel data in Buffer2
                    // volatile short int *buffer2_pixel_address;
                    // buffer2_pixel_address = (volatile short int *)&Buffer2 + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix) << 0);
                    // *buffer2_pixel_address = prevPixel;
                }
            }
        }
    }
    obj->currentlyRendered = 0; //set obj to 0 since we are not rendering it
}

int checkCollision(GameObject *a, GameObject *b) {
    if (!(*a->collidable) || !(*b->collidable)) return 0; // Ignore non-collidable objects

    return (*(a->x) < *(b->x) + b->width &&
            *(a->x) + a->width > *(b->x) &&
            *(a->y) < *(b->y) + b->height &&
            *(a->y) + a->height > *(b->y));
}

void resolveCollision(GameObject *a, GameObject *b) {
    if (*(a->x) < *(b->x)) *(a->x) -= 5;
    else *(a->x) += 5;

    if (*(a->y) < *(b->y)) *(a->y) -= 5;
    else *(a->y) += 5;
}

void initializeGeneralObject(GameObject **gameObject, short int *asset, int collidable, int x, int y, int width, int height) {
    (*gameObject) = (GameObject*)malloc(sizeof(GameObject));
    short int* gameObjectPrevData = malloc(sizeof(short int) * width * height);

    (*gameObject)->x = malloc(sizeof(int));
    (*gameObject)->y = malloc(sizeof(int));

    (*gameObject)->velocityX = malloc(sizeof(double));
    (*gameObject)->velocityY = malloc(sizeof(double));
    (*gameObject)->collidable = malloc(sizeof(int));
    (*gameObject)->width = width;
    (*gameObject)->height = height;
    (*gameObject)->asset = asset;
    (*gameObject)->prevPixelData = gameObjectPrevData;

    *((*gameObject)->collidable) = collidable;
    *((*gameObject)->x) = x;
    *((*gameObject)->y) = y;
    *((*gameObject)->velocityX) = 0;
    *((*gameObject)->velocityY) = 0;

}

void destroyGeneralObject(GameObject *obj) {
    if (obj == NULL) return;

    free(obj->x);
    free(obj->y);
    free(obj->velocityX);
    free(obj->velocityY);
    free(obj->collidable);
    free(obj->prevPixelData);
    free(obj); 
}

