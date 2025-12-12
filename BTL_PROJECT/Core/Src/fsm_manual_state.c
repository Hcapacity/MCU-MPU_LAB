/*
 * fsm_manual_state.c
 *
 *  Created on: Nov 22, 2025
 *      Author: Windows
 */

#include "fsm_manual_state.h"

void fsm_processing_manual_wait() {
	if (system_state == MANUAL_STATE && manual_state == MANUAL_WAIT_STATE) {
		RGB_TrafficLight_Blink(RGB_tl1, 2);
		RGB_TrafficLight_Blink(RGB_tl2, 2);
	}
}

void fsm_manual_wait_state() {
	if (system_state == MANUAL_STATE && manual_state == MANUAL_WAIT_STATE) {
		if (Manual_Wait_Counter >= 100) {
			Manual_Wait_Counter = 0;
			if (Manual_Wait_Second >= 2) {
				Manual_Wait_Second = 0;
				manual_state = MANUAL_SWITCH_STATE;
				system_state = MANUAL_STATE;
			}
			else ++Manual_Wait_Second;
		}
		else ++Manual_Wait_Counter;

		if (is_button_pressed(0)) {
			system_state = CONFIG_STATE;
			setting_state = CONFIG_RED_STATE;
		}
	}
}

void fsm_processing_manual_switch() {
	if (system_state == MANUAL_STATE && manual_state == MANUAL_SWITCH_STATE) {
		if (is_switch) {
			if (light_state1 == RED_STATE) {
				light_state1 = GREEN_STATE;
				light_state2 = RED_STATE;
			}
			else if (light_state2 == RED_STATE) {
				light_state2 = GREEN_STATE;
				light_state1 = RED_STATE;
			}
			is_switch = 0;
		}
		RGB_TrafficLight_TurnOn(RGB_tl1, light_state1);
		RGB_TrafficLight_TurnOn(RGB_tl2, light_state2);
	}
}

void fsm_manual_switch_state() {
	if (system_state == MANUAL_STATE && manual_state == MANUAL_SWITCH_STATE) {
		if (is_button_pressed(0)) {
			system_state = CONFIG_STATE;
			setting_state = CONFIG_RED_STATE;
		}
		else if (is_button_pressed(1)) {
			is_switch = 1;
			system_state = MANUAL_STATE;
			manual_state = MANUAL_WAIT_STATE;
			Manual_Wait_Second = 0;
			Manual_Wait_Counter = 0;
		}
	}
}
