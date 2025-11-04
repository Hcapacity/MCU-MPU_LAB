/*
 * Light_Display.c
 *
 *  Created on: Nov 2, 2025
 *      Author: Admin
 */

#include "Light_Display.h"

void RGB_TrafficLight_Init(RGB_TrafficLight_t* RGB_tl, uint16_t RED_Pin, uint16_t YELLOW_Pin, uint16_t GREEN_Pin,
	GPIO_TypeDef * RED_Port, GPIO_TypeDef * YELLOW_Port, GPIO_TypeDef * GREEN_Port){
	RGB_tl->RED_Pin = RED_Pin;
	RGB_tl->YELLOW_Pin = YELLOW_Pin;
	RGB_tl->GREEN_Pin = GREEN_Pin;

	RGB_tl->RED_Port = RED_Port;
	RGB_tl->YELLOW_Port = YELLOW_Port;
	RGB_tl->GREEN_Port = GREEN_Port;
}

void RGB_TrafficLight_TurnOn(RGB_TrafficLight_t* RGB_tl, uint8_t State){
	if(State == RED_STATE){
		HAL_GPIO_WritePin(RGB_tl->RED_Port, RGB_tl->RED_Pin, 0);
		HAL_GPIO_WritePin(RGB_tl->YELLOW_Port, RGB_tl->YELLOW_Pin, 1);
		HAL_GPIO_WritePin(RGB_tl->GREEN_Port, RGB_tl->GREEN_Pin, 1);
	}
	else if(State == YELLOW_STATE){
		HAL_GPIO_WritePin(RGB_tl->RED_Port, RGB_tl->RED_Pin, 1);
		HAL_GPIO_WritePin(RGB_tl->YELLOW_Port, RGB_tl->YELLOW_Pin, 0);
		HAL_GPIO_WritePin(RGB_tl->GREEN_Port, RGB_tl->GREEN_Pin, 1);
	}
	else {
		HAL_GPIO_WritePin(RGB_tl->RED_Port, RGB_tl->RED_Pin, 1);
		HAL_GPIO_WritePin(RGB_tl->YELLOW_Port, RGB_tl->YELLOW_Pin, 1);
		HAL_GPIO_WritePin(RGB_tl->GREEN_Port, RGB_tl->GREEN_Pin, 0);
	}
}

void RGB_TrafficLight_Blink(RGB_TrafficLight_t* RGB_tl, uint8_t State){
	if(State == RED_STATE){
		HAL_GPIO_TogglePin(RGB_tl->RED_Port, RGB_tl->RED_Pin);
		HAL_GPIO_WritePin(RGB_tl->YELLOW_Port, RGB_tl->YELLOW_Pin, 1);
		HAL_GPIO_WritePin(RGB_tl->GREEN_Port, RGB_tl->GREEN_Pin, 1);
	}
	else if(State == YELLOW_STATE){
		HAL_GPIO_WritePin(RGB_tl->RED_Port, RGB_tl->RED_Pin, 1);
		HAL_GPIO_TogglePin(RGB_tl->YELLOW_Port, RGB_tl->YELLOW_Pin);
		HAL_GPIO_WritePin(RGB_tl->GREEN_Port, RGB_tl->GREEN_Pin, 1);
	}
	else {
		HAL_GPIO_WritePin(RGB_tl->RED_Port, RGB_tl->RED_Pin, 1);
		HAL_GPIO_WritePin(RGB_tl->YELLOW_Port, RGB_tl->YELLOW_Pin, 1);
		HAL_GPIO_TogglePin(RGB_tl->GREEN_Port, RGB_tl->GREEN_Pin);
	}
}
