#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "loadAssets.c"
#include "objecthandler.h"
#include "inputhandler.h"
#include "movementhandler.h"

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

// Global Variables --------------------------------------------------------------------

// Buffer Register and Pixel Buffer Start
volatile int * buffer_register = (int *)0xFF203020;
volatile int pixel_buffer_start;

// Front and Back Buffers of size SCREEN_HEIGHT rows, SCREEN_WIDTH columns (SCREEN_WIDTHxSCREEN_HEIGHT)
short int Buffer1[480][640];
short int Buffer2[480][640];

// global pointers to memory mapped IO
volatile int* ps2_ptr = (int*)PS2_BASE;

// Keyboard Input Polling Bytes
uint8_t byte1 = 0, byte2 = 0, byte3 = 0;

// Global Game Objects
GameObject *leftMovementObj;
GameObject *rightMovementObj;
GameObject *backgroundObj;
GameObject *mainMenuTitleObj;

// Global Game Controls
const char* gameControls[] = {
    "Move_Left",
    "Move_Right",
    "Move_Jump",
    // ...
  };
  

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

    // Setting Some Initial Object Data.
    // leftMovementObj = (GameObject *)malloc(sizeof(GameObject));
    // int leftmovementPrevData[LEFTMOVEMENT_HEIGHT][LEFTMOVEMENT_WIDTH];
    // leftMovementObj->x = 80;
    // leftMovementObj->y = 80;
    // leftMovementObj->asset = &leftmovement;
    // leftMovementObj->collidable = 0;
    // leftMovementObj->height = LEFTMOVEMENT_HEIGHT;
    // leftMovementObj->width = LEFTMOVEMENT_WIDTH;
    // leftMovementObj->prevPixelData = &leftmovementPrevData;

    // rightMovementObj = (GameObject *)malloc(sizeof(GameObject));
    // int rightmovementPrevData[RIGHTMOVEMENT_HEIGHT][RIGHTMOVEMENT_WIDTH];
    // rightMovementObj->x = 20;
    // rightMovementObj->y = 50;
    // rightMovementObj->asset = &rightmovement;
    // rightMovementObj->collidable = 0;
    // rightMovementObj->height = RIGHTMOVEMENT_HEIGHT;
    // rightMovementObj->width = RIGHTMOVEMENT_WIDTH;
    // rightMovementObj->prevPixelData = &rightmovementPrevData;

    backgroundObj = (GameObject *)malloc(sizeof(GameObject));
    int backgroundPrevData[BACKGROUND_HEIGHT][BACKGROUND_WIDTH];
    backgroundObj->asset = &background;
    backgroundObj->collidable = 0;
    backgroundObj->height = BACKGROUND_HEIGHT;
    backgroundObj->width = BACKGROUND_WIDTH;
    backgroundObj->prevPixelData = &backgroundPrevData;

    mainMenuTitleObj = (GameObject *)malloc(sizeof(GameObject));
    int mainMenuTitlePrevData[MAIN_MENU_TITLE_HEIGHT][MAIN_MENU_TITLE_WIDTH];
    mainMenuTitleObj->x = &(int){SCREEN_WIDTH - MAIN_MENU_TITLE_WIDTH - 40};
    mainMenuTitleObj->y = &(int){10};
    mainMenuTitleObj->asset = &main_menu_title;
    mainMenuTitleObj->collidable = 0;
    mainMenuTitleObj->height = MAIN_MENU_TITLE_HEIGHT;
    mainMenuTitleObj->width = MAIN_MENU_TITLE_WIDTH;
    mainMenuTitleObj->prevPixelData = &mainMenuTitlePrevData;

    // Test Player
    Character player;
    initializeCharacter(&player, &idle, &leftmovement, &rightmovement, &jump, &idlePrev, &leftmovementPrev, &rightmovementPrev, &jumpPrev);

    // Rendering Background
    for (int ypos = 0; ypos <= SCREEN_WIDTH + 40; ypos += 40) {
        for (int xpos = 0; xpos <= SCREEN_HEIGHT + 40; xpos += 40) {
            backgroundObj->x = &xpos;
            backgroundObj->y = &ypos;
            renderIn(backgroundObj);
        }
    }

    // Rendering Main Menu Title
    renderIn(mainMenuTitleObj);

    poll_start_input();

    int count = 0;
    // Game Logic Loop ----------------------------------------------------------------------
    while (1)
    {
        // Input Handler Logic
        char* control = single_poll_input();

        if (control != NULL) {
            printf("%s\n", control);
        }

        moveCharacter(&player, control);
        drawCharacter(&player);

        
        // renderIn(player.idleCharacter);
        // renderIn(player.walkLeftCharacter);
        // renderIn(player.walkRightCharacter);
        
        
        // renderIn(leftMovementObj);
       
        // count++;

        // if (count % 100) {
        //     // rightMovementObj->x += 5;
        //     renderOut(rightMovementObj);
        //     renderIn(rightMovementObj);

        // }

        // if (count % 200) {
        //     // leftMovementObj->x += 5;
        //     // leftMovementObj->y += 5;
        //     renderOut(leftMovementObj);
        //     renderIn(leftMovementObj);

        // }


        
        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(buffer_register + 1); // new back buffer
    }

    free(leftMovementObj);
    free(rightMovementObj);
}

// Functions ------------------------------------------------------------------------------

// Screen Functions
void clear_screen() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            // 0x0000 represents:
            // 0 red (3rd hex digit)
            // 0 green (2nd hex )
            // 0 blue (binary 0 to 4)
            plot_pixel(x,y,0x0000);
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

// Drawing Functions
void plot_pixel(int x, int y, short int line_color)
{
    if (line_color != -1) {
        volatile short int *one_pixel_address;
        one_pixel_address = (volatile short int*)pixel_buffer_start + (y << 9) + (x << 0);
        *one_pixel_address = line_color;
    }
}