#include "inputhandler.h"

const char* gameControls[] = {
    "Move_Left", // 0
    "Move_Right", // 1
    "Move_Jump", // 2
    "Move_Left_Stop", // 3
    "Move_Right_Stop", // 4
    "Move_Jump_Stop", // 5
    "Stay", // 6
    "Face_Right_Grenade", // 7
    "Face_Left_Grenade", // 8
    "Rotate_Up_Grenade", // 9
    "Rotate_Up_Grenade_Stop", // 10
    "Rotate_Down_Grenade", // 11
    "Rotate_Down_Grenade_Stop", // 12
    "Throw_Grenade", // 13
    "Throw_Grenade_Stop", // 14

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

bool poll_move_or_stay_input(){
    while (1) {
        ps2_data = *ps2_ptr;
        RVALID = ps2_data & 0x8000;

        if (RVALID) {
            byte1 = byte2;
            byte2 = byte3;
            byte3 = ps2_data & 0xFF;
        }

        if (byte3 == 0x16) {  // User pressed 1
            if (byte2 == 0xF0) {
                printf("You selected move\n");
                byte1 = byte2 = byte3 = 0;
                return false;
            }
        } else if (byte3 == 0x1E) {  // User pressed 2
            if (byte2 == 0xF0) {
                printf("You selected stay\n");
                byte1 = byte2 = byte3 = 0;
                return true;
            }
        }
    }
}

bool poll_grenade_or_stay_input(){
    while (1) {
        ps2_data = *ps2_ptr;
        RVALID = ps2_data & 0x8000;

        if (RVALID) {
            byte1 = byte2;
            byte2 = byte3;
            byte3 = ps2_data & 0xFF;
        }

        if (byte3 == 0x16) {  // User pressed 1
            if (byte2 == 0xF0) {
                printf("You selected throw grenade\n");
                byte1 = byte2 = byte3 = 0;
                return false;
            }
        } else if (byte3 == 0x1E) {  // User pressed 2
            if (byte2 == 0xF0) {
                printf("You selected stay\n");
                byte1 = byte2 = byte3 = 0;
                return true;
            }
        }
    }
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
    }

    
    return NULL;
}

char* grenade_control_input(){
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
                case 0x75: // Up Arrow
                    return gameControls[9]; // rotate up grenade
                case 0x72: // Down Arrow (S)
                    return gameControls[11]; //rotate down grenade
                case 0x6B: // Left Arrow (A)
                    return gameControls[8]; // face left grenade
                case 0x74: // Right Arrow (D)
                    return gameControls[7]; // face right grenade
                case 0xF0:  // Break code detected
                    if (byte3 == 0x75) return gameControls[10]; // rotate up grenade stop
                    else if (byte3 == 0x72) return gameControls[12]; // rotate down grenade stop
                    break;
            }
        } else if (byte1 == 0x29) {
            switch(byte2){
                case 0x29: return gameControls[13]; // user throwing grenade

                case 0xF0: return gameControls[14]; // user grenade stop
            }

            
        }
    }

    
    return NULL;
}


//goofy ahh function
// void clearPS2Fifo(){

//     printf("START OF CLEAR FIFO FUNCTION BEFORE LOOP\n-----------------\n");

//     while(1){
//         ps2_data = *(ps2_ptr);  // Read data from PS/2 port
//         RVALID = ps2_data & 0x8000;


        
//         if(RVALID){
//             byte1 = byte2;
//             byte2 = byte3;
//             byte3 = ps2_data & 0xFF;

//             printf("Data Just Read in: %d\n", byte3);
//         }
//         else{
//             printf("Exiting loop since RVALID == 0\n");
//             return;
//         }
//     }

// }

