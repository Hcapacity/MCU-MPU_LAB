/*
 * button.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Admin
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

#define BUTTON_COUNT 3

#define PRESSED_STATE GPIO_PIN_RESET
#define NOR_STATE GPIO_PIN_SET

// External variables declaration
extern int button_auto_increase[BUTTON_COUNT];

// Function declarations
void getKeyInput(void);
int is_button_pressed(int index);
int is_button_pressed_1s(int index);
int is_button_double_pressed(int index);
int is_button_auto_increase(int index);
int is_button_held(int index);

#endif /* BUTTON_H_ */
