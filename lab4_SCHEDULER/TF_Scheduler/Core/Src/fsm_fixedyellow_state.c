/*
 * fsm_fixedyellow_state.c
 *
 *  Created on: Nov 16, 2025
 *      Author: Admin
 */

#include "fsm_fixedyellow_state.h"

void fsm_processing_yellow_trafficlight(){
	if(system_state == FIX_YELLOW_STATE){
		RGB_TrafficLight_Blink(RGB_tl1, 2);
		RGB_TrafficLight_Blink(RGB_tl2, 2);
	}
}

void fsm_fixedyellow_state(){
			// Blink Yellow Led 2hz
			// Button2 -> increase the time duration value for Yellow LEDs (press -> increase 1, hold press -> increase 1 each second)
			// Note: Range Yellow Counter = 1-99
			// Button3 -> Set value
	if(system_state == FIX_YELLOW_STATE){
		if(is_button_pressed(&btn[0])){
			if(Yellow_Counter != Pre_Yellow_Counter){
				Pre_Yellow_Counter = Yellow_Counter;
			}
			index_led = 0;
			system_state = FIX_GREEN_STATE;
			updateClockBuffer(system_state, Pre_Green_Counter);
		}
		else{
			if(is_button_pressed_1s(&btn[1])){
				Pre_Yellow_Counter++;
				if(Pre_Yellow_Counter >= 100) Pre_Yellow_Counter = 1;
				updateClockBuffer(system_state, Pre_Yellow_Counter);
				index_led = 0;
			}
			else {
				if(is_button_pressed(&btn[1])){
					Pre_Yellow_Counter++;
					if(Pre_Yellow_Counter >= 100) Pre_Yellow_Counter = 1;
					updateClockBuffer(system_state, Pre_Yellow_Counter);
					index_led = 0;
				}
			}

			if(is_button_pressed(&btn[2])){
				Yellow_Counter = Pre_Yellow_Counter;
			}

		}
	}
}
