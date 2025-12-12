/*
 * lcd_display.c
 *
 *  Created on: Nov 22, 2025
 *      Author: Windows
 */

#include "lcd_display.h"

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void) {
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	HAL_Delay(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	HAL_Delay(50);
	lcd_send_cmd (0x01); /* clear display */
	HAL_Delay(50);
	lcd_send_cmd (0x06); /* set entry mode */
	HAL_Delay(50);
	lcd_send_cmd (0x0c); /* set display to on */
	HAL_Delay(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 0)  // Sửa thành row 0 (thay vì 1)
	{
		pos_Addr = 0x80 + col;  // Dòng 1: 0x80 + vị trí
	}
	else if(row == 1)  // Thêm điều kiện cho dòng 2
	{
		pos_Addr = 0xC0 + col;  // Dòng 2: 0xC0 + vị trí
	}
	else
	{
		pos_Addr = 0x80 + col;  // Mặc định dòng 1
	}
	lcd_send_cmd(pos_Addr);
}

void lcd_send_number(uint8_t num) {
    if (num < 10) {
        lcd_send_data(num + '0');
    } else {
        lcd_send_data((num / 10) + '0');
        lcd_send_data((num % 10) + '0');
    }
}

void updateLCDBuffer_Auto() {
	if (system_state != NORMAL_STATE) return;
	lcd_goto_XY(0,0);
	lcd_send_string("AUTO MODE");
	lcd_goto_XY(1,0);
	switch (light_state1) {
		case (RED_STATE): {
			lcd_send_string("R: ");
			lcd_goto_XY(1,3);
			lcd_send_number(buffer_display[0]);
		} break;

		case (YELLOW_STATE): {
			lcd_send_string("Y: ");
			lcd_goto_XY(1,3);
			lcd_send_number(buffer_display[0]);
		} break;

		case (GREEN_STATE): {
			lcd_send_string("G: ");
			lcd_goto_XY(1,3);
			lcd_send_number(buffer_display[0]);
		} break;
	}

	lcd_goto_XY(1,8);
	switch (light_state2) {
		case (RED_STATE): {
			lcd_send_string("R: ");
			lcd_goto_XY(1,11);
			lcd_send_number(buffer_display[1]);
		} break;

		case (YELLOW_STATE): {
			lcd_send_string("Y: ");
			lcd_goto_XY(1,11);
			lcd_send_number(buffer_display[1]);
		} break;

		case (GREEN_STATE): {
			lcd_send_string("G: ");
			lcd_goto_XY(1,11);
			lcd_send_number(buffer_display[1]);
		} break;
	}
}

void updateLCDBuffer_Manual() {
	if (system_state != MANUAL_STATE) return;
	lcd_goto_XY(0,0);
	lcd_send_string("MANUAL MODE");
	switch (manual_state) {
		case MANUAL_WAIT_STATE: {
			lcd_goto_XY(1,0);
			lcd_send_string("Y: ");
			lcd_goto_XY(1,3);
			lcd_send_number(3 - Manual_Wait_Second);
		} break;

		case MANUAL_SWITCH_STATE: {
			lcd_goto_XY(1,0);
			switch (light_state1) {
				case RED_STATE: {
					lcd_send_string("R:");
					lcd_goto_XY(1,8);
					lcd_send_string("G:");
				} break;

				case GREEN_STATE: {
					lcd_send_string("G:");
					lcd_goto_XY(1,8);
					lcd_send_string("R:");
				} break;
			}
		} break;
	}
}

void updateLCDBuffer_Config() {
	if (system_state != CONFIG_STATE) return;
	lcd_goto_XY(0,0);
	lcd_send_string("CONFIG MODE");
	lcd_goto_XY(1,0);
	lcd_send_string("M: ");
	lcd_goto_XY(1,3);
	switch (setting_state) {
		case CONFIG_RED_STATE: {
			lcd_send_string("R");
		} break;

		case CONFIG_YELLOW_STATE: {
			lcd_send_string("Y");
		} break;

		case CONFIG_GREEN_STATE: {
			lcd_send_string("G");
		} break;
	}
	lcd_goto_XY(1,8);
	lcd_send_string("N: ");
	lcd_goto_XY(1,11);
	switch (setting_state) {
		case CONFIG_RED_STATE: {
			lcd_send_number(Pre_Red_Counter);
		} break;

		case CONFIG_YELLOW_STATE: {
			lcd_send_number(Pre_Yellow_Counter);
		} break;

		case CONFIG_GREEN_STATE: {
			lcd_send_number(Pre_Green_Counter);
		} break;
	}
}

void updateLCDBuffer_Error() {
	if (system_state != ERROR_STATE) return;
	lcd_goto_XY(0,0);
	lcd_send_string("ERROR MODE");
	lcd_goto_XY(1,0);
	switch (error_state) {
		case RED_NOT_EQUAL_YELLOW_AND_GREEN: {
			lcd_send_string("R != Y + G");
		} break;

		case RED_LESS_OR_EQUAL_THAN_YELLOW: {
			lcd_send_string("R <= Y");
		} break;

		case RED_LESS_OR_EQUAL_THAN_GREEN: {
			lcd_send_string("R <= G");
		} break;
	}
}

void updateLCDBuffer() {
	lcd_goto_XY(0,0);
	lcd_send_string("                ");
	lcd_goto_XY(1,0);
	lcd_send_string("                ");
	updateLCDBuffer_Auto();
	updateLCDBuffer_Manual();
	updateLCDBuffer_Config();
	updateLCDBuffer_Error();
}
