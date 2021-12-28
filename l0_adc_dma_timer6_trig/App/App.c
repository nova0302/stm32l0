/*
 * App.c
 *
 *  Created on: Dec 25, 2021
 *      Author: LG
 */

#include <stdio.h>
#include "main.h"
#include "App.h"
#include "lcd_user.h"

extern ADC_HandleTypeDef hadc;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim6;

//https://blog.naver.com/eziya76/221472568302
#include <stdbool.h>

#define NUM_ADC_CHANNEL (3)

static uint32_t adcValues[NUM_ADC_CHANNEL];

volatile bool updateAdcValues = false;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	updateAdcValues = true;
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}

void appSetup() {
	HAL_ADC_Start_DMA(&hadc, adcValues, NUM_ADC_CHANNEL);
	HAL_TIM_Base_Start(&htim6);
	lcd_init(&hi2c1);
}
void appLoop() {

	static uint32_t last;

	uint32_t now = HAL_GetTick();

	if (now - last > 500) {
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		last = now;
	}

	if (updateAdcValues) {
		updateAdcValues = false;
		char str[40] = { 0, };
		OLED_Clear();
		for (int i = 0; i < 3; i++) {
			sprintf(str, "%d: %d", i, (int) adcValues[i]);
			//OLED_ShowString(0, i, str, 1);
			OLED_ShowStringXY(0, i, str, 1);//(0, i, str, 1);
		}
	}

}

