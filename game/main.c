#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "loadAssets.c"
#include "objecthandler.c"

// Global Variables --------------------------------------------------------------------

// Pixel Location for (0,0)
volatile int pixel_buffer_start;

// Front and Back Buffers of size 480 rows, 640 columns (640x480)
short int Buffer1[480][640];
short int Buffer2[480][640];

// Internal Buffers
short int backgroundBuffer[480][640]; // Background Layer (Static Terrain, Decorations)
short int midgroundBuffer[480][640]; // Midground Layer (Buildings, platforms, large objects)
short int entityBuffer[480][640]; //Entity Layer (Characters, projectiles, items)
short int uiBuffer[480][640]; // UI Layer (Health Bars, Menus, etc)

//---------------------------------------------------------------------------------------

// Function Declarations ----------------------------------------------------------------

// Screen Functions
void clear_screen();
void wait_for_vsync();

// Drawing Functions
void plot_pixel(int x, int y, short int line_color);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void draw_6x6_box(int x0, int y0, short int box_color); 

// Helper Functions
void swap(int* num1, int* num2);


//----------------------------------------------------------------------------------------

int main(void)
{
    volatile int * buffer_register = (int *)0xFF203020;
    
    /* set front pixel buffer to Buffer 1 */
    *(buffer_register + 1) = (int) &Buffer1; // first store the address in the  back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    // after this functin the back_buffer register content,
    // has swapped with the front_buffer register content
    
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *buffer_register;
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    /* set back pixel buffer to Buffer 2 */
    *(buffer_register + 1) = (int) &Buffer2;
    // *(buffer_register + 1) = (int) &Buffer1; // Making it one buffer only.
    pixel_buffer_start = *(buffer_register + 1); // we draw on the back buffer
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    // Game Function ----------------------------------------------------------------------
    while (1)
    {
        /* Erase any boxes and lines that were drawn in the last iteration */
        // clear_screen();


        

        for (int y_pix = 0; y_pix < LEFTMOVEMENT_HEIGHT; y_pix++){
            for (int x_pix = 0; x_pix < LEFTMOVEMENT_WIDTH; x_pix++){
                if(leftmovement[x_pix+y_pix*LEFTMOVEMENT_WIDTH] != -1) {
                    plot_pixel(x_pix + 10, y_pix, leftmovement[x_pix+y_pix*LEFTMOVEMENT_WIDTH]);
                }
            }
        }

        for (int y_pix = 0; y_pix < RIGHTMOVEMENT_HEIGHT; y_pix++){
            for (int x_pix = 0; x_pix < RIGHTMOVEMENT_WIDTH; x_pix++){
                if(rightmovement[x_pix+y_pix*RIGHTMOVEMENT_WIDTH] != -1) {
                    plot_pixel(x_pix + 40, y_pix, rightmovement[x_pix+y_pix*RIGHTMOVEMENT_WIDTH]);
                }
            }
        }


        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(buffer_register + 1); // new back buffer
    }
}

// Functions ------------------------------------------------------------------------------

// Screen Functions
void clear_screen() {
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 480; y++) {
            // 0x0000 represents:
            // 0 red (3rd hex digit)
            // 0 green (2nd hex )
            // 0 blue (binary 0 to 4)
            plot_pixel(x,y,0x000);
        }
    }
}

void wait_for_vsync(){
    // Store 1 into buffer register to enable swaps
    volatile int* buffer_register = (int *)0xFF203020;
    *buffer_register = 1;
    
    // obtaining value stored in status register
    // if 1 then swap is ongoing, if 0 then swap completed
    volatile int* status_register = (buffer_register + 3);
    int status_register_value = *(status_register);
        
    // Poll for the S bit in status register until it becomes 0.
    // When it becomes 0, then finish function, otherwise hold it there.
    while((status_register_value & 0x1) != 0){
        status_register_value = *(status_register); // Polling
    }
}

// Drawing Functions
void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;
    one_pixel_address = (volatile short int*)pixel_buffer_start + (y << 9) + x;
    *one_pixel_address = line_color;
}

void draw_line(int x0, int y0, int x1, int y1, short int line_color) {
    // If is_steep then we want to use 
    bool is_steep = abs(y1-y0) > abs(x1-x0);
    
    // Basically flips the algorithm such that the x-axis and y-axis are swapped
    // but only if it is steep.
    if (is_steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    
    // Makes sure x1 is the greater value
    // If swap needs to occur to ensure this, then we must swap the corresponding
    // y values as well.
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }
    
    int y_step;
    // Don't need abs here, because above be made sure that x1 > x0
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    // The formula for error E =  
    int error = -(deltax / 2);
    int y = y0;
    
    // If y1 > y0, step is positive (going up)
    if (y0 < y1) {
        y_step = 1;   
    }
    else { // If y0 > y1, step is negative (going down)
        y_step = -1;
    }
    
    // For all x values from x0 to x1 (inclusive)
    for (int x = x0; x <= x1; x++) {
        if (is_steep) {
            // Here is where we correct orient it such that we flip back
            // the (x,y) variables due to the intial swap if is_steep = true.
            plot_pixel(y, x, line_color);
        }
        else {
            plot_pixel(x, y, line_color);
        }
        
        // Calculating the error for the current pixel.
        // With the calculation we will determine if we want to increase our 
        // y-value (if the line is closer to the diagonal pixel) or keep it
        // the same (if the line is closer to the horizontal pixel)
        error = error + deltay;
        // error > 0, if the line is closer to the diagonal pixel
        if (error > 0) {
            y += y_step;
            error -= deltax;
        }           
    }
}

void draw_6x6_box(int x0, int y0, short int box_color){
    //draw a 2 2 pixel wide lines stacked
    for (int i = 0; i <= 3; i++) {
        draw_line(x0-3,y0 + i,x0+3,y0 + i, box_color);
    }
    for (int i = 1; i <= 3; i++) {
        draw_line(x0-3,y0 - i,x0+3,y0 - i, box_color);
    }
}

// Helper Swap Function
void swap(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

//-----------------------------------------------------------------------------------------
