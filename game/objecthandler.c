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

    // Render the object into the pixel buffer
    for (int y_pix = 0; y_pix < obj->height; y_pix++) {
        if (((*obj->y + y_pix) > SCREEN_HEIGHT) || ((*obj->y + y_pix) < 0) ){
            continue;
        }
        for (int x_pix = 0; x_pix < obj->width; x_pix++) {
            if (((*obj->x + x_pix) > SCREEN_WIDTH) || ((*obj->x + x_pix) < 0) ){
                if (currentRender == LEFTVIEW) {
                    printf("LEFTVIEW\n");
                }
                continue;
            }
            short int pixel = obj->asset[x_pix + y_pix * obj->width];
            if (pixel != -1) {
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
        }
    }
}

// rendering the prev data from the asset (renders yellow backgrround)
void renderOut(GameObject *obj) {
    if (obj->currentlyRendered == 1) {
        for (int y_pix = 0; y_pix < obj->height; y_pix++) {
            for (int x_pix = 0; x_pix < obj->width; x_pix++) {
                int prevPixel = obj->prevPixelData[x_pix + y_pix * obj->width];
                if (prevPixel != -1) {
                    // Restore the previous pixel data in Buffer1
                    volatile short int *buffer1_pixel_address;
                    buffer1_pixel_address = (volatile short int *)&Buffer1 + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix) << 0);
                    *buffer1_pixel_address = prevPixel;

                    // Restore the previous pixel data in Buffer2
                    volatile short int *buffer2_pixel_address;
                    buffer2_pixel_address = (volatile short int *)&Buffer2 + ((obj->prevY + y_pix) << 9) + ((obj->prevX + x_pix) << 0);
                    *buffer2_pixel_address = prevPixel;
                }
            }
        }
    } else {
        obj->currentlyRendered = 0; //set obj to 0 since we are not rendering it
    }
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



