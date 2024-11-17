/*
 * HOME_interface.c
 *
 * Created: 06-Oct-24 6:38:01 PM
 *  Author: 
 */ 


/* STD LIBS */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/* MCAL */
#include "DIO_interface.h"
#include "UART_interface.h"
#include "TMR1_interface.h"
#include "TMR1_config.h"
#include "ADC_interface.h"
/* HAL */
#include "LCD_interface.h"
#include "LED_interface.h"
#include "SRVM_interface.h"
#include "DCM_interface.h"
#include "LM35_interface.h"
#include "BUZ_interface.h"
#include "KPD_interface.h"

#include "HOME_interface.h"

#include "User_interface.h"
#include "Admin_interface.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void LIGHT_SYSTEM( u8 room)
{
	switch(room)
	{
		case ROOM1:
		LCD_clear();
		LED_toggle (DIO_PORTA,DIO_PIN2);
		UART_Tx_NewLine();
		UART_sendString("Room1 light changed! ");
		UART_Tx_NewLine();
		LCD_writeString("Room1 light changed! ");
		break;
		
		case ROOM2:
		LCD_clear();
		LED_toggle (DIO_PORTA,DIO_PIN3);
		UART_Tx_NewLine();
		UART_sendString(" Room 2 light changed! ");
		UART_Tx_NewLine();
		LCD_writeString(" Room 2 light changed! ");
		break;
		
		case LIVING_ROOM:
		LCD_clear();
		LED_toggle (DIO_PORTA,DIO_PIN4);
		UART_Tx_NewLine();
		UART_sendString(" Living room light changed! ");
		UART_Tx_NewLine();
		LCD_writeString(" Living room light changed! ");
		break;
		
		case KITCHEN:
		LCD_clear();
		LED_toggle (DIO_PORTA,DIO_PIN5);
		UART_Tx_NewLine();
		UART_sendString(" Kitchen light changed! ");
		UART_Tx_NewLine();
		LCD_writeString(" Kitchen light changed! ");
		break;
		
		case BATHROOM:
		LCD_clear();
		LED_toggle (DIO_PORTA,DIO_PIN6);
		UART_Tx_NewLine();
		UART_sendString(" Bathroom light changed! ");
		UART_Tx_NewLine();
		LCD_writeString(" Bathroom light changed! ");
		break;
	}
}

void DIMMING_LAMP(u8 lumination_int)
{
	lumination_int -= '0' ;
	
	TMR0_setDutyCycleUsingFastPWM(lumination_int*10);
	TMR0_start();
		UART_Tx_NewLine();
		UART_sendString(" Dimming Lamp Intensity Changed! ");
		UART_Tx_NewLine();
		LCD_writeString(" Dimming Lamp Intensity Changed! ");
	
}

void OPEN_DOOR()
{
	SRVM_on(SRVM_ANGLE_90);
	LCD_clear();
	UART_Tx_NewLine();
	UART_sendString("Door is open");
	UART_Tx_NewLine();
	LCD_writeString("Door is open");   //for continous display on lcd
}
void CLOSE_DOOR()
{
	SRVM_on(SRVM_ANGLE_0);
	LCD_clear();
	UART_Tx_NewLine();
	UART_sendString("Door is closed");
	UART_Tx_NewLine();
	LCD_writeString("Door is closed");   //for continous display on lcd
}
void AC_STATE()
{
	
			u8 Temp = 0 ;
			Temp = LM35_getTemperature();
			if (Temp<=21)
			{
				
				DCM_off(DCM_MOTOR_A);
				UART_Tx_NewLine();
				UART_sendString ("AC OFF!");
				UART_Tx_NewLine();
				LCD_writeString ("AC OFF!");
				
			}
			else if(Temp>=28)
			{
				DCM_on(DCM_MOTOR_A,DCM_CLOCK_WISE);
				UART_Tx_NewLine();
				UART_sendString(" AC ON! ");
				UART_Tx_NewLine();
				LCD_writeString(" AC ON! ");
			
	}

	
}
void	FIRE_ALARM()
{
	    BUZ_init(DIO_PORTA,DIO_PIN7);
	    BUZ_on(DIO_PORTA,DIO_PIN7);
		_delay_ms(3000);
		BUZ_off(DIO_PORTA,DIO_PIN7);
		
}

