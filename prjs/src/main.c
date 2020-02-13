/*
 ******************************************************************************
 File:     main.c
 Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2020-02-09

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
//GPIO_MODER_MODE0;
/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void) {
	// 7.3.12 GPIO clock enable register(RCC_IOPENR)
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Enable GPIOA Clock.

	// 00: input, 01:general purpose output mode, 10:Alternate function mode, 11:Analog mode(reset state)
	// PA0 as output
	GPIOA->MODER &= ~(0x3 << 0);// Clear mode register for PA0
	GPIOA->MODER |=  (0x1 << 0); // set 0th bit

	/* PA15 as input pullup configuration for btn  */
// 0b00~~~~~~~ input mode
	GPIOA->MODER &= ~(0x3 << 30); // clear GPIOA->MODER[31:0]
// pullup, PUPDR 0b01~~~~~~~~~~~
	GPIOA->PUPDR &= ~(0x1 << 31); // clear 32nd bit
	GPIOA->PUPDR |= (0x1 << 30); // set 31st bit

	/* TODO - Add your application code here */
	while (1) {
		if (GPIOA->IDR & (0x1 << 15))
			GPIOA->ODR |= (0x1 << 0);
		else
			GPIOA->ODR &= ~(0x1 << 0);
	}

	return 0;
}