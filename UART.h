/*
 * UART.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Rafaat
 */

#ifndef UART_H_
#define UART_H_
#include "Std_Types.h"
#include <avr/io.h>
void UART_Init();
uint8 UART_Recieve();
void UART_Send(uint8 Char);
void UART_setCallBack(ptrTmuFunctionCallBk_t FuncName);
#endif /* UART_H_ */
