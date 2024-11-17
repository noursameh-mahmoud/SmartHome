/*
 * SRVM_program.c
 *
 * Created: 7/30/2024 1:48:00 AM
 *  Author: waadr
 */ 
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "TMR1_interface.h"

/* HAL */
#include "SRVM_interface.h"


void SRVM_init(void)
{
	/* OC1A pin as output pin */
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
	
	/* TMR1 init at pwm mode 14 */
	TMR1_init();
}


void SRVM_on(u8 angle)
{
	/* Set pwm fre. = 50
	   Set pwm duty cycle between 5 : 10
	   depend on desired angle
	   TMR1 start */
	switch(angle)
	{
		case SRVM_ANGLE_N90:
		TMR1_setFastPWM_usingMode14(5,50);
		TMR1_start();
		break;
		
		case SRVM_ANGLE_0:
		TMR1_setFastPWM_usingMode14(7.5,50);
		TMR1_start();
		break;
		
		case SRVM_ANGLE_90:
		TMR1_setFastPWM_usingMode14(10,50);
		TMR1_start();
		break;
	}
}


void SRVM_off(void)
{
	/* TMR1 stop */
	TMR1_stop();
}