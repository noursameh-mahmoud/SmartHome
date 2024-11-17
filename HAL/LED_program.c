/*
 * LED_program.c
 *
 * Created: 12/18/2023 4:14:15 PM
 *  Author: waadr
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "DIO_private.h"


void LED_init(u8 LedPort, u8 LedPin)
{
 DIO_SetPinDirection(LedPort,LedPin,DIO_PIN_OUTPUT);
}

void LED_on(u8 LedPort, u8 LedPin)
{
	DIO_SetPinValue(LedPort,LedPin,DIO_PIN_HIGH);
}
void LED_off(u8 LedPort, u8 LedPin)
{
	DIO_SetPinValue(LedPort,LedPin,DIO_PIN_LOW);
}

void LED_toggle (u8 LedPort, u8 LedPin)
{
	DIO_TooglePinValue(LedPort,LedPin);
}