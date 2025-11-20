/*
 * button.c
 *
 *  Created on: Nov 16, 2025
 *      Author: Admin
 */


#include "button.h"

void Button_Init(btn_typedef* btn, uint16_t btn_Pin, GPIO_TypeDef * btn_Port){
	btn->btn_Pin = btn_Pin;
	btn->btn_Port = btn_Port;

	btn->btn_state = 0;
	btn->counterForButtonPress1s = 0;
	btn->counterForButtonPressDouble = 0;
	btn->firtpressflag = 0;
	btn->flagpress = 0;
	btn->flagForButtonPress1s = 0;
	btn->flagForButtonPressDouble = 0;
}


void button_reading(){
	for(int i = 0; i < N0_OF_BUTTONS; i++){
		btn[i].debounceButton_3 = btn[i].debounceButton_2;
		btn[i].debounceButton_2 = btn[i].debounceButton_1;
		btn[i].debounceButton_1 = HAL_GPIO_ReadPin(btn[i].btn_Port, btn[i].btn_Pin);

		// update state of button
		if( btn[i].debounceButton_3 == btn[i].debounceButton_1){
			if(btn[i].btn_state != btn[i].debounceButton_1){
				if(btn[i].debounceButton_1 == BUTTON_IS_PRESSED){
					btn[i].flagpress = 1;
				}
			btn[i].btn_state = btn[i].debounceButton_1;
			}
		}

		// checking press every 1s
		if(btn[i].btn_state == BUTTON_IS_PRESSED){
			if( btn[i].counterForButtonPress1s < DURATION_FOR_AUTO_INCREASING ){
				++btn[i].counterForButtonPress1s;
			} else {
			btn[i].flagForButtonPress1s = 1;
			btn[i].counterForButtonPress1s = 0;
			}
		} else {
			btn[i].counterForButtonPress1s = 0;
			btn[i].flagForButtonPress1s = 0;
		}
	}
	// checking press double
//	if(btn->btn_state == BUTTON_IS_PRESSED && btn->firtpressflag == 0){
//		btn->firtpressflag = 1;
//		btn->counterForButtonPressDouble = 0;
//	}

//	if(btn->firtpressflag == 1){
//		if(btn->counterForButtonPressDouble >= DOUBLE_PRESS_CHECKIN
//				&& btn->counterForButtonPressDouble < DOUBLE_PRESS_TIMEOUT){
//			if(btn->btn_state == BUTTON_IS_PRESSED){
//				btn->flagForButtonPressDouble = 1;
//				btn->firtpressflag = 0;
//				btn->counterForButtonPressDouble = 0;
//			}
//		}
//
//		if(btn->counterForButtonPressDouble >= DOUBLE_PRESS_TIMEOUT){
//			btn->firtpressflag = 0;
//			btn->counterForButtonPressDouble = 0;
//		}
//		++btn->counterForButtonPressDouble;
//	}

}

unsigned char is_button_pressing (btn_typedef* btn){
	return ( btn->btn_state == BUTTON_IS_PRESSED );
}

unsigned char is_button_pressed (btn_typedef* btn){
	if(btn->flagpress){
		btn->flagpress = 0;
		return 1;
	}
	return 0;
}

unsigned char is_button_pressed_1s (btn_typedef* btn){
	if( btn->flagForButtonPress1s == 1){
		btn->flagForButtonPress1s = 0;
		return 1;
	}
	return 0;
}

unsigned char is_button_double_press (btn_typedef* btn){
	if( btn->flagForButtonPressDouble == 1){
		btn->flagForButtonPressDouble = 0;
		return 1;
	}
	return 0;
}
