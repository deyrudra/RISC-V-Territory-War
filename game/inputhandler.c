#include "inputhandler.h"

void poll_start_input(){
    printf("Welcome to Territory War!\n");
    printf("Press Enter to Start\n");

    int ps2_data, RVALID;
    
    // Poll user to hit enter key
    while (1) {
        ps2_data = *ps2_ptr;
        RVALID = ps2_data & 0x8000;

        if (RVALID) {
            byte1 = byte2;
            byte2 = byte3;
            byte3 = ps2_data & 0xFF;
        }

        if (byte2 == 0xF0) {
            if (byte3 == 0x5A) {
                break;
            }
        }
    }
    byte1 = byte2 = byte3 = 0;

    printf("Game started!\n\n");

}

char* single_poll_input() {
    int ps2_data, RVALID;
    ps2_data = *ps2_ptr;  // Read data from PS/2 port
    RVALID = ps2_data & 0x8000;

    if (RVALID) {
        byte1 = byte2;
        byte2 = byte3;
        byte3 = ps2_data & 0xFF;

        // Arrow Keys
        if (byte1 == 0xE0) {  // Extended key
            switch (byte2) {
                case 0x75: // Up Arrow
                    return gameControls[2];
                case 0x72: // Down Arrow
                    break;
                case 0x6B: // Left Arrow
                    return gameControls[0];
                case 0x74: // Right Arrow
                    return gameControls[1];
                case 0xF0:  // Break code detected
                    // if (byte3 == 0x75) printf("Up arrow released!\n");
                    // else if (byte3 == 0x72) printf("Down arrow released!\n");
                    // else if (byte3 == 0x6B) printf("Left arrow released!\n");
                    // else if (byte3 == 0x74) printf("Right arrow released!\n");
                    break;
            }
        }
    }
    
    return NULL;
}

