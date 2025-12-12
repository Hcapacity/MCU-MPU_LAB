/*
 * fsm_manual_state.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Admin
 */

#ifndef INC_FSM_MANUAL_STATE_H_
#define INC_FSM_MANUAL_STATE_H_

#include "global.h"
#include "lcd_display.h"
#include "light_display.h"
#include "button.h"

void fsm_manual_wait_state(void);
void fsm_processing_manual_wait(void);

void fsm_manual_switch_state(void);
void fsm_processing_manual_switch(void);

#endif /* INC_FSM_MANUAL_STATE_H_ */
