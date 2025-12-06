/*
 * software_timer.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

void setTimer(uint32_t index, uint32_t counter);
void timeRun(void);
uint8_t getTimerFlag(uint32_t index);
void setTimerFlag(uint32_t index, uint8_t value);

#endif /* INC_SOFTWARE_TIMER_H_ */
