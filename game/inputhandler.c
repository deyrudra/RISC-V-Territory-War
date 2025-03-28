#include "inputhandler.h"

const char* gameControls[] = {
    "Move_Left", // 0
    "Move_Right", // 1
    "Move_Jump", // 2
    "Move_Left_Stop", // 3
    "Move_Right_Stop", // 4
    "Move_Jump_Stop", // 5
    "Stay", // 6
    // ...
};
volatile int* ps2_ptr = (int*)PS2_BASE;
uint8_t byte1 = 0, byte2 = 0, byte3 = 0;
int ps2_data, RVALID;


void poll_start_input(){
    printf("Welcome to Territory War!\n");
    printf("Press Enter to Start\n");
    
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
    ps2_data = *ps2_ptr;  // Read data from PS/2 port
    RVALID = ps2_data & 0x8000;

    // SWITCH TO WASD if buffer overflow becomes a problem

    if (RVALID) {
        byte1 = byte2;
        byte2 = byte3;
        byte3 = ps2_data & 0xFF;

        // Arrow Keys
        if (byte1 == 0xE0) {  // Extended key
            switch (byte2) {
                case 0x75: // Up Arrow (W)
                    return gameControls[2];
                case 0x72: // Down Arrow (S)
                    break;
                case 0x6B: // Left Arrow (A)
                    return gameControls[0];
                case 0x74: // Right Arrow (D)
                    return gameControls[1];
                case 0xF0:  // Break code detected
                    if (byte3 == 0x75) return gameControls[5]; // Up Arrow Released
                    else if (byte3 == 0x72) printf("Down arrow released!\n"); // Down Arrow Released
                    else if (byte3 == 0x6B) return gameControls[3]; // Left Arrow Released
                    else if (byte3 == 0x74) return gameControls[4]; // Right Arrow Released
                    break;
            }
        } else if (byte1 == 0x1E) {
            if (byte2 == 0xF0) {
                return gameControls[6]; //user wants to stay
            }
        }

    // } else if (byte3 == 0x1E) {  // User pressed 2
    //     if (byte2 == 0xF0) {
    //         printf("You selected stay\n");
    //         end_turn = true;
    //         break;
    //     }
    // }

    }
    
    return NULL;
}

void clearPS2Fifo(){
    while(1){
        ps2_data = *ps2_ptr;  // Read data from PS/2 port
        RVALID = ps2_data & 0x8000;

        int numItemsInFIFO = ps2_data & 0xFFFF0000;
        printf("top of loop: # items is %d\n", numItemsInFIFO);

        if(numItemsInFIFO > 0){
            int tempData = ps2_data & 0xFF;
            printf("after tempData: # items is %d\n", numItemsInFIFO);

        }
        else{
            printf("cleared: # items is %d\n", numItemsInFIFO);
            return;
        }
    }
    


}

