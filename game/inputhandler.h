#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#define LED_BASE 0xFF200000
#define LEDR_BASE 0xFF200000
#define HEX3_HEX0_BASE 0xFF200020
#define HEX5_HEX4_BASE 0xFF200030
#define SW_BASE 0xFF200040
#define KEY_BASE 0xFF200050
#define JP1_BASE 0xFF200060
#define JP2_BASE 0xFF200070
#define PS2_BASE 0xFF200100
#define PS2_DUAL_BASE 0xFF200108
#define JTAG_UART_BASE 0xFF201000
#define IrDA_BASE 0xFF201020
#define TIMER_BASE 0xFF202000
#define TIMER_2_BASE 0xFF202020
#define AV_CONFIG_BASE 0xFF203000
#define RGB_RESAMPLER_BASE 0xFF203010
#define PIXEL_BUF_CTRL_BASE 0xFF203020
#define CHAR_BUF_CTRL_BASE 0xFF203030
#define AUDIO_BASE 0xFF203040
#define VIDEO_IN_BASE 0xFF203060
#define EDGE_DETECT_CTRL_BASE 0xFF203070
#define ADC_BASE 0xFF204000
#define MTIME_BASE 0xFF202100

#define MAP_BOUNDS 0
#define PIXELS_IN_1_METER 1

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Global pointers

extern const char* gameControls[];
extern volatile int* ps2_ptr;
extern uint8_t byte1, byte2, byte3;
extern int ps2_data, RVALID;

// Polling Functions
void poll_start_input();
bool poll_move_or_stay_input();
bool poll_grenade_or_stay_input(); //same as 1 above just diff debug print statements for now
char* single_poll_input(); // returns key
char* grenade_control_input();
void clearPS2Fifo();


#endif // INPUTHANDLER_H