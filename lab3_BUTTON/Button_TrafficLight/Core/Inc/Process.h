/*
 * Process.h
 *
 *  Created on: Nov 2, 2025
 *      Author: Admin
 */

#ifndef INC_PROCESS_H_
#define INC_PROCESS_H_

#include "Button.h"
#include "Led_Display.h"
#include "Light_Display.h"
#include "Software_Timer.h"
#include "main.h"

#define AUTO_STATE 0
#define FIX_RED_STATE 1
#define FIX_YELLOW_STATE 2
#define FIX_GREEN_STATE 3

#define RED_STATE 0
#define GREEN_STATE 1
#define YELLOW_STATE 2

#define DURATION_RED 5
#define DURATION_YELLOW 3
#define DURATION_GREEN 2

// Timer0 -> 1s (Change Value of 7seg, Duration for LEDs)
// Timer1 -> 250ms (Blink LEDs)
// Timer2 -> 50ms (Scan LEDs)
void fsm_processing_trafficlight(RGB_TrafficLight_t* RGB_tl1, RGB_TrafficLight_t* RGB_tl2);

//*************************************//
// RULE: IF AFTER SAVE GREEN STATE, RED_DURATION != YELLOW_DURATION + GREEN_DURATION --> SET THE DEFAULT VALUE FOR THEM! //
void fsm_processing_system(btn_typedef* btn, RGB_TrafficLight_t* RGB_tl1, RGB_TrafficLight_t* RGB_tl2);


#endif /* INC_PROCESS_H_ */
