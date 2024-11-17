/*
 * LCD_program.c
 *
 * Created: 3/5/2024 6:54:05 PM
 *  Author: waadr
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>


 #include"STD_TYPES.h"
 #include"BIT_MATH.h"
 #include"DIO_interface.h"
 #include"LCD_interface.h"
 #include"LCD_config.h"

//THIS FUNCTION STEPS AS DATA SHEET SAYS
void LCD_init(void)
{
	//INTIALIZE LCD PINS OUTPUT
	DIO_SetPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_E_PORT ,LCD_E_PIN ,DIO_PIN_OUTPUT);
	 _delay_ms(35);

//SET RS PIN BY 0 TO BE COMAND
DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);

//SET R/W PIN BY 0 TO BE WRITE
DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
  
  DIO_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,0);
  DIO_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,1);
  DIO_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,0);
  DIO_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,0);
  //ENABLE
  DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
  _delay_ms(1);
  DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
  
  LCD_sendcomand(0b00101000);	
  _delay_us(45);
	
  LCD_sendcomand(0b00001111);
  _delay_us(45);
	
   LCD_sendcomand(0b00000001);
   _delay_ms(2);
   
   LCD_sendcomand(0b00000110);
	
}
void LCD_sendchar(u8 data)
{
		//SET RS PIN BY 0 TO BE DATA
		DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
		
		//SET R/W PIN BY 0 TO BE WRITE
		DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
		
		//MSB
		DIO_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(data,4));
		DIO_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(data,5));
		DIO_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(data,6));
		DIO_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(data,7));
		
		//ENABLE
		DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
		
		//LSB
		DIO_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(data,0));
		DIO_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(data,1));
		DIO_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(data,2));
		DIO_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(data,3));
		
		//ENABLE
		DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
}
void LCD_sendcomand(u8 cmnd)
{   
	//SET RS PIN BY 0 TO BE COMAND
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	//SET R/W PIN BY 0 TO BE WRITE
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	//MSB
	DIO_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(cmnd,4));
	DIO_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(cmnd,5));
	DIO_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(cmnd,6));
	DIO_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(cmnd,7));
	
	//ENABLE
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
	//LSB
	DIO_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(cmnd,0));
	DIO_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(cmnd,1));
	DIO_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(cmnd,2));
	DIO_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(cmnd,3));
	
	//ENABLE
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
}

void LCD_clear(void)
{
	LCD_sendcomand(0b00000001);
	_delay_ms(2);
}

void LCD_writeString(u8* string)
{
	u8 counter = 0;
	if(string!=NULL)
	{
		
		while(string[counter]!='\0')
		{
			LCD_sendchar(string[counter]);
			counter++;
		}
	}
}

void LCD_shift(u8 shifttingDirection)
{
	switch(shifttingDirection)
	{
		case LCD_SHIFT_RIGHT :
		LCD_sendcomand(0b00011100);
		_delay_us(45);
		   break;
		
		case LCD_SHIFT_LEFT :
		LCD_sendcomand(0b00011000); 
		_delay_us(45);
		  break;
	}
}


void LCD_goToSpecificPosition(u8 LineNumber, u8 position)
{
	switch(LineNumber)
	{
		case LCD_LINE_ONE:
		LCD_sendcomand(0x80+position);
		_delay_us(45);
		break;
		
		case LCD_LINE_TWO:
		LCD_sendcomand(0xc0+position);
		_delay_us(45);
		break;
		
	}
	
	
}

void LCD_writeNumber(u32 number)
{
	u32 reversedNum=1;
	if(number ==0)
	{
		LCD_sendchar('0');
	}
	else
	{ //reverse number
		while(number!=0)
		{
			reversedNum=reversedNum*10 + number%10;
			number/=10;
		}
		do 
		{
			LCD_sendchar(reversedNum%10 + '0');
			reversedNum/=10;
		} while(reversedNum!=1);
	}
}