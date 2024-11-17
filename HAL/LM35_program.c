/*
 * LM35_program.c
 *
 * Created: 7/6/2024 11:49:45 PM
 *  Author: waadr
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "ADC_interface.h"
#include "DIO_interface.h"

/* HAL */
#include "LM35_interface.h"
#include "LM35_config.h"


void LM35_init(void)
{
	DIO_SetPinDirection(DIO_PORTA,LM35_CHANNEL_NUM,DIO_PIN_INPUT);
	ADC_init(ADC_REFERENCE_INTERNAL);
}


u8 LM35_getTemperature(void)
{
	u16 digitalVal,analogVal;
	u8 temp;
	
	digitalVal = ADC_getDigitalValue(LM35_CHANNEL_NUM);
	
	analogVal = ((u32)digitalVal*2560)/1024;
	
	temp = analogVal/10;
	
	return temp;
}