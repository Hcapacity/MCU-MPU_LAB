/*
 * fsm_config_state.h
 *
 *  Created on: Nov 21, 2025
 *      Author: Admin
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
		if(is_button_pressed(&btn[0])){
			if(Red_Counter != Yellow_Counter + Green_Counter){
				error_state = RED_NOT_EQUAL_YELLOW_AND_GREEN;
				system_state = ERROR_STATE;
			}
			else {
				if(Red_Counter != Pre_Red_Counter){
					Pre_Red_Counter = Red_Counter;
				}
				Red_Counter_temp1 = Red_Counter;
				Red_Counter_temp2 = Green_Counter;
				light_state1 = RED_STATE;
				light_state2 = GREEN_STATE;
				// handle buffer in LCD
				updateLCDBuffer(Red_Counter, Green_Counter);
				system_state = NORMAL_STATE;
			}
		}
		else{
			if(is_button_pressed_1s(&btn[1])){
				Pre_Red_Counter++;
				if(Pre_Red_Counter >= 100) Pre_Red_Counter = 1;
				// handle buffer in LCD
				updateLCDBuffer(setting_state, Pre_Red_Counter);
			}
			else{
				if(is_button_double_press(&btn[1])){
					Pre_Red_Counter = 1;
					// handle buffer in LCD
					updateLCDBuffer(setting_state, Pre_Red_Counter);
				}
				else {
					if(is_button_pressed(&btn[1])){
						Pre_Red_Counter++;
						if(Pre_Red_Counter >= 100) Pre_Red_Counter = 1;
						// handle buffer in LCD
						updateLCDBuffer(setting_state, Pre_Red_Counter);
					}
				}
			}

			if(is_button_pressed(&btn[2])){
				Red_Counter = Pre_Red_Counter;
			}

			if(is_button_pressed1s(&btn[2])){
				setting_state = CONFIG_YELLOW_STATE;
				// handle buffer in lCD
				updateLCDBuffer(setting_state, Pre_Yellow_Counter);
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
			// Blink Yellow Led 2hz
			// Button2 -> increase the time duration value for Yellow LEDs (press -> increase 1, hold press -> increase 1 each second)
			// Note: Range Yellow Counter = 1-99
			// Button3 -> Set value
	if(system_state == CONFIG_STATE && setting_state == CONFIG_YELLOW_STATE){
		if(is_button_pressed(&btn[0])){
			if(Yellow_Counter != Pre_Yellow_Counter){
				Pre_Yellow_Counter = Yellow_Counter;
			}
			if(Red_Counter != Blue_Counter + Green_Counter){
				error_state = RED_NOT_EQUAL_YELLOW_GREEN;
				system_state = ERROR_STATE;
			}
			else{
				Red_Counter_temp1 = Red_Counter;
				Yellow_Counter_temp1 = Yellow_Counter;
				Green_Counter_temp1 = Green_Counter;

				Red_Counter_temp2 = Red_Counter;
				Yellow_Counter_temp2 = Yellow_Counter;
				Green_Counter_temp2 = Green_Counter;

				RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
				RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);
				// handle buffer in LCD
				updateLCDBuffer(Red_Counter, Green_Counter);

				light_state1 = RED_STATE;
				light_state2 = GREEN_STATE;
				// handle buffer in LCD
				updateLCDBuffer(Red_Counter, Green_Counter);
				system_state = NORMAL_STATE;
			}
		}
		else{
			if(is_button_pressed_1s(&btn[1])){
				Pre_Yellow_Counter++;
				if(Pre_Yellow_Counter >= 100) Pre_Yellow_Counter = 1;
				// handle buffer in LCD
				updateLCDBuffer(setting_state, Pre_Red_Counter);
			}
			else {
				if(is_button_double_pressed(&btn[1])){
					Pre_Yellow_Counter = 1;
					// handle buffer in LCD
					updateLCDBuffer(setting_state, Pre_Red_Counter);
				}
				else{
					if(is_button_pressed(&btn[1])){
						Pre_Yellow_Counter++;
						if(Pre_Yellow_Counter >= 100) Pre_Yellow_Counter = 1;
						// handle buffer in LCD
						updateLCDBuffer(setting_state, Pre_Red_Counter);
					}
				}
			}

			if(is_button_pressed(&btn[2])){
				Yellow_Counter = Pre_Yellow_Counter;
				if(Red_Counter <= Yellow_Counter){
					error_state = RED_LESS_OR_EQUAL_THAN_YELLOW;
					system_state = ERROR_STATE;
				}
			}

			if(is_button_pressed1s(&btn[2])){
				setting_state = CONFIG_GREEN_STATE;
				// handle buffer in lCD
				updateLCDBuffer(setting_state, Pre_Green_Counter);
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
		if(is_button_pressed(&btn[0])){

			if(Green_Counter != Pre_Green_Counter){
				Pre_Green_Counter = Green_Counter;
			}

			uint8_t Red_Check = Green_Counter + Yellow_Counter;
			if(Red_Counter != Red_Check){
				error_state = RED_NOT_EQUAL_YELLOW_GREEN;
				system_state = ERROR_STATE;
			}
			else{
				Red_Counter_temp1 = Red_Counter;
				Yellow_Counter_temp1 = Yellow_Counter;
				Green_Counter_temp1 = Green_Counter;

				Red_Counter_temp2 = Red_Counter;
				Yellow_Counter_temp2 = Yellow_Counter;
				Green_Counter_temp2 = Green_Counter;

				// handle buffer in lCD
				updateLCDBuffer(setting_state, Pre_Green_Counter);
				RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
				RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);

				light_state1 = RED_STATE;
				light_state2 = GREEN_STATE;
				system_state = NORMAL_STATE;
			}
		}
		else{
			if(is_button_pressed_1s(&btn[1])){
				Pre_Green_Counter++;
				if(Pre_Green_Counter >= 100) Pre_Green_Counter = 1;
				// handle buffer in lCD
				updateLCDBuffer(setting_state, Pre_Green_Counter);
			}
			else {
				if(is_button_double_pressed(&btn[1])){
					Pre_Green_Counter = 1;
					// handle buffer in lCD
					updateLCDBuffer(setting_state, Pre_Green_Counter);
				}
				else{
					if(is_button_pressed(&btn[1])){
						Pre_Green_Counter++;
						if(Pre_Green_Counter >= 100) Pre_Green_Counter = 1;
						// handle buffer in lCD
						updateLCDBuffer(setting_state, Pre_Green_Counter);
					}
				}
			}

			if(is_button_pressed(&btn[2])){
				Green_Counter = Pre_Green_Counter;
				if(Pre_Red_Counter <= Pre_Green_Counter){
					error_state = RED_LESS_OR_EQUAL_THAN_GREEN;
					system_state = ERROR_STATE;
				}
			}

			if(is_button_pressed1s(&btn[2])){
				setting_state = CONFIG_RED_STATE;
				// handle buffer in lCD
				updateLCDBuffer(setting_state, Pre_Red_Counter);
			}
		}
	}
}
