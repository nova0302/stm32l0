/*
 * App.c
 *
 *  Created on: Dec 25, 2021
 *      Author: LG
 */

#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "App.h"
#include "lcd_user.h"

int32_t computeTemperature(uint32_t m);

extern ADC_HandleTypeDef hadc;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim22;

//https://blog.naver.com/eziya76/221472568302
#define N_ADC_CHANNEL (2)

static uint32_t adcValues[N_ADC_CHANNEL];
volatile bool updateAdcValues = false;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	updateAdcValues = true;
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}

void appSetup() {
	HAL_ADC_Start_DMA(&hadc, adcValues, N_ADC_CHANNEL);

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim22, TIM_CHANNEL_2);

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
		htim2.Instance->CCR1  = adcValues[0] >> 4;
		htim22.Instance->CCR2 = adcValues[1] >> 4;

		OLED_Clear();
		for (int i = 0; i < N_ADC_CHANNEL; i++) {
			char pStr[40] = { 0, };
			sprintf(pStr, "%d: %d", i, (int) adcValues[i]);
			OLED_ShowString(0, i, pStr, 1);
		}
	}
}
