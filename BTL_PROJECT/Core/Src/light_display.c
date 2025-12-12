/*
 * light_display.c
 *
 *  Created on: Nov 22, 2025
 *      Author: Windows
 */

#include "light_display.h"

void RGB_TrafficLight_Init(RGB_TrafficLight_t* RGB_tl, uint16_t LIGHTA_Pin, uint16_t LIGHTB_Pin,
	GPIO_TypeDef * LIGHTA_Port, GPIO_TypeDef * LIGHTB_Port){
	RGB_tl->LIGHTA_Pin = LIGHTA_Pin;
	RGB_tl->LIGHTB_Pin = LIGHTB_Pin;

	RGB_tl->LIGHTA_Port = LIGHTA_Port;
	RGB_tl->LIGHTB_Port = LIGHTB_Port;
}

void RGB_TrafficLight_TurnOn(RGB_TrafficLight_t RGB_tl, uint8_t State){
	HAL_GPIO_WritePin(RGB_tl.LIGHTA_Port, RGB_tl.LIGHTA_Pin, 0);
	HAL_GPIO_WritePin(RGB_tl.LIGHTB_Port, RGB_tl.LIGHTB_Pin, 0);
	if(State == RED_STATE){
		HAL_GPIO_WritePin(RGB_tl.LIGHTA_Port, RGB_tl.LIGHTA_Pin, 1);
		HAL_GPIO_WritePin(RGB_tl.LIGHTB_Port, RGB_tl.LIGHTB_Pin, 1);
	}
	else if(State == YELLOW_STATE){
		HAL_GPIO_WritePin(RGB_tl.LIGHTA_Port, RGB_tl.LIGHTA_Pin, 1);
		HAL_GPIO_WritePin(RGB_tl.LIGHTB_Port, RGB_tl.LIGHTB_Pin, 0);
	}
	else {
		HAL_GPIO_WritePin(RGB_tl.LIGHTA_Port, RGB_tl.LIGHTA_Pin, 0);
		HAL_GPIO_WritePin(RGB_tl.LIGHTB_Port, RGB_tl.LIGHTB_Pin, 1);
	}
}

void RGB_TrafficLight_Blink(RGB_TrafficLight_t RGB_tl, uint8_t State){
	if (blink) {
		HAL_GPIO_WritePin(RGB_tl.LIGHTA_Port, RGB_tl.LIGHTA_Pin, 0);
		HAL_GPIO_WritePin(RGB_tl.LIGHTB_Port, RGB_tl.LIGHTB_Pin, 0);
	}
	else {
		RGB_TrafficLight_TurnOn(RGB_tl, State);
	}
}

void updateBlink() {
	blink = 1 - blink;
}
