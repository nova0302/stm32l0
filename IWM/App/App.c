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

extern ADC_HandleTypeDef hadc;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim6;

//https://blog.naver.com/eziya76/221472568302
#define N_ADC_CHANNEL (3)

enum {
	SAMPLE_SIG
};

typedef	struct _event {
		uint16_t sig;
		/* event parameters */
		uint32_t now;
		bool s1, s2, s3, s4;
		bool mEntry, mExit;
		bool sEntry, sExit;
		uint8_t curPos;
	} event;
static uint32_t adcValues[N_ADC_CHANNEL];
volatile bool updateAdcValues = false;

void systemHearbit();
void swEvntCheck(event * e);

void showMenu(uint8_t curPos);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	updateAdcValues = true;
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}

void appSetup() {
	lcd_init(&hi2c1);
	OLED_ShowString(1, 1, "Welcome\nWashing Machine", 0);
	HAL_Delay(4000);
	//HAL_ADC_Start_DMA(&hadc, adcValues, N_ADC_CHANNEL);
	//HAL_TIM_Base_Start(&htim6);
}
void appLoop() {
	systemHearbit();
	static enum {
		INIT, MAIN, SEL_MOD, MANUAL, SEMI_ATUO
	} state = INIT;

	static event evt;
	event * e = &evt;
	static uint32_t last;


	/* buffering inputs*/

	evt.sig = SAMPLE_SIG;
	evt.now = HAL_GetTick();
	swEvntCheck(e);

	switch (state) {
	case INIT:
		e->mEntry = true;
		e->mExit = false;
		OLED_Clear();
		state = MAIN;
	case MAIN:
		if (e->mEntry) {
			e->mEntry = false;
			e->curPos = 1;
			showMenu(1);
		}
		if (e->s4 && e->curPos == 2) {
			e->curPos = 1;
			showMenu(1);
		}
		if (e->s2 && e->curPos == 1) {
			e->curPos = 2;
			showMenu(2);
		}
		if (e->s1) {
			e->mExit = true;
		}
		if (e->mExit) {
			state = SEL_MOD;
			e->mEntry = false;
			e->sEntry = true;
			last = e->now;
		}
		break;
	case SEL_MOD:
		if (e->now - last > 1000) {
			last = e->now;
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		}
		break;
	case MANUAL:
	case SEMI_ATUO:
	default:
		break;

	}
}

#define IS_PRESSED(n) (prevS##n && !s##n)

void swEvntCheck(event * e) {
	static uint32_t last;
	static bool prevS1, prevS2, prevS3, prevS4;
	uint32_t now = HAL_GetTick();
	if (now - last > 10) {
		bool s1 = HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin);
		bool s2 = HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin);
		bool s3 = HAL_GPIO_ReadPin(S3_GPIO_Port, S3_Pin);
		bool s4 = HAL_GPIO_ReadPin(S4_GPIO_Port, S4_Pin);

		e->s1 = IS_PRESSED(1);
		e->s2 = IS_PRESSED(2);
		e->s3 = IS_PRESSED(3);
		e->s4 = IS_PRESSED(4);

		prevS1 = s1;
		prevS2 = s2;
		prevS3 = s3;
		prevS4 = s4;

		last = now;
	}
}

void systemHearbit() {
	static uint32_t last;
	uint32_t now = HAL_GetTick();
	if (now - last > 500) {
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		last = now;
	}
}
void showMenu(uint8_t curPos) {
	OLED_ShowString(1, 1, "Menu", 1);
	OLED_ShowString(1, 2, "-ENTER", !(curPos == 1));
	OLED_ShowString(1, 3, "-LOG",   !(curPos == 2));
}

/*
 if (updateAdcValues) {
 updateAdcValues = false;
 OLED_Clear();
 for (int i = 0; i < N_ADC_CHANNEL; i++) {
 char pStr[40] = { 0, };
 sprintf(pStr, "%d: %d", i, (int) adcValues[i]);
 OLED_ShowString(0, i, pStr, 1);
 }
 }
 */

