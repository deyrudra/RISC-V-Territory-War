// renderhandler.h

#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

// Global Variables
extern volatile int* buffer_register;
extern volatile int pixel_buffer_start;

extern short int Buffer1[480][640];
extern short int Buffer2[480][640];

void wait_for_vsync();
void clear_screen();
void plot_pixel(int x, int y, short int line_color);

#endif // RENDERHANDLER_H