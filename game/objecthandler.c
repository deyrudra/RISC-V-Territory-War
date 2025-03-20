// Global Variables
// extern volatile int pixel_buffer_start;
extern short int Buffer1[480][640];
extern short int Buffer2[480][640];
extern volatile int pixel_buffer_start;

// Define GameObject structure
typedef struct {
    int x, y; // Position
    int prevX, prevY; // Position
    int width, height; // Size
    int collidable; // 1 for collidable, 0 for non-collidable
    int velocityX, velocityY; // Velocity for movement
    int * asset;
    int * prevPixelData;
    int currentlyRendered;
} GameObject;

static void resetPrevPixelData(GameObject *obj) {
    for (int y_pix = 0; y_pix < obj->height; y_pix++){
        for (int x_pix = 0; x_pix < obj->width; x_pix++){
            obj->prevPixelData[x_pix+y_pix*obj->width] = -1;
        }
    }
}

static void renderIn(GameObject *obj) {
    // Saving Previous Pixe Data
    obj->prevX = obj->x;
    obj->prevY = obj->y;
    resetPrevPixelData(obj);

    // Setting rendered state
    obj->currentlyRendered = 1;

    for (int y_pix = 0; y_pix < obj->height; y_pix++){
        for (int x_pix = 0; x_pix < obj->width; x_pix++){
            short int pixel = obj->asset[x_pix+y_pix*obj->width];
            if(pixel != -1) {
                volatile short int *one_pixel_address;
                one_pixel_address = (volatile short int*)pixel_buffer_start + (obj->prevY + y_pix << 9) + obj->prevX + x_pix;
                short int prevPixel = *one_pixel_address;
                obj->prevPixelData[x_pix+y_pix*obj->width] = *one_pixel_address;
                
                volatile short int *buffer1_pixel_address;
                buffer1_pixel_address = (volatile short int*)&Buffer1 + ((obj->y + y_pix) << 9) + (obj->x + x_pix);
                *buffer1_pixel_address = pixel; 
                
                volatile short int *buffer2_pixel_address;
                buffer2_pixel_address = (volatile short int*)&Buffer2 + ((obj->y + y_pix) << 9) + (obj->x + x_pix);
                *buffer2_pixel_address = pixel; 
            }
        }
    }
}

static void renderOut(GameObject *obj) {
    if (obj->currentlyRendered == 1) {
        for (int y_pix = 0; y_pix < obj->height; y_pix++) {
            for (int x_pix = 0; x_pix < obj->width; x_pix++) {
                int prevPixel = obj->prevPixelData[x_pix+y_pix*obj->width];
                if (prevPixel != -1) {
                    // Erase from Buffer1
                    volatile short int *buffer1_pixel_address;
                    buffer1_pixel_address = (volatile short int*)&Buffer1 + ((obj->prevY + y_pix) << 9) + (obj->prevX + x_pix);
                    *buffer1_pixel_address = prevPixel; // Draw black pixel
                    // Erase from Buffer2
                    volatile short int *buffer2_pixel_address;
                    buffer2_pixel_address = (volatile short int*)&Buffer2 + ((obj->prevY + y_pix) << 9) + (obj->prevX + x_pix);
                    *buffer2_pixel_address = prevPixel; // Draw black pixel
                }
            }
        }
    }
    else {
        obj->currentlyRendered = 0;
    }
}

// Function to check collision between two game objects
static int checkCollision(GameObject *a, GameObject *b) {
    if (!a->collidable || !b->collidable) return 0; // Ignore non-collidable objects

    return (a->x < b->x + b->width  &&
            a->x + a->width > b->x  &&
            a->y < b->y + b->height &&
            a->y + a->height > b->y);
}

// Function to resolve basic collision by stopping movement
static void resolveCollision(GameObject *a, GameObject *b) {
    if (a->x < b->x) a->x -= 5;
    else a->x += 5;

    if (a->y < b->y) a->y -= 5;
    else a->y += 5;
}