void HOME_INIT()
{
	//HOME LIGHTS
	LED_init(DIO_PORTA,DIO_PIN2);
	LED_init(DIO_PORTA,DIO_PIN3);
	LED_init(DIO_PORTA,DIO_PIN4);
	LED_init(DIO_PORTA,DIO_PIN5);
	LED_init(DIO_PORTA,DIO_PIN6);
	
	//DIMMER LED (OC0 PIN)
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT);
	TMR0_init();
	
	//BLUETOOTH MODULE
	UART_init();
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT); //TX PIN
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT);  //RX PIN
	
	
	//DOOR (OC1A PIN)
	SRVM_init();
	
	//AC CONTROLLER
	LM35_init(); //TEMPERATURE SENSOR
	DCM_init(DCM_MOTOR_A); //AC FAN
	
	//ON-SITE
	LCD_init();
	KPD_init();
	
	//EXTERNAL EEPROM 
	EEPROM_init();
	_delay_ms(5);
	EEPROM_writeByte(ADMIN_SIGNUP_LOC,0);
	_delay_ms(5);
	/*EEPROM_writeByte(ADDRESS_NUM_OF_USERS,0);
	_delay_ms(5);8*/
	
}
void USER_HOME_Cntrl_lcd()
{
	
	LCD_writeString("USER MENU.");
	_delay_ms(1500);
	LCD_clear();
	
	LCD_writeString("1-LIGHT SYSTEM ");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_writeString("2-DIMMING LIGHT");
	_delay_ms(1500);
	LCD_clear();
	LCD_writeString("3-AC CONTROL");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_writeString("4-LOG OUT");
	_delay_ms(1500);
	
	u8 option= 0xFF;
	while(1)
	{
		option = KPD_getValue();
		if (option != 0xFF)
		{
			break;
		}
	}
	
	
	switch(option)
	{
		 
		case '1' :
			LCD_clear();
			LCD_writeString("1-ROOM1 2-ROOM2  ");
			LCD_goToSpecificPosition(LCD_LINE_TWO,0);
			LCD_writeString("3-LIVING ROOM ");
			_delay_ms(1500);
			LCD_clear();
			LCD_writeString("4-KITCHEN");
			LCD_goToSpecificPosition(LCD_LINE_TWO,0);
			LCD_writeString("5-BATHROOM ");
			_delay_ms(1500);
			
		u8 choice=0xFF;
		while(1)
		{
			choice = KPD_getValue();
			if (choice != 0xFF)
			{
				break;
			}
		}
	
			switch(choice)
			{
			case '1' :
			LCD_clear();
			LIGHT_SYSTEM(ROOM1);
			break;
			case '2' :
			LCD_clear();
			LIGHT_SYSTEM(ROOM2);
			break;
			case '3' :
			LCD_clear();
			LIGHT_SYSTEM(LIVING_ROOM);
			break;
			case '4' :
			LCD_clear();
			LIGHT_SYSTEM(KITCHEN);
			break;
			
			case '5' :
			LCD_clear();
			LIGHT_SYSTEM(BATHROOM);
			break;
			
			default:
			LCD_clear();
			LCD_writeString("Invalid Room");
			_delay_ms(1000);
			break;
	
		}
		
		case '2' :
			LCD_clear();
			LCD_writeString("Insert intensity:");
			LCD_goToSpecificPosition(LCD_LINE_TWO,0);
			LCD_writeString("From 1 to 5:");
			u8 lumination=0;
			while(1)
			{
				lumination = KPD_getValue();
				if (lumination != 0xFF)
				{
					break;
				}
			}
			DIMMING_LAMP(lumination);
			break;
		
		case '3' :
			LCD_clear();
			AC_STATE();
			break;
		
		case '4' :
			LCD_clear();
			HOME_Start();
		
		default:
			LCD_clear();
			LCD_writeString("Please insert");
			LCD_goToSpecificPosition(LCD_LINE_TWO,0);
			LCD_writeString("a valid input:");
			break;
		
	}
	
USER_HOME_Cntrl_lcd();

 
}


