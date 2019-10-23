/*
 * BCM.h
 *
 *  Created on: Oct 19, 2019
 *      Author: Rafaat
 */

#ifndef BCM_RX_H_
#define BCM_RX_H_

#include "UART.h"
#include"Std_Types.h"
#include <avr/interrupt.h>
#include "LCD.h"

typedef enum{INVALIDARGUMENT =-500,INVALID_DATA_LENGTH=-400,INVALID_CHECK_SUM=-300,OK=1}EnmBCMError_t;

/*
 * @LOKING_MECHANISM
 */
typedef enum{UNLOCKED=0,LOCKED = 1}Lock_t;

/*
 *  This is a Configuration structure for a BCM_Rx_Config
 */

typedef struct
{
	uint8 BCM_ID;			/* Possible values  can be from 0 to 255 */
	uint8 Lock;				/* Possible values is @LOKING_MECHANISM  */
	uint16 Data_Length;		/* Possible values can be from 1-> 65535  */
	uint8  CheckSum;		/*Check sum will be used in run time */
	uint8 *Data;			/*pointer to the internal buffer*/
}BCM_Rx_Config_t;

BCM_Rx_Config_t BCM_Rx;


/*
 * BCM Init
 */
EnmBCMError_t BCM_Rx_Init(ptrTmuFunctionCallBk_t func);

/*
 * BCM Rx setup buffer
 */
EnmBCMError_t BCM_Rx_SetupRxBuffer(uint8 *Buffer,uint16 Size);

/*
 * BCM Rx Dispatcher
 */
EnmBCMError_t BCM_RxDispatch(void);
/*
 * BCM callback
 */
void BCM_Callback();


#endif /* BCM_RX_H_ */
