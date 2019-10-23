/*
 * UART.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Rafaat
 */
#include "UART.h"
#include <avr/interrupt.h>


ptrTmuFunctionCallBk_t g_ptr ;

void UART_Init()
{
UCSRB |=1<<RXEN|1<<RXCIE;
UCSRC |=1<<UCSZ1|1<<UCSZ0|1<<URSEL;
UBRRL = 0x33 ;

}

void UART_Send(uint8 Char)
{
	while(!(UCSRA&(1<<UDRE)));
	UDR=Char;
}

void UART_setCallBack(ptrTmuFunctionCallBk_t FuncName){
	g_ptr = FuncName;
}

ISR(USART_RXC_vect)
{
	if(*g_ptr!=NULL)
	   (*g_ptr)();
}

uint8 UART_Recieve()
{
	//while(!(UCSRA&(1<<RXC)));
	return UDR;
}



