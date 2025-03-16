#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Global Variables --------------------------------------------------------------------

// Pixel Location for (0,0)
volatile int pixel_buffer_start;

// Front and Back Buffers of size 480 rows, 640 columns (640x480)
short int Buffer1[480][640];
short int Buffer2[480][640];

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

// Structs
typedef struct {
    unsigned int x, y;
    unsigned int rgb_565;
} Pixel;

typedef struct {
    Pixel data_array[240][320];
    int width;
    int height;
} Asset;

// Define and initialize the Asset object globally
Asset img = {
    .data_array = {
        {   // Row 0
            { .x = 0, .y = 0, .rgb_565 = 0xFFFF },  // Pixel (0,0)
            { .x = 1, .y = 0, .rgb_565 = 0x07E0 },  // Pixel (1,0)
            { .x = 2, .y = 0, .rgb_565 = 0xF800 }   // Pixel (2,0)
        },
        {   // Row 1
            { .x = 0, .y = 1, .rgb_565 = 0x001F },  // Pixel (0,1)
            { .x = 1, .y = 1, .rgb_565 = 0x07FF },  // Pixel (1,1)
            { .x = 2, .y = 1, .rgb_565 = 0xE07F }   // Pixel (2,1)
        }
    },
    .width = 3,
    .height = 2
};

// Assets Loading and Assets List
// Declare global variables as extern
extern Asset rocket;



//----------------------------------------------------------------------------------------

int main(void)
{
    volatile int * buffer_register = (int *)0xFF203020;
    // declare other variables(not shown)
    int N = 15;
    int x_pos[N], y_pos[N]; //tracking Middle pixel
    short int colour[N];
    int dx[N], dy[N];
    short int colours_list[10] = 
        {0xf800, 0xfd08, 0xf7c4,
        0xafec, 0x3ffc, 0x8e1f,
        0xfd76, 0xde5f, 0xfaff,
        0xffff}; 
    // initialize location and direction of rectangles(not shown)
    for (int i = 0; i < N; i++){
        // These generate object movement direction (steps) between -1 and 1, for both dx and dy.
        dx[i] = ((rand() % 2) * 2) - 1;
        dy[i] = ((rand() % 2) * 2) - 1;
        
        //rand() % (max-min+1) + min
        x_pos[i] = rand() % 320; // x position ranges from 0 to 319
        y_pos[i] = rand() % 240; // y position ranges from 0 to 239

        // Chooses a color form 0 to 9 in the colour array
        colour[i] = colours_list[rand() % 10];
    }
    
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
        clear_screen();
        
        // // code for drawing the boxes and lines (not shown)
        // for(int i = 0; i < N; i++){
            
        //     //draw a box at its determined position
        //     draw_6x6_box(x_pos[i], y_pos[i], colour[i]);
            
        //     //draw line from this box to the next box (indexing prevents out of bounds error when i == N-1)
        //     draw_line(x_pos[i], y_pos[i], x_pos[(i+1) % N], y_pos[(i+1) % N], colour[i]);
            
        //     // update box positions for next frame
        //     x_pos[i] += dx[i];
        //     y_pos[i] += dy[i];
            
        //     //check for collisions at edges and flip dx or dy for next frame
        //     if(x_pos[i] == 0 || x_pos[i] + 1 == 319){
        //         dx[i] *= -1;
        //     }
            
        //     if(y_pos[i] == 0 || y_pos[i]+1 == 239){
        //         dy[i] *= -1;
        //     }
        // }

        for (int y_pix = 0; y_pix < rocket.height; y_pix++){
            for (int x_pix = 0; x_pix < rocket.width; x_pix++){
                Pixel current_pixel = rocket.data_array[y_pix][x_pix];
                plot_pixel(current_pixel.x, current_pixel.y, current_pixel.rgb_565);
            }
        }

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(buffer_register + 1); // new back buffer
    }
}

// Functions ------------------------------------------------------------------------------

// Screen Functions
void clear_screen() {
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 240; y++) {
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
    one_pixel_address = (volatile short int*)pixel_buffer_start + (y << 10) + (x << 1);
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