void USER_HOME_Cntrl_remotely()
{
	u8 option,choice,lumination;
	UART_sendString("1-LIGHT SYSTEM  2-DIMMING LAMP ");
	UART_Tx_NewLine();
	UART_sendString("3-AC Control 4-LOG OUT");
	UART_Tx_NewLine();
	UART_RxChar(&option);
	UART_Tx_NewLine();
	switch(option)
	{
		case '1':
		UART_sendString("1-ROOM1  2-ROOM2  ");
		UART_Tx_NewLine();
		UART_sendString("3-LIVING ROOM  4-KITCHEN");
		UART_Tx_NewLine();
		UART_sendString("5-BATHROOM  ");
		UART_Tx_NewLine();
		UART_RxChar(&choice);
		switch(choice)
		{
			case '1' :
			LIGHT_SYSTEM(ROOM1);
			break;
			case '2' :
			LIGHT_SYSTEM(ROOM2);
			break;
			case '3' :
			LIGHT_SYSTEM(LIVING_ROOM);
			break;
			case '4' :
			LIGHT_SYSTEM(KITCHEN);
			break;
			
			case '5' :
			LIGHT_SYSTEM(BATHROOM);
			break;
			
			
		}
		
		UART_Tx_NewLine();
		break;
		
		case '2':
		UART_sendString("Please insert the lumination intensity:");
		UART_Tx_NewLine();
		UART_RxChar(&lumination);
		UART_Tx_NewLine();
		DIMMING_LAMP(lumination);
		break;
		
		case '3':
		AC_STATE();
		break;
		case '4':
		HOME_Start();
		break;

		default:
		UART_sendString("Please insert a valid input:");
		UART_Tx_NewLine();
		break;
		
	}
	USER_HOME_Cntrl_remotely();
}


void ADMIN_HOME_Cntrl()
{
	u8 option,choice,lumination,door_control;
	option=0;
	
	UART_sendString("1-LIGHT SYSTEM  2-DIMMING LAMP ");
	UART_Tx_NewLine();
	UART_sendString("3-AC Control 4-Door Control");
	UART_Tx_NewLine();
	UART_sendString("5-ADD User  6-REMOVE User");
	UART_Tx_NewLine();
	UART_sendString("7-Back to USER MODE");
	UART_Tx_NewLine();
	UART_RxChar(&option);
	UART_Tx_NewLine();
	switch(option)
	{
		case '1':
		UART_sendString("1-ROOM1  2-ROOM2  ");
		UART_Tx_NewLine();
		UART_sendString("3-LIVING ROOM  4-KITCHEN");
		UART_Tx_NewLine();
		UART_sendString("5-BATHROOM  ");
		UART_Tx_NewLine();
		UART_RxChar(&choice);
		switch(choice)
		{
			case '1' :
			LIGHT_SYSTEM(ROOM1);
			break;
			case '2' :
			LIGHT_SYSTEM(ROOM2);
			break;
			case '3' :
			LIGHT_SYSTEM(LIVING_ROOM);
			break;
			case '4' :
			LIGHT_SYSTEM(KITCHEN);
			break;
			
			case '5' :
			LIGHT_SYSTEM(BATHROOM);
			break;
			
		}
		
		UART_Tx_NewLine();
		break;
		
		case '2':
		UART_sendString("Insert Intensity From 1 to 5:");
		UART_Tx_NewLine();
		UART_RxChar(&lumination);
		UART_Tx_NewLine();
		DIMMING_LAMP(lumination);
		break;
		
		case '3':
		AC_STATE();
		break;
		
		case '4':
		UART_sendString("1-Open door 2-Close door");
		UART_RxChar(&door_control);
		if(door_control== '1') OPEN_DOOR();
		else if(door_control== '2') CLOSE_DOOR();
		break;
		
		case '5':
		ADMIN_Add_User();
		break;
		
		case '6':
		ADMIN_Remove_User();
		break;
		
		case '7':
		USER_MODE_Init();
		break;
		
		default:
		UART_sendString("Please insert a valid input:");
		UART_Tx_NewLine();
		break;
		
	}

	ADMIN_HOME_Cntrl();
}

void HOME_Start()
{
	u8 option=0;
	
	UART_sendString("Welcome to your smart home!");
	UART_Tx_NewLine();
	UART_sendString("1-ADMIN MODE  2-USER MODE");
	UART_Tx_NewLine();
	UART_RxChar(&option);
	UART_Tx_NewLine();
	
	LCD_writeString("WELCOME");
	LCD_clear();
	LCD_writeString("1-ADMIN MODE");
	LCD_goToSpecificPosition(1,0);
	LCD_writeString("2-USER MODE");
	
	if(option=='1')
	{
		LCD_clear();
		LCD_writeString("ADMIN MODE");
		ADMIN_MODE_Init();
		
	}
	else if(option=='2')
	{
		LCD_clear();
		LCD_writeString("USER MODE");
		USER_MODE_Init();
	}
	else
	{
		UART_sendString("Invalid option");
		UART_Tx_NewLine();
		
	}
}