   /*
 * fsm_fixedblue_state.c
 *
 *  Created on: Nov 16, 2025
 *      Author: Admin
 */

#include "fsm_fixedgreen_state.h"

void fsm_processing_green_trafficlight(){
	if(system_state == FIX_GREEN_STATE){
		RGB_TrafficLight_Blink(RGB_tl1, 1);
		RGB_TrafficLight_Blink(RGB_tl2, 1);
	}
}

void fsm_fixedgreen_state(){
	if(system_state == FIX_GREEN_STATE){
		if(is_button_pressed(&btn[0])){
			index_led = 0;

			if(Green_Counter != Pre_Green_Counter){
				Pre_Green_Counter = Green_Counter;
			}

			uint8_t Red_Check = Green_Counter + Yellow_Counter;
			if(Red_Counter != Red_Check){
				Pre_Red_Counter = DURATION_RED;
				Pre_Yellow_Counter = DURATION_YELLOW;
				Pre_Green_Counter = DURATION_GREEN;

				Red_Counter = DURATION_RED;
				Yellow_Counter = DURATION_YELLOW;
				Green_Counter = DURATION_GREEN;
			}

			Red_Counter_temp1 = Red_Counter;
			Yellow_Counter_temp1 = Yellow_Counter;
			Green_Counter_temp1 = Green_Counter;

			Red_Counter_temp2 = Red_Counter;
			Yellow_Counter_temp2 = Yellow_Counter;
			Green_Counter_temp2 = Green_Counter;

			updateClockBuffer(Red_Counter_temp1, Green_Counter_temp2);
			RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
			RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);
			light_state1 = RED_STATE;
			light_state2 = GREEN_STATE;
			system_state = AUTO_STATE;
		}
		else{
			if(is_button_pressed_1s(&btn[1])){
				Pre_Green_Counter++;
				if(Pre_Green_Counter >= 100) Pre_Green_Counter = 1;
				updateClockBuffer(system_state, Pre_Green_Counter);
				index_led = 0;
			}
			else {
				if(is_button_pressed(&btn[1])){
					Pre_Green_Counter++;
					if(Pre_Green_Counter >= 100) Pre_Green_Counter = 1;
					updateClockBuffer(system_state, Pre_Green_Counter);
					index_led = 0;
				}
			}

			if(is_button_pressed(&btn[2])){
				Green_Counter = Pre_Green_Counter;
			}
		}
	}
}
