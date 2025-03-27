// renderhandler.c

#include "renderhandler.h"

// Buffer Register and Pixel Buffer Start
volatile int* buffer_register = (int*)0xFF203020;
volatile int pixel_buffer_start;

// Front and Back Buffers of size SCREEN_HEIGHT rows, SCREEN_WIDTH columns
short int Buffer1[480][640];
short int Buffer2[480][640];

// World Save Data Array
short int WORLD[WORLD_HEIGHT][WORLD_WIDTH];
short int * LEFT[SCREEN_HEIGHT][SCREEN_WIDTH];
short int * MIDDLE[SCREEN_HEIGHT][SCREEN_WIDTH];
short int * RIGHT[SCREEN_HEIGHT][SCREEN_WIDTH];

RenderView currentRender = LEFTVIEW;

void initializeWorld() {
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // LEFT points to first 320 columns (0-319)
        LEFT[y][x] = &WORLD[y][x];
        
        // MIDDLE points to middle 320 columns (320-639)
        MIDDLE[y][x] = &WORLD[y][x + 320];
        
        // RIGHT points to last 320 columns (640-959)
        RIGHT[y][x] = &WORLD[y][x + 640];
    }
  }
}

void renderLeft() {
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        short int pixel_value = *LEFT[y][x];
        plot_pixel(x, y, pixel_value); // Render at (x, y)
    }
  }
}

void renderMiddle() {
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        short int pixel_value = *MIDDLE[y][x];
        plot_pixel(x, y, pixel_value); // Render at (x, y)
    }
  }
}

void renderRight() {
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        short int pixel_value = *RIGHT[y][x];
        plot_pixel(x, y, pixel_value); // Render at (x, y)
    }
  }
}

void saveLeft() {
  // Loop through this x and y of screen resolution
  for (int y_pix = 0; y_pix < SCREEN_HEIGHT; y_pix++) {
    for (int x_pix = 0; x_pix < SCREEN_WIDTH; x_pix++) {
      // Calculate address for the pixel in the pixel buffer
      volatile short int *one_pixel_address;
      one_pixel_address = (volatile short int *)pixel_buffer_start + (y_pix << 9) + (x_pix << 0);

      // Save the previous pixel data
      *(LEFT[y_pix][x_pix]) = *one_pixel_address; //takes whatever inside buffer and store in prev pixel data
    }
  }
}

void saveMiddle() {
  // Loop through this x and y of screen resolution
  for (int y_pix = 0; y_pix < SCREEN_HEIGHT; y_pix++) {
    for (int x_pix = 0; x_pix < SCREEN_WIDTH; x_pix++) {
      // Calculate address for the pixel in the pixel buffer
      volatile short int *one_pixel_address;
      one_pixel_address = (volatile short int *)pixel_buffer_start + (y_pix << 9) + (x_pix << 0);

      // Save the previous pixel data
      *(MIDDLE[y_pix][x_pix]) = *one_pixel_address; //takes whatever inside buffer and store in prev pixel data
    }
  }
}

void saveRight() {
  // Loop through this x and y of screen resolution
  for (int y_pix = 0; y_pix < SCREEN_HEIGHT; y_pix++) {
    for (int x_pix = 0; x_pix < SCREEN_WIDTH; x_pix++) {
      // Calculate address for the pixel in the pixel buffer
      volatile short int *one_pixel_address;
      one_pixel_address = (volatile short int *)pixel_buffer_start + (y_pix << 9) + (x_pix << 0);

      // Save the previous pixel data
      *(RIGHT[y_pix][x_pix]) = *one_pixel_address; //takes whatever inside buffer and store in prev pixel data
    }
  }
}

// Screen Functions
void clear_screen() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
        plot_pixel(x, y, 0x0000);
        }
    }
}

void plot_pixel(int x, int y, short int pixel) {
  // Write the new pixel data to Buffer1
  volatile short int *buffer1_pixel_address;
  buffer1_pixel_address = (volatile short int *)&Buffer1 + (y << 9) + (x << 0);
  *buffer1_pixel_address = pixel;

  // Write the new pixel data to Buffer2
  volatile short int *buffer2_pixel_address;
  buffer2_pixel_address = (volatile short int *)&Buffer2 + (y << 9) + (x << 0);
  *buffer2_pixel_address = pixel;

}

void wait_for_vsync() {
    // Store 1 into buffer register to enable swaps
    volatile int* buffer_register = (int*)0xFF203020;
    *buffer_register = 1;
  
    // obtaining value stored in status register
    // if 1 then swap is ongoing, if 0 then swap completed
    volatile int* status_register = (buffer_register + 3);
    int status_register_value = *(status_register);
  
    // Poll for the S bit in status register until it becomes 0.
    // When it becomes 0, then finish function, otherwise hold it there.
    while ((status_register_value & 0x1) != 0) {
      status_register_value = *(status_register);  // Polling
    }
  }

void initializeBuffers() {
  /* set front pixel buffer to Buffer 1 */
  *(buffer_register + 1) = (int)&Buffer1;  // first store the address in the  back buffer
  /* now, swap the front/back buffers, to set the front buffer location */
  wait_for_vsync();
  // after this functin the back_buffer register content,
  // has swapped with the front_buffer register content

  /* initialize a pointer to the pixel buffer, used by drawing functions */
  pixel_buffer_start = *buffer_register;
  clear_screen();  // pixel_buffer_start points to the pixel buffer

  /* set back pixel buffer to Buffer 2 */
  *(buffer_register + 1) = (int)&Buffer2;
  // *(buffer_register + 1) = (int) &Buffer1; // Making it one buffer only.
  pixel_buffer_start = *(buffer_register + 1);  // we draw on the back buffer
  clear_screen();  // pixel_buffer_start points to the pixel buffer


}