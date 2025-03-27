// renderhandler.h

#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

#define WORLD_WIDTH 960
#define WORLD_HEIGHT 240

// Global Variables
extern volatile int* buffer_register;
extern volatile int pixel_buffer_start;

extern short int Buffer1[480][640];
extern short int Buffer2[480][640];

// World Array
extern short int WORLD[WORLD_HEIGHT][WORLD_WIDTH];
extern short int * LEFT[SCREEN_HEIGHT][SCREEN_WIDTH];
extern short int * MIDDLE[SCREEN_HEIGHT][SCREEN_WIDTH];
extern short int * RIGHT[SCREEN_HEIGHT][SCREEN_WIDTH];

typedef enum {LEFTVIEW, MIDDLEVIEW, RIGHTVIEW} RenderView;

extern RenderView currentView;
extern RenderView prevView;


void initializeWorld();
void renderLeft();
void renderMiddle();
void renderRight();
void saveLeft();
void saveMiddle();
void saveRight();


void wait_for_vsync();
void clear_screen();
void plot_pixel(int x, int y, short int pixel);
void initializeBuffers();



#endif // RENDERHANDLER_H