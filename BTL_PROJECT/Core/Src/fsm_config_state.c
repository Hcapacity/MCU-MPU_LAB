/*
 * fsm_config_state.c
 *
 *  Created on: Nov 21, 2025
 *  Author: Admin
 */

#include "fsm_config_state.h"

/*********************** RULE OPERATIO ************************/
// button 1 -> change the system state
// button 2 -> change the value
// button 3 -> save and change config state (press to save the value and holded press to change config state)
/**************************************************************/

void blink_red_trafficlight(){
	if(system_state == CONFIG_STATE && setting_state == CONFIG_RED_STATE){
		RGB_TrafficLight_Blink(RGB_tl1, 0);
		RGB_TrafficLight_Blink(RGB_tl2, 0);
	}
}


void fsm_fixedred_state(){
	if(system_state == CONFIG_STATE && setting_state == CONFIG_RED_STATE){
		if(is_button_pressed(0)){
			if(Red_Counter != Green_Counter + Yellow_Counter){
				error_state = RED_NOT_EQUAL_YELLOW_AND_GREEN;
				system_state = ERROR_STATE;
			}
			else{
				Pre_Red_Counter = Red_Counter;

				Red_Counter_temp1 = Red_Counter;
				Yellow_Counter_temp1 = Yellow_Counter;
				Green_Counter_temp1 = Green_Counter;

				Red_Counter_temp2 = Red_Counter;
				Yellow_Counter_temp2 = Yellow_Counter;
				Green_Counter_temp2 = Green_Counter;

				buffer_display[0] = Red_Counter;
				buffer_display[1] = Green_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
				RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);

				light_state1 = RED_STATE;
				light_state2 = GREEN_STATE;
				system_state = NORMAL_STATE;
			}
		}
		else{
			// Handle auto-increase after 1s long press
			if(is_button_auto_increase(1)){
				Pre_Red_Counter++;
				if(Pre_Red_Counter >= 100) Pre_Red_Counter = 1;
			}

			// Handle double press
			else if(is_button_double_pressed(1)){
				Pre_Red_Counter = 1;
			}
			// Handle single press
			else if(is_button_pressed(1)){
				Pre_Red_Counter++;
				if(Pre_Red_Counter >= 100) Pre_Red_Counter = 1;
			}

			if(is_button_pressed(2)){
				Red_Counter = Pre_Red_Counter;
				setting_state = CONFIG_YELLOW_STATE;
				system_state = CONFIG_STATE;
			}
		}
	}
}


void blink_yellow_trafficlight(){
	if(system_state == CONFIG_STATE && setting_state == CONFIG_YELLOW_STATE){
		RGB_TrafficLight_Blink(RGB_tl1, 2);
		RGB_TrafficLight_Blink(RGB_tl2, 2);
	}
}

void fsm_fixedyellow_state(){
	if(system_state == CONFIG_STATE && setting_state == CONFIG_YELLOW_STATE){
		if(is_button_pressed(0)){
			if(Red_Counter != Green_Counter + Yellow_Counter){
				error_state = RED_NOT_EQUAL_YELLOW_AND_GREEN;
				system_state = ERROR_STATE;
			}
			else{
				Pre_Yellow_Counter = Yellow_Counter;

				Red_Counter_temp1 = Red_Counter;
				Yellow_Counter_temp1 = Yellow_Counter;
				Green_Counter_temp1 = Green_Counter;

				Red_Counter_temp2 = Red_Counter;
				Yellow_Counter_temp2 = Yellow_Counter;
				Green_Counter_temp2 = Green_Counter;

				buffer_display[0] = Red_Counter;
				buffer_display[1] = Green_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
				RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);

				light_state1 = RED_STATE;
				light_state2 = GREEN_STATE;
				system_state = NORMAL_STATE;
			}
		}
		else {
			// Handle auto-increase after 1s long press
			if(is_button_auto_increase(1)){
				Pre_Yellow_Counter++;
				if(Pre_Yellow_Counter >= 100) Pre_Yellow_Counter = 1;
			}
			// Handle initial 1s press
//			else if(is_button_pressed_1s(1)){
//				Pre_Yellow_Counter++;
//				if(Pre_Yellow_Counter >= 100) Pre_Yellow_Counter = 1;
//			}
			// Handle double press
			else if(is_button_double_pressed(1)){
				Pre_Yellow_Counter = 1;
			}
			// Handle single press
			else if(is_button_pressed(1)){
				Pre_Yellow_Counter++;
				if(Pre_Yellow_Counter >= 100) Pre_Yellow_Counter = 1;
			}

			if(is_button_pressed(2)){
				Yellow_Counter = Pre_Yellow_Counter;
				if(Red_Counter <= Pre_Yellow_Counter){
					error_state = RED_LESS_OR_EQUAL_THAN_YELLOW;
					system_state = ERROR_STATE;
				}
				else {
					setting_state = CONFIG_GREEN_STATE;
					system_state = CONFIG_STATE;
				}
			}
		}
	}
}


void blink_green_trafficlight(){
	if(system_state == CONFIG_STATE && setting_state == CONFIG_GREEN_STATE){
		RGB_TrafficLight_Blink(RGB_tl1, 1);
		RGB_TrafficLight_Blink(RGB_tl2, 1);
	}
}

void fsm_fixedgreen_state(){
	if(system_state == CONFIG_STATE && setting_state == CONFIG_GREEN_STATE){
		if(is_button_pressed(0)){
			if(Red_Counter != Green_Counter + Yellow_Counter){
				error_state = RED_NOT_EQUAL_YELLOW_AND_GREEN;
				system_state = ERROR_STATE;
			}
			else{
				Pre_Green_Counter = Green_Counter;

				Red_Counter_temp1 = Red_Counter;
				Yellow_Counter_temp1 = Yellow_Counter;
				Green_Counter_temp1 = Green_Counter;

				Red_Counter_temp2 = Red_Counter;
				Yellow_Counter_temp2 = Yellow_Counter;
				Green_Counter_temp2 = Green_Counter;

				buffer_display[0] = Red_Counter;
				buffer_display[1] = Green_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
				RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);

				light_state1 = RED_STATE;
				light_state2 = GREEN_STATE;
				system_state = NORMAL_STATE;
			}
		}
		else {
			// Handle auto-increase after 1s long press
			if(is_button_auto_increase(1)){
				Pre_Green_Counter++;
				if(Pre_Green_Counter >= 100) Pre_Green_Counter = 1;
			}
			// Handle initial 1s press
//			else if(is_button_pressed_1s(1)){
//				Pre_Green_Counter++;
//				if(Pre_Green_Counter >= 100) Pre_Green_Counter = 1;
//			}
			// Handle double press
			else if(is_button_double_pressed(1)){
				Pre_Green_Counter = 1;
			}
			// Handle single press
			else if(is_button_pressed(1)){
				Pre_Green_Counter++;
				if(Pre_Green_Counter >= 100) Pre_Green_Counter = 1;
			}

			if(is_button_pressed(2)){
				Green_Counter = Pre_Green_Counter;
				if(Red_Counter <= Green_Counter) {
					error_state = RED_LESS_OR_EQUAL_THAN_GREEN;
					system_state = ERROR_STATE;
				}
				else {
					setting_state = CONFIG_RED_STATE;
					system_state = CONFIG_STATE;
				}
			}
		}
	}
}
