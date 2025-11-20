/*
 * fsm_normal_state.c
 *
 *  Created on: Nov 16, 2025
 *      Author: Admin
 */

/* fsm_normal_state.c */

#include "fsm_normal_state.h"

/* Task này chạy mỗi 1s (do scheduler gọi), chỉ xử lý AUTO_STATE */
void fsm_processing_trafficlight(void) {
    if (system_state == AUTO_STATE) {
		// TL1
		switch (light_state1) {
		case RED_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);

			if (Red_Counter_temp1 == 0) {
				Red_Counter_temp1 = Red_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, GREEN_STATE);
				num1        = Green_Counter_temp1--;
				light_state1 = GREEN_STATE;
				break;
			}
			num1 = Red_Counter_temp1--;
			break;

		case GREEN_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl1, GREEN_STATE);
			if (Green_Counter_temp1 == 0) {
				Green_Counter_temp1 = Green_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, YELLOW_STATE);
				num1        = Yellow_Counter_temp1--;
				light_state1 = YELLOW_STATE;
				break;
			}
			num1 = Green_Counter_temp1--;
			break;

		case YELLOW_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl1, YELLOW_STATE);
			if (Yellow_Counter_temp1 == 0) {
				Yellow_Counter_temp1 = Yellow_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
				num1        = Red_Counter_temp1--;
				light_state1 = RED_STATE;
				break;
			}
			num1 = Yellow_Counter_temp1--;
			break;
		}

		// TL2
		switch (light_state2) {
		case RED_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl2, RED_STATE);
			if (Red_Counter_temp2 == 0) {
				Red_Counter_temp2 = Red_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);
				num2        = Green_Counter_temp2--;
				light_state2 = GREEN_STATE;
				break;
			}
			num2 = Red_Counter_temp2--;
			break;

		case GREEN_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);
			if (Green_Counter_temp2 == 0) {
				Green_Counter_temp2 = Green_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl2, YELLOW_STATE);
				num2        = Yellow_Counter_temp2--;
				light_state2 = YELLOW_STATE;
				break;
			}
			num2 = Green_Counter_temp2--;
			break;

		case YELLOW_STATE:
			RGB_TrafficLight_TurnOn(RGB_tl2, YELLOW_STATE);
			if (Yellow_Counter_temp2 == 0) {
				Yellow_Counter_temp2 = Yellow_Counter;
				RGB_TrafficLight_TurnOn(RGB_tl2, RED_STATE);
				num2        = Red_Counter_temp2--;
				light_state2 = RED_STATE;
				break;
			}
			num2 = Yellow_Counter_temp2--;
			break;
		}

		updateClockBuffer(num1, num2);
    }
}

void fsm_normal_state(void) {
    if (system_state == AUTO_STATE) {
		if (is_button_pressed(&btn[0])) {
			system_state = FIX_RED_STATE;
			index_led    = 0;
			updateClockBuffer(system_state, Pre_Red_Counter);
		}
    }
}

