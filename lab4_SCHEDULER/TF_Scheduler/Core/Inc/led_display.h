/*
 * led_display.h
 *
 *  Created on: Nov 16, 2025
 *      Author: Admin
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "global.h"

void updateClockBuffer(uint8_t left, uint8_t right);
void display7SEG(uint8_t counter);
void update7SEG(int index);
void Scan_Led(void);

#endif /* INC_LED_DISPLAY_H_ */
