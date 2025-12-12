/*
 * light_display.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Admin
 */

#ifndef INC_LIGHT_DISPLAY_H_
#define INC_LIGHT_DISPLAY_H_

#include "main.h"
#include "global.h"

void RGB_TrafficLight_Init(RGB_TrafficLight_t* RGB_tl, uint16_t LIGHTA_Pin, uint16_t LIGHTB_Pin,
	GPIO_TypeDef * LIGHTA_Port, GPIO_TypeDef * LIGHTB_Port);
void RGB_TrafficLight_TurnOn(RGB_TrafficLight_t RGB_tl, uint8_t State);
void RGB_TrafficLight_Blink(RGB_TrafficLight_t RGB_tl, uint8_t State);
void updateBlink();

#endif /* INC_LIGHT_DISPLAY_H_ */
