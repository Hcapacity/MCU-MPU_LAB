/*
 * fsm_error_state.c
 *
 *  Created on: Nov 21, 2025
 *      Author: Admin
 */

#include "fsm_error_state.h"

void blink_led_error_state(){
	if(system_state == ERROR_STATE){
		RGB_TrafficLight_Blink(RGB_tl1, 0);
		RGB_TrafficLight_Blink(RGB_tl2, 0);
	}
}

void fsm_error_state(){
	if(system_state == ERROR_STATE && error_state == RED_NOT_EQUAL_YELLOW_AND_GREEN){
		if(is_button_pressed(0)){
			system_state = CONFIG_STATE;
			setting_state = CONFIG_RED_STATE;
			Pre_Red_Counter = Green_Counter + Yellow_Counter;
			Red_Counter = Green_Counter + Yellow_Counter;
		}
	}
	if(system_state == ERROR_STATE && error_state == RED_LESS_OR_EQUAL_THAN_YELLOW){
		if(is_button_pressed(0)){
			system_state = CONFIG_STATE;
			setting_state = CONFIG_RED_STATE;
			Pre_Red_Counter = Yellow_Counter + 1;
		}
	}
	if(system_state == ERROR_STATE && error_state == RED_LESS_OR_EQUAL_THAN_GREEN){
		if(is_button_pressed(0)){
			system_state = CONFIG_STATE;
			setting_state = CONFIG_RED_STATE;
			Pre_Red_Counter = Green_Counter + 1;
		}
	}

}
