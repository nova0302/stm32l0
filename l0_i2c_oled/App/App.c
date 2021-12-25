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

extern I2C_HandleTypeDef hi2c1;

void appSetup() {
	lcd_init(&hi2c1);
}
typedef struct _pos {
	uint8_t x, y;
} pos;

void incPos(pos *p) {
	if (p->x++ > 8) {
		p->x = 0;
	}
	if (p->y++ > 8) {
		p->y = 0;
	}
}
void appLoop() {

	static pos p = { 0, 0 };
	char str[20] = {0,};
	char * pStr = str;
	sprintf(pStr,"x: %d, y: %d", p.x, p.y);

	OLED_ShowString(p.x*8, p.y, pStr, 1);
	HAL_Delay(1000);
	incPos(&p);
	OLED_Clear();
}

