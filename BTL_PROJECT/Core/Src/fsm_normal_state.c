/*
 * fsm_normal_state.c
 *
 *  Created on: Nov 21, 2025
 *      Author: Admin
 */


#include "fsm_normal_state.h"

/* Task này chạy mỗi 1s (do scheduler gọi), chỉ xử lý AUTO_STATE */
void fsm_processing_trafficlight(void) {
    if (system_state == NORMAL_STATE) {
		// TL1
		switch (light_state1) {
		case RED_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);

			if (Red_Counter_temp1 == 0) {
				Red_Counter_temp1 = Red_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, GREEN_STATE);
				buffer_display[0] = Green_Counter_temp1--;
				light_state1 = GREEN_STATE;
				break;
			}
			buffer_display[0] = Red_Counter_temp1--;
			break;

		case GREEN_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl1, GREEN_STATE);
			if (Green_Counter_temp1 == 0) {
				Green_Counter_temp1 = Green_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, YELLOW_STATE);
				buffer_display[0] = Yellow_Counter_temp1--;
				light_state1 = YELLOW_STATE;
				break;
			}
			buffer_display[0] = Green_Counter_temp1--;
			break;

		case YELLOW_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl1, YELLOW_STATE);
			if (Yellow_Counter_temp1 == 0) {
				Yellow_Counter_temp1 = Yellow_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
				buffer_display[0] = Red_Counter_temp1--;
				light_state1 = RED_STATE;
				break;
			}
			buffer_display[0] = Yellow_Counter_temp1--;
			break;
		}

		// TL2
		switch (light_state2) {
		case RED_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl2, RED_STATE);
			if (Red_Counter_temp2 == 0) {
				Red_Counter_temp2 = Red_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);
				buffer_display[1] = Green_Counter_temp2--;
				light_state2 = GREEN_STATE;
				break;
			}
			buffer_display[1] = Red_Counter_temp2--;
			break;

		case GREEN_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);
			if (Green_Counter_temp2 == 0) {
				Green_Counter_temp2 = Green_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl2, YELLOW_STATE);
				buffer_display[1] = Yellow_Counter_temp2--;
				light_state2 = YELLOW_STATE;
				break;
			}
			buffer_display[1] = Green_Counter_temp2--;
			break;

		case YELLOW_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl2, YELLOW_STATE);
			if (Yellow_Counter_temp2 == 0) {
				Yellow_Counter_temp2 = Yellow_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl2, RED_STATE);
				buffer_display[1] = Red_Counter_temp2--;
				light_state2 = RED_STATE;
				break;
			}
			buffer_display[1] = Yellow_Counter_temp2--;
			break;
		}
    }
}

void fsm_normal_state(void) {
    if (system_state == NORMAL_STATE) {
		if (is_button_pressed(0)) {
			system_state = MANUAL_STATE;
			manual_state = MANUAL_WAIT_STATE;
			Manual_Wait_Second = 0;
			Manual_Wait_Counter = 0;
		}
    }
}
