/*
 ******************************************************************************
 File:     main.c
 Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2020-02-05

 The MIT License (MIT)
 Copyright (c) 2019 STMicroelectronics

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 ******************************************************************************
 */

/* Includes */
#include <stddef.h>
#include "stm32l0xx.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
uint8_t updateSysClock = 0;

void changeSystemClock() {
	static uint8_t HSI16_flag = 0;
	if (HSI16_flag) {
		HSI16_flag = 0;
		if ((RCC->CR & RCC_CR_HSION) == 0)
			RCC->CR |= RCC_CR_HSION;
		while ((RCC->CR & RCC_CR_HSIRDY) == 0)
			;

		RCC->CFGR |= RCC_CFGR_SW_0;
		while ((RCC->CFGR & RCC_CFGR_SWS_0) == 0)
			;
	} else {
		HSI16_flag = 1;
		if ((RCC->CR & RCC_CR_MSION) == 0)
			RCC->CR |= RCC_CR_MSION;
		while ((RCC->CR & RCC_CR_MSIRDY) == 0)
			;
		RCC->CFGR &= ~(RCC_CFGR_SW_1 | RCC_CFGR_SW_0);
		while ((RCC->CFGR & (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0)) != 0)
			;
	}
}

#define Dly 500

volatile uint8_t flag = 0;
void EXTI4_15_IRQHandler() {
	if (EXTI->PR & EXTI_PR_PR15) {
		EXTI->PR |= EXTI_PR_PR15;
		updateSysClock = 1;
		if (flag) {
			flag = 0;
			GPIOA->BSRR = 1 << 1;
		} else {
			flag = 1;
			GPIOA->BRR = 1 << 1;
		}
	}
}
volatile int32_t TimeDelay;
void SysTick_Handler() {
	if (TimeDelay > 0)
		TimeDelay--;
}
void Delay(uint32_t nTime) {
	TimeDelay = nTime;
	while (TimeDelay != 0)
		;
}
void Systic_Init(uint32_t ticks) {

	//0xE000E010
	SysTick->CTRL = 0; // disable Systic
	SysTick->LOAD = ticks - 1; // Set reload register
	//Set interrupt priority of SysTic to least urgency (i.e., largest priority value)
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0;

	// Select processor clock: 1=Processor clock, 0=external clock
	//SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

	// Enables SysTick interrupt, 1=Enable, 0=Disable;
	SysTick->CTRL |= 1 << 1;

	// Enables SysTick
	SysTick->CTRL |= 1;

}
void SystemClockInit(void) {
	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSIRDY) == 0)
		;

	RCC->CFGR |= RCC_CFGR_SW_0;
	while ((RCC->CFGR & RCC_CFGR_SWS_0) == 0)
		;
}
/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void) {
//RCC_CFGR_SW;
	//SystemClockInit();
	Systic_Init(262);// for msi 2.07MHz
	//Systic_Init(2000); // for his16
	Delay(1000);
	/* TODO - Add your application code here */
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Enable GPIOA Clock.

	GPIOA->MODER &= ~(0x1 << 1); // PA0 as output
	GPIOA->MODER &= ~(0x1 << 3); // PA1 as output

	/* PA15 as input pullup configuration for btn  */
// 0b00~~~~~~~ input mode
	GPIOA->MODER &= ~(0x3 << 30);
// pullup, PUPDR 0b01~~~~~~~~~~~
	GPIOA->PUPDR &= ~(0x1 << 31); // clear 32nd bit
	GPIOA->PUPDR |= (0x1 << 30); // set 31st bit

// RM0376 cha 13
	EXTI->IMR |= EXTI_IMR_IM15;  // interrupt mask
	EXTI->FTSR |= EXTI_FTSR_FT15; // falling edge detection

// select PA15 among PB15, PC15,...refer RM0376 Ch 10 System configuration controller
	SYSCFG->EXTICR[3] |= ~(0xF << 12);

// RM0376 cha 12
	NVIC_EnableIRQ(EXTI4_15_IRQn);
	NVIC_SetPriority(EXTI4_15_IRQn, 0);

	while (1) {
		GPIOA->BSRR = 1;
		Delay(Dly);
		GPIOA->BRR = 1;
		Delay(Dly);
		//RCC->AHBENR |= RCC_AHBENR_;
		if (updateSysClock) {
			updateSysClock = 0;
			changeSystemClock();

		}
	}
	return 0;
}
