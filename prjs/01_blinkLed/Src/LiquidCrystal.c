#include <stm32l052xx.h>
#include "main.h"


#define D2_Pin GPIO_PIN_2
#define D3_Pin GPIO_PIN_3
#define D4_Pin GPIO_PIN_4
#define D5_Pin GPIO_PIN_5
#define D6_Pin GPIO_PIN_6
#define D7_Pin GPIO_PIN_7
#define D8_Pin GPIO_PIN_8

#define D2_GPIO_Port GPIOA
#define D3_GPIO_Port GPIOA
#define D4_GPIO_Port GPIOA
#define D5_GPIO_Port GPIOA
#define D6_GPIO_Port GPIOA
#define D7_GPIO_Port GPIOA
#define D8_GPIO_Port GPIOA



// Advanced macro to swap routine names and parameters.

#define digitalWrite(PIN_NAME,PIN_STATE) \
HAL_GPIO_WritePin(D##PIN_NAME##_GPIO_Port,D##PIN_NAME##_Pin,GPIO_PIN_##PIN_STATE)

#define digitalRead(PIN_NAME) \
HAL_GPIO_ReadPin(D##PIN_NAME##_GPIO_Port,D##PIN_NAME##_Pin)

void init(){
	digitalWrite(2, SET);
	/*
	HAL_GPIO_WritePin(GPIOA, rs_Pin,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOA, rw_Pin,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOA, d4_Pin,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOA, d5_Pin,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOA, d6_Pin,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOA, d7_Pin,  GPIO_PIN_RESET );
*/
}
