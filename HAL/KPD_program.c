/*
 * KPD_program.c
 *
 * Created: 3/7/2024 8:44:54 PM
 *  Author: waadr
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "KPD_interface.h"
#include "KPD_config.h"


void KPD_init(void)
{
	DIO_SetPinDirection(KPD_COL0_PORT,KPD_COL0_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(KPD_COL1_PORT,KPD_COL1_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(KPD_COL2_PORT,KPD_COL2_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(KPD_COL3_PORT,KPD_COL3_PIN,DIO_PIN_OUTPUT);
	
	//ROWS >> input
	DIO_SetPinDirection(KPD_ROW0_PORT,KPD_ROW0_PIN,DIO_PIN_INPUT);
	DIO_SetPinDirection(KPD_ROW1_PORT,KPD_ROW1_PIN,DIO_PIN_INPUT);
	DIO_SetPinDirection(KPD_ROW2_PORT,KPD_ROW2_PIN,DIO_PIN_INPUT);
	DIO_SetPinDirection(KPD_ROW3_PORT,KPD_ROW3_PIN,DIO_PIN_INPUT);
	
	//active internal pull up (ROWS initial values are ones)
	DIO_ActivePinPullUpResistance(KPD_ROW0_PORT,KPD_ROW0_PIN);
	DIO_ActivePinPullUpResistance(KPD_ROW1_PORT,KPD_ROW1_PIN);
	DIO_ActivePinPullUpResistance(KPD_ROW2_PORT,KPD_ROW2_PIN);
	DIO_ActivePinPullUpResistance(KPD_ROW3_PORT,KPD_ROW3_PIN);
}





u8 KPD_getValue(void)
{
	u8 colsPorts[4] ={KPD_COL0_PORT,KPD_COL1_PORT,KPD_COL2_PORT,KPD_COL3_PORT};
	u8 colsPins [4] ={KPD_COL0_PIN ,KPD_COL1_PIN ,KPD_COL2_PIN ,KPD_COL3_PIN};
	u8 rowsPorts[4] ={KPD_ROW0_PORT,KPD_ROW1_PORT,KPD_ROW2_PORT,KPD_ROW3_PORT};
	u8 rowsPins [4] ={KPD_ROW0_PIN ,KPD_ROW1_PIN ,KPD_ROW2_PIN ,KPD_ROW3_PIN};
	u8 kpdKeys[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
	
	u8 pinValue;
	u8 colsCounter,rowsCounter;
	
	
	for(colsCounter=0;colsCounter<4;colsCounter++)
	{
		DIO_SetPinValue(colsPorts[colsCounter],colsPins[colsCounter],DIO_PIN_LOW);
		
		for(rowsCounter=0;rowsCounter<4;rowsCounter++)
		{
			//Read Each Row
		DIO_getPinValue(rowsPorts[rowsCounter],rowsPins[rowsCounter],&pinValue);
			
			
             if(pinValue == 0)
			 {
				 while(pinValue == 0)
				 {
					 DIO_getPinValue(rowsPorts[rowsCounter],rowsPins[rowsCounter],&pinValue);
					 
				 }
				 return kpdKeys[rowsCounter][colsCounter];
			 }
		}
			 
			 // Deactivate current cols
			 DIO_SetPinValue(colsPorts[colsCounter],colsPins[colsCounter],DIO_PIN_HIGH);
		 
	}
	      return KPD_NOT_PRESSED;
}