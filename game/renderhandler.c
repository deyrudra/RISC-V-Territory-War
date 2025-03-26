// renderhandler.c

#include "renderhandler.h"

// Buffer Register and Pixel Buffer Start
volatile int* buffer_register = (int*)0xFF203020;
volatile int pixel_buffer_start;

// Front and Back Buffers of size SCREEN_HEIGHT rows, SCREEN_WIDTH columns
short int Buffer1[480][640];
short int Buffer2[480][640];

// Screen Functions
void clear_screen() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
        // 0x0000 represents:
        // 0 red (3rd hex digit)
        // 0 green (2nd hex )
        // 0 blue (binary 0 to 4)
        plot_pixel(x, y, 0x0000);
        }
    }
}

void plot_pixel(int x, int y, short int line_color) {
    if (line_color != -1) {
      volatile short int* one_pixel_address;
      one_pixel_address =
          (volatile short int*)pixel_buffer_start + (y << 9) + (x << 0);
      *one_pixel_address = line_color;
    }
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