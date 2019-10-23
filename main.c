/*
 * main.c
 *
 *  Created on: Oct 19, 2019
 *      Author: Rafaat
 */

#include "BCM_Rx.h"


void Send_data(void);

static uint8 buffer[19];
static uint8 index =19;
int main()
{
	BCM_Rx_Init(Send_data);
	BCM_Rx_SetupRxBuffer(buffer,19);
	sei();
	while(1)
	{
		BCM_RxDispatch();
		//_delay_ms(500);
	}
}


void Send_data(void)
{

	LCD_gotoRawCol(0,0);
	for(uint8_t x=3;x<index-1;x++)
	{
		LCD_displayChar(BCM_Rx.Data[x]);
		_delay_ms(1);

	}
}

