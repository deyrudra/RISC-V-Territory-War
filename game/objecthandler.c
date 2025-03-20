// Define GameObject structure
typedef struct {
    int x, y;        // Position
    int width, height; // Size
    int collidable;  // 1 for collidable, 0 for non-collidable
    int velocityX, velocityY; // Velocity for movement
    int * asset;
    int * layer;
} GameObject;

static void renderIn(GameObject *obj) {
    for (int y_pix = 0; y_pix < obj->height; y_pix++){
        for (int x_pix = 0; x_pix < obj->width; x_pix++){
            short int pixel = obj->asset[x_pix+y_pix*obj->width];
            if(pixel != -1) {
                // plot_pixel(x_pix + obj->x, y_pix + obj->y, pixel);
                obj->layer[x_pix + obj->x, y_pix + obj->y] = pixel;
            }
        }
    }
}

static void renderOut(GameObject *obj) {
    for (int y_pix = 0; y_pix < obj->height; y_pix++){
        for (int x_pix = 0; x_pix < obj->width; x_pix++){
            int pixel = obj->asset[x_pix+y_pix*obj->width];
            if(pixel != -1) {
                plot_pixel(x_pix + obj->x, y_pix + obj->y, pixel);
            }
        }
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
