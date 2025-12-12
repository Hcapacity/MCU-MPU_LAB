/*
 * global.c
 *
 *  Created on: Nov 21, 2025
 *      Author: Admin
 */


#include "global.h"

uint8_t system_state  = NORMAL_STATE;
uint8_t setting_state = CONFIG_RED_STATE;
uint8_t error_state;
uint8_t manual_state = MANUAL_WAIT_STATE;

uint8_t light_state1  = RED_STATE;
uint8_t light_state2  = GREEN_STATE;

uint8_t Pre_Red_Counter    = DURATION_RED;
uint8_t Pre_Yellow_Counter = DURATION_YELLOW;
uint8_t Pre_Green_Counter  = DURATION_GREEN;

uint8_t Red_Counter    = DURATION_RED;
uint8_t Yellow_Counter = DURATION_YELLOW;
uint8_t Green_Counter  = DURATION_GREEN;

uint8_t Red_Counter_temp1    = DURATION_RED;
uint8_t Yellow_Counter_temp1 = DURATION_YELLOW;
uint8_t Green_Counter_temp1  = DURATION_GREEN;

uint8_t Red_Counter_temp2    = DURATION_RED;
uint8_t Yellow_Counter_temp2 = DURATION_YELLOW;
uint8_t Green_Counter_temp2  = DURATION_GREEN;

uint8_t buffer_display[2];

uint16_t Manual_Wait_Counter = 0;
uint8_t Manual_Wait_Second = 0;

uint8_t num1 = 0;
uint8_t num2 = 0;

uint8_t is_switch = 1;

uint8_t blink = 1;

int index_led = 0;

// initialize the below variables in main
btn_typedef       btn[N0_OF_BUTTONS];
RGB_TrafficLight_t RGB_tl1;
RGB_TrafficLight_t RGB_tl2;
