/*
 * lcd_display.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Admin
 */

#ifndef INC_LCD_DISPLAY_H_
#define INC_LCD_DISPLAY_H_

#include "stm32f1xx_hal.h"
#include "global.h"

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD (0x21 << 1) // change this according to ur setup

void lcd_init (void);   // initialize lcd
void lcd_send_cmd (char cmd);  // send command to the lcd
void lcd_send_data (char data);  // send data to the lcd
void lcd_send_string (char *str);  // send string to the lcd
void lcd_clear_display (void);	//clear display lcd
void lcd_goto_XY (int row, int col); //set proper location on screen
void lcd_send_number(uint8_t num);

void updateLCDBuffer_Auto();
void updateLCDBuffer_Manual();
void updateLCDBuffer_Config();
void updateLCDBuffer_Error();
void updateLCDBuffer();

#endif /* INC_LCD_DISPLAY_H_ */
