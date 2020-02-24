/*
 * obser.c
 *
 *  Created on: 2020. 2. 20.
 *      Author: Sanglae Kim
 */

#include "obser.h"
#include "LCD.h"


void button_Init(Button *pButton) {
	pButton->listener_count = 0;
}

void button_RemoveClickListener(Button *pButton, void (*fp)(uint32_t))
{
	unsigned i;
	//void (*temp)(uint32_t);

	for (i = 0; i < pButton->listener_count; ++i) {
		if (pButton->listener_list[i] == fp) {
			pButton->listener_count--;
			pButton->listener_list[i] =
					pButton->listener_list[pButton->listener_count];
		}
	}
}

void button_AddClickListener(Button *pButton, void (*fp)(uint32_t)) {
	button_RemoveClickListener(pButton, fp);
	pButton->listener_list[pButton->listener_count++] = fp;
}

void button_Click(Button *pButton, uint32_t j) {
	unsigned i;
	for (i = 0; i < pButton->listener_count; ++i) {
		pButton->listener_list[i](j);
	}
}

/* observer component 1 */
void observer1_OnClick(uint32_t i) {
	char theString[16];
	sprintf(theString, "i    : %d", (int)i);
	LCD_Puts(0, 0, theString);
	//printf( "observer_OnClick( 0x%X, 0x%X )\r\n", x, y );
}
void observer2_OnClick(uint32_t i) {
	char theString[16];
	sprintf(theString, "%d * 4: %d", (int)i, (int)i*4);
		LCD_Puts(0, 1, theString);
	//printf( "observer_OnClick( 0x%X, 0x%X )\r\n", x, y );
}
/* observer component 2 */

