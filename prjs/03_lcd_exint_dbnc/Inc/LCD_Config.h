
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H 

#define _LCD_USE_FREERTOS 0
#define _LCD_COLS         16
#define _LCD_ROWS         2

#define _LCD_RS_PORT      GPIOA
#define _LCD_RS_PIN       rs_Pin

#define _LCD_E_PORT       GPIOA
#define _LCD_E_PIN        en_Pin

#define _LCD_RW_PORT      GPIOA
#define _LCD_RW_PIN       rw_Pin

#define _LCD_D4_PORT      GPIOA
#define _LCD_D4_PIN		  d4_Pin

#define _LCD_D5_PORT      GPIOA
#define _LCD_D5_PIN       d5_Pin

#define _LCD_D6_PORT      GPIOA
#define _LCD_D6_PIN       d6_Pin

#define _LCD_D7_PORT      GPIOA
#define _LCD_D7_PIN       d7_Pin

#endif

