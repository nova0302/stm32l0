/*
 * App.c
 *
 *  Created on: Dec 25, 2021
 *      Author: LG
 */
#include <stdio.h>
#include <stdbool.h>
#include "App.h"
#include "main.h"
#include "lcd_user.h"

extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_adc;

extern I2C_HandleTypeDef hi2c1;

volatile bool updateAdcValues = false;
static uint32_t adcValues[3];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	updateAdcValues = true;
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}


void appSetup(){
	lcd_init(&hi2c1);
	OLED_ShowString(0, 0, "Starting...", 0);
}
void appLoop(){
	static bool btnLastStatus;
	static uint32_t lastTime, lLastTime;

	uint32_t now = HAL_GetTick();
	bool btnStatus = HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin);

	if(now - lastTime > 10){
#define BTN_FALLING_EDGE (btnLastStatus == true && btnStatus == false)
		//if(btnLastStatus == true && btnStatus == false){
		if(BTN_FALLING_EDGE){
			HAL_ADC_Start_DMA(&hadc, adcValues, 3);
			//HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
		}
		lastTime = now;
		btnLastStatus = btnStatus;
	}
	if(updateAdcValues){
		updateAdcValues = false;
		uint32_t lAdcValues[3];
		OLED_Clear();
		char strBuffer[40] = {0,};
		__disable_irq();
		for(int i = 0; i<3; i++){
			lAdcValues[i] = adcValues[i];
		}
		__enable_irq();
		for(int i=0; i<3; i++){
			sprintf(strBuffer, "%d: %d",i, (int)lAdcValues[i]);
			OLED_ShowString(0, i, strBuffer, 0);
		}
	}
	if(now - lLastTime > 1000){
		lLastTime = now;
		HAL_ADC_Start_DMA(&hadc, adcValues, 3);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	}
}


