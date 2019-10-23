/*
 * BCM.c
 *
 *  Created on: Oct 19, 2019
 *      Author: Rafaat
 */


#include "BCM_Rx.h"

ptrTmuFunctionCallBk_t FuncName = NULL ;
extern BCM_Rx_Config_t BCM_Rx;
static uint16 index=0;
static uint8 state=1;
static uint8 flag=0;
static uint8 SizeFlag=0;
static uint16 LengthSizeRx=0;

/************************************************************************
 * @Function name 			-BCM_Rx_Init
 *
 * @brief					- This Function is used to init the BCM Rx
 *
 * @param[in]				-ptr to the call back function that will be called after ISR fires
 *
 * @return					- EnmBCMError_t is an Error type
 *
 *
 * @note					- none
 *
 */


EnmBCMError_t BCM_Rx_Init(ptrTmuFunctionCallBk_t func)
{
	EnmBCMError_t retval=OK;

	BCM_Rx.BCM_ID='A';
	UART_Init();
	LCD_init();
	UART_setCallBack(BCM_Callback);
	if(func != NULL)
	{
		FuncName = func;

	}else
	{
		retval = INVALIDARGUMENT;
	}
	return retval;
}


/************************************************************************
 * @Function name 			-BCM_Rx_SetupRxBuffer
 *
 * @brief					- This Function is used to setup the Rx buffer
 *
 * @param[in]				- ptr to the buffer in the internal
 *
 * @param[in]				- the size of the array
 *
 * @return					- EnmBCMError_t is an Error type
 *
 *
 * @note					- none
 *
 */


EnmBCMError_t BCM_Rx_SetupRxBuffer(uint8 *Buffer,uint16 Size)
{
	EnmBCMError_t retval=OK;

	if(Buffer != NULL)
	{
		BCM_Rx.Data=Buffer;
		BCM_Rx.Data_Length=Size;
		BCM_Rx.Lock = 1;
	}
	else
	{
		retval = INVALIDARGUMENT;
	}
	return retval;

}


/************************************************************************
 * @Function name 			-BCM_RxDispatch
 *
 * @brief					- This Function is used to handling the recieving in run time
 *
 * @param[in]				- None
 *
 * @return					- EnmBCMError_t is an Error type
 *
 *
 * @note					- none
 *
 */

EnmBCMError_t BCM_RxDispatch()
{
	EnmBCMError_t retval=OK;
	if(BCM_Rx.Lock == 1)
	{
		switch(state)
		{
		case 0 : break;
		case 1 :
			if(BCM_Rx.Data[0] == BCM_Rx.BCM_ID)
			{

				index++;
				BCM_Rx.Lock = 1;
				state++;
				flag =0;

			}
			else
			{

			}
			break;
		case 2:
			if(flag==1)
			{
				flag=0;
				if(SizeFlag == 0)
				{

					LengthSizeRx=BCM_Rx.Data[index];

					SizeFlag++;
					index++;

				}else if(SizeFlag == 1)
				{

					LengthSizeRx|=(BCM_Rx.Data[index]<<8);
					SizeFlag++;
				}

				if(LengthSizeRx == BCM_Rx.Data_Length && SizeFlag== 2 )
				{
					SizeFlag =0;
					state++;
				}else
				{
					retval = INVALID_DATA_LENGTH;
					//	return retval;
				}
			}
			break;
		case 3 :
			if(flag==1)
			{
				BCM_Rx.CheckSum +=BCM_Rx.Data[index];
				index++;

				flag=0;
				if((index+1) == (BCM_Rx.Data_Length))
				{
					LCD_gotoRawCol(1,0);
					LCD_IntToStr(BCM_Rx.CheckSum);

					state++;
				}
			}
			break;

		case 4 :
			if(BCM_Rx.CheckSum == BCM_Rx.Data[index])
			{
				(*FuncName)();
				BCM_Rx.Lock = 0;
				flag=0;

			}else
			{
				retval = INVALID_CHECK_SUM;
			}
			break;
		}
	}
	return retval;
}

/************************************************************************
 * @Function name 			-BCM_Callback
 *
 * @brief					- This is the function will called in when ISR fires
 *
 * @param[in]				- None
 *
 * @return					- None
 *
 *
 * @note					- None
 *
 */
void BCM_Callback()
{
	BCM_Rx.Data[index]=UART_Recieve();

	flag=1;
}
