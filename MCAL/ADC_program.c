/*
 * ADC_program.c
 *
 * Created: 7/6/2024 7:46:09 PM
 *  Author: waadr
 */ 
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"


void ADC_init(u8 referenceVoltage)
{
	switch(referenceVoltage)
	{
		//Select Reference Voltage
		
		//Select AREF
		case ADC_REFERENCE_AREF:
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		break;
		
		//Select AVCC
		case ADC_REFERENCE_AVCC:
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		
		//Select Internal
		case ADC_REFERENCE_INTERNAL:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	}
	
	//Set Right Adjustment
	CLR_BIT(ADMUX,ADLAR);
	
	// Single Conversion Mode
	CLR_BIT(ADCSRA,ADATE);
	
	//Disable ADC Interrupt
	CLR_BIT(ADCSRA,ADIE);
	
	// Prescaler 128 For 16MHZ (125 KHZ)
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS0);
	
	//ADC ENABLE
	SET_BIT(ADCSRA,ADEN);
}


u16 ADC_getDigitalValue(u8 channelNum)
{
	if(channelNum<32)
	{
		//Clear ADMUX Channel Bits
		ADMUX &= 0xE0; //0b11100000
		
		// Select Channel Number
		ADMUX |= channelNum;
		
		// Start Conversion
		SET_BIT(ADCSRA,ADSC);
		
		// Busy wait on ADC flag
		while(0 == GET_BIT(ADCSRA,ADIF));
		
		// Clear Flag(write one to clear)
		SET_BIT(ADCSRA,ADIF);
		
		return ADC_u16;
	}
	else
	{
		return 0;
	}
	
	
	
}