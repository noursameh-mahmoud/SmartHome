/*
 * BUZ_program.c
 *
 * Created: 2/7/2024 1:41:20 PM
 *  Author: waadr
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "BUZ_interface.h"
#include "DIO_private.h"


void BUZ_init(u8 BUZPort, u8 BUZPin)
{
	DIO_SetPinDirection(BUZPort,BUZPin,DIO_PIN_OUTPUT);
}

void BUZ_on(u8 BUZPort, u8 BUZPin)
{
	DIO_SetPinValue(BUZPort,BUZPin,DIO_PIN_HIGH);
}
void BUZ_off(u8 BUZPort, u8 BUZPin)
{
	DIO_SetPinValue(BUZPort,BUZPin,DIO_PIN_LOW);
}

void BUZ_toggle (u8 BUZPort, u8 BUZPin)
{
	DIO_TooglePinValue(BUZPort,BUZPin);
}