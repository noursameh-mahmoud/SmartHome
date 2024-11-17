/*
 * DCM_program.c
 *
 * Created: 7/29/2024 10:10:43 PM
 *  Author: waadr
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "TMR0_interface.h"

/* HAL */
#include "DCM_interface.h"

void DCM_init(u8 motorId)
{
	/* Initializ H-Bridge As Output Pins depend on motor id*/
	switch(motorId)
	{
		case DCM_MOTOR_A:
		DIO_SetPinDirection(DIO_PORTC ,DIO_PIN3, DIO_PIN_OUTPUT);
		DIO_SetPinDirection(DIO_PORTC ,DIO_PIN4, DIO_PIN_OUTPUT);
		DIO_SetPinDirection(DIO_PORTD ,DIO_PIN4, DIO_PIN_OUTPUT);
		break;
		
		case DCM_MOTOR_B:
		DIO_SetPinDirection(DIO_PORTC ,DIO_PIN5, DIO_PIN_OUTPUT);
		DIO_SetPinDirection(DIO_PORTC ,DIO_PIN6, DIO_PIN_OUTPUT);
		DIO_SetPinDirection(DIO_PORTD ,DIO_PIN5, DIO_PIN_OUTPUT);
		break;
	}
}
void DCM_on(u8 motorId, u8 motorDirection)
{
	/* Turn the desired(motorId) DC motor on using H-Bridge
	 By Setting Dir and Enable pins with high
	 or Dir Low depend on motorDirection*/
	 
	switch(motorId)
	{
		case DCM_MOTOR_A:
		switch(motorDirection)
		{
			case DCM_CLOCK_WISE:
			DIO_SetPinValue(DIO_PORTC, DIO_PIN3, DIO_PIN_HIGH);
			DIO_SetPinValue(DIO_PORTC, DIO_PIN4, DIO_PIN_LOW);
			break;
			
			case DCM_COUNTER_CLOCK_WISE:
			DIO_SetPinValue(DIO_PORTC, DIO_PIN3, DIO_PIN_LOW);
			DIO_SetPinValue(DIO_PORTC, DIO_PIN4, DIO_PIN_HIGH);
			break;
		}
		DIO_SetPinValue(DIO_PORTD, DIO_PIN4, DIO_PIN_HIGH);
		break;
		
		case DCM_MOTOR_B:
		switch(motorDirection)
		{
			case DCM_CLOCK_WISE:
			DIO_SetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_HIGH);
			DIO_SetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW);
			break;
			
			case DCM_COUNTER_CLOCK_WISE:
			DIO_SetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_LOW);
			DIO_SetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH);
			break;
		}
		DIO_SetPinValue(DIO_PORTD, DIO_PIN5, DIO_PIN_HIGH);
		break;
	}
}
void DCM_onControlSpeed(u8 motorId, u8 motorDirection, u8 motorSpeed)
{
	/* Controlling desired(motorId) DC motor speed using PWM
	mode from TMR0 by setting Duty Cycle and turn it on using H-Bridge
	 By Setting Dir and Enable pins with high
	 or Dir Low depend on motorDirection*/
	 
	switch(motorId)
	{
		case DCM_MOTOR_A:
		switch(motorDirection)
		{
			case DCM_CLOCK_WISE:
			DIO_SetPinValue(DIO_PORTC, DIO_PIN3, DIO_PIN_HIGH);
			DIO_SetPinValue(DIO_PORTC, DIO_PIN4, DIO_PIN_LOW);
			break;
			
			case DCM_COUNTER_CLOCK_WISE:
			DIO_SetPinValue(DIO_PORTC, DIO_PIN3, DIO_PIN_LOW);
			DIO_SetPinValue(DIO_PORTC, DIO_PIN4, DIO_PIN_HIGH);
			break;
		}
		break;
		
		case DCM_MOTOR_B:
		switch(motorDirection)
		{
			case DCM_CLOCK_WISE:
			DIO_SetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_HIGH);
			DIO_SetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW);
			break;
			
			case DCM_COUNTER_CLOCK_WISE:
			DIO_SetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_LOW);
			DIO_SetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH);
			break;
		}
		break;
	}
	
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT);
	TMR0_init();
	TMR0_setDutyCycleUsingFastPWM(motorSpeed);
	TMR0_start();
}
void DCM_off(u8 motorId)
{
	/* Turn desired(motorId) DC motor off using H-Bridge
	   By Setting Enable pin with low */
	   
	switch(motorId)
	{
		case DCM_MOTOR_A:
		DIO_SetPinValue(DIO_PORTD, DIO_PIN4, DIO_PIN_LOW);
		break;
		
		case DCM_MOTOR_B:
		DIO_SetPinValue(DIO_PORTD, DIO_PIN5, DIO_PIN_LOW);
		break;
	}
}

