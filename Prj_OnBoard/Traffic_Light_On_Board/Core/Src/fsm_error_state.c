/*
 * fsm_error_state.h
 *
 *  Created on: Nov 21, 2025
 *      Author: Admin
 */

#include "fsm_error_state.h"

void blink_led_error_state(){
	if(system_state == ERROR_STATE){
		RGB_TrafficLight_Blink(RGB_tl1, 1);
		RGB_TrafficLight_Blink(RGB_tl2, 1);
	}
}

void blink_led_error_state(){
	if(system_state == ERROR_STATE && error_state == RED_NOT_EQUAL_YELLOW_AND_GREEN){
		// display error in LCD RED_NOT_EQUAL_YELLOW_AND_GREEN
		updateLCDBuffer();

		if(is_button_pressed(&btn[0])){
			Pre_Red_Counter = Pre_Green_Counter + Pre_Yellow_Counter;
			system_state = CONFIG_STATE;
			setting_state = CONFIG_RED_STATE;
		}
	}
	if(system_state == ERROR_STATE && error_state == RED_LESS_OR_EQUAL_THAN_YELLOW){
		// display error in LCD RED_LESS_OR_EQUAL_THAN_YELLOW
		updateLCDBuffer();

		if(is_button_pressed(&btn[0])){
			system_state = CONFIG_STATE;
			setting_state = CONFIG_RED_STATE;
		}
	}
	if(system_state == ERROR_STATE && error_state == RED_LESS_OR_EQUAL_THAN_GREEN){
		// display error in LCD RED_LESS_OR_EQUAL_THAN_GREEN
		updateLCDBuffer();

		if(is_button_pressed(&btn[0])){
			system_state = CONFIG_STATE;
			setting_state = CONFIG_RED_STATE;
		}
	}

}
