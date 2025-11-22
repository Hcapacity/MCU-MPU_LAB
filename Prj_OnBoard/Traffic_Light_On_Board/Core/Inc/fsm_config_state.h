/*
 * fsm_config_state.h
 *
 *  Created on: Nov 21, 2025
 *      Author: Admin
 */

#ifndef INC_FSM_CONFIG_STATE_H_
#define INC_FSM_CONFIG_STATE_H_

#include "global.h"
#include "lcd_display.h"
#include "light_display.h"
#include "button.h"

void fsm_fixedred_state(void);
void fsm_processing_red_trafficlight(void);

void fsm_fixedyellow_state(void);
void fsm_processing_yellow_trafficlight(void);

void fsm_fixedgreen_state(void);
void fsm_processing_green_trafficlight(void);

#endif /* INC_FSM_CONFIG_STATE_H_ */
