/*
 * button.h
 *
 *  Created on: Nov 21, 2025
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

void Button_Init(btn_typedef* btn, uint16_t btn_Pin, GPIO_TypeDef * btn_Port);
void button_reading();
unsigned char is_button_pressed(btn_typedef* btn);
unsigned char is_button_pressed_1s(btn_typedef* btn);
unsigned char is_button_double_pressed(btn_typedef* btn);

#endif /* INC_BUTTON_H_ */
