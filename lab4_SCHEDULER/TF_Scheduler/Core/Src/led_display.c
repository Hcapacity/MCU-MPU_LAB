/*
 * led_display.c
 *
 *  Created on: Nov 16, 2025
 *      Author: Admin
 */


#include "led_display.h"

int counter = 0;
int led_buffer[MAXLED];

void updateClockBuffer(uint8_t left, uint8_t right) {
    led_buffer[0] = left / 10;
    led_buffer[1] = left % 10;
    led_buffer[2] = right / 10;
    led_buffer[3] = right % 10;
}

void display7SEG(uint8_t counter) {
    if (counter != 1 && counter != 4) {
        HAL_GPIO_WritePin(LEDPORT, SEG0_PIN, GPIO_PIN_RESET);
    } else HAL_GPIO_WritePin(LEDPORT, SEG0_PIN, GPIO_PIN_SET);

    if (counter != 5 && counter != 6) {
        HAL_GPIO_WritePin(LEDPORT, SEG1_PIN, GPIO_PIN_RESET);
    } else HAL_GPIO_WritePin(LEDPORT, SEG1_PIN, GPIO_PIN_SET);

    if (counter != 2) {
        HAL_GPIO_WritePin(LEDPORT, SEG2_PIN, GPIO_PIN_RESET);
    } else HAL_GPIO_WritePin(LEDPORT, SEG2_PIN, GPIO_PIN_SET);

    if (counter != 1 && counter != 4 && counter != 7) {
        HAL_GPIO_WritePin(LEDPORT, SEG3_PIN, GPIO_PIN_RESET);
    } else HAL_GPIO_WritePin(LEDPORT, SEG3_PIN, GPIO_PIN_SET);

    if (counter == 0 || counter == 2 || counter == 6 || counter == 8) {
        HAL_GPIO_WritePin(LEDPORT, SEG4_PIN, GPIO_PIN_RESET);
    } else HAL_GPIO_WritePin(LEDPORT, SEG4_PIN, GPIO_PIN_SET);

    if (counter != 1 && counter != 2 && counter != 3 && counter != 7) {
        HAL_GPIO_WritePin(LEDPORT, SEG5_PIN, GPIO_PIN_RESET);
    } else HAL_GPIO_WritePin(LEDPORT, SEG5_PIN, GPIO_PIN_SET);

    if (counter != 0 && counter != 1 && counter != 7) {
        HAL_GPIO_WritePin(LEDPORT, SEG6_PIN, GPIO_PIN_RESET);
    } else HAL_GPIO_WritePin(LEDPORT, SEG6_PIN, GPIO_PIN_SET);
}

void update7SEG(int index) {
    switch (index) {
    case 0:
        display7SEG(led_buffer[0]);
        HAL_GPIO_WritePin(ENALEDPORT, EN0_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ENALEDPORT, EN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN2_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN3_PIN, GPIO_PIN_SET);
        break;
    case 1:
        display7SEG(led_buffer[1]);
        HAL_GPIO_WritePin(ENALEDPORT, EN0_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ENALEDPORT, EN2_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN3_PIN, GPIO_PIN_SET);
        break;
    case 2:
        display7SEG(led_buffer[2]);
        HAL_GPIO_WritePin(ENALEDPORT, EN0_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN2_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ENALEDPORT, EN3_PIN, GPIO_PIN_SET);
        break;
    case 3:
        display7SEG(led_buffer[3]);
        HAL_GPIO_WritePin(ENALEDPORT, EN0_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN2_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(ENALEDPORT, EN3_PIN, GPIO_PIN_RESET);
        break;
    default:
        break;
    }
}

void Scan_Led(void) {
    if (index_led >= 4) index_led = 0;
    update7SEG(index_led++);
}
