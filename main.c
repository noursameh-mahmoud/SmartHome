/*
 * Smart_Home.c
 *
 * Created: 06-Oct-24 5:48:18 PM
 * Author : 
 */ 

/* STD LIBS */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/* MCAL */
#include "DIO_interface.h"
#include "UART_interface.h"
#include "TMR1_interface.h"
#include "TMR1_config.h"
#include "TMR0_interface.h"
#include "TMR0_config.h"
#include "ADC_interface.h"
#include "TWI_interface.h"
/* HAL */
#include "EEPROM_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include "BUZ_interface.h"
#include "SRVM_interface.h"
#include "DCM_interface.h"
#include "LM35_interface.h"
#include "LM35_config.h"

#include "HOME_interface.h"
#include "Admin_interface.h"
#include "User_interface.h"


#define F_CPU 16000000UL
#include <util/delay.h>


int main(void)
{
	HOME_INIT();
	HOME_Start();
}
 