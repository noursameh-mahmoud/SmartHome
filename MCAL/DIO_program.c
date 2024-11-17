/*
 * DIO_program.c
 *
 * Created: 12/11/2023 7:28:27 PM
 *  Author: waadr
 */ 
#include "DIO_private.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"


void DIO_SetPinDirection (u8 PortID, u8 PinID, u8 PinDirection)
{
	if((PortID<=3)&&(PinID<=7)&&((PinDirection== DIO_PIN_OUTPUT)||(PinDirection== DIO_PIN_INPUT)))
	{
		switch(PortID)
		{
			
		case DIO_PORTA: 
		if(DIO_PIN_OUTPUT==PinDirection) //output
		{
			SET_BIT(DDRA,PinID);
		}
		else
		{
			CLR_BIT(DDRA,PinID);
		}
		break;
		
		case DIO_PORTB: 
		if(DIO_PIN_OUTPUT==PinDirection)
		{
			SET_BIT(DDRB,PinID);
		}
		else
		{
			CLR_BIT(DDRB,PinID);
		}
		break;
		case DIO_PORTC: 
		if(DIO_PIN_OUTPUT==PinDirection) 
		{
			SET_BIT(DDRC,PinID);
		}
		else
		{
			CLR_BIT(DDRC,PinID);
		}
		break;
		case DIO_PORTD: 
		if(DIO_PIN_OUTPUT==PinDirection) //output
		{
			SET_BIT(DDRD,PinID);
		}
		else
		{
			CLR_BIT(DDRD,PinID);
		}
		break;

	}
	}
	else
	{
		
	}
}

void DIO_SetPinValue     (u8 PortID, u8 PinID, u8 PinValue)
{
	
	if((PortID<=3)&&(PinID<=7)&&((PinValue== DIO_PIN_LOW )||(PinValue== DIO_PIN_HIGH)))
	{
		
		
			if(PinValue== DIO_PIN_HIGH)
			{
				switch(PortID)
				{
			case DIO_PORTA: SET_BIT(PORTA,PinID); break;
			case DIO_PORTB: SET_BIT(PORTB,PinID); break;
			case DIO_PORTC: SET_BIT(PORTC,PinID); break;
			case DIO_PORTD: SET_BIT(PORTD,PinID); break;
			   }
			}
			else
			{
				switch(PortID)
				{
				case DIO_PORTA: CLR_BIT(PORTA,PinID); break;
				case DIO_PORTB: CLR_BIT(PORTB,PinID); break;
				case DIO_PORTC: CLR_BIT(PORTC,PinID); break;
				case DIO_PORTD: CLR_BIT(PORTD,PinID); break;
				}
			}
		}
   
   else
   {
	   
   }
}

void DIO_TooglePinValue(u8 PortID, u8 PinID)
{
	if((PortID<=3)&&(PinID<=7))
	{
		switch(PortID)
		{
			case DIO_PORTA: TOG_BIT(PORTA,PinID); break;
			case DIO_PORTB: TOG_BIT(PORTB,PinID); break;
			case DIO_PORTC: TOG_BIT(PORTC,PinID); break;
			case DIO_PORTD: TOG_BIT(PORTD,PinID); break;
		}
	}
	else
	{
		
	}
}
/*u8 DIO_GetPinValue(u8 PortID, u8 PinID)
{
	if((PortID<=3)&&(PinID<=7))
	{
		switch(PortID)
		{
			case DIO_PORTA: return(GET_BIT(PINA,PinID)); break;
			case DIO_PORTB: return(GET_BIT(PINB,PinID)); break;
			case DIO_PORTC: return(GET_BIT(PINC,PinID)); break;
			case DIO_PORTD: return(GET_BIT(PIND,PinID)); break;
		}
	}
	else
	{
		
	}
	return 0;
}*/
void DIO_getPinValue(u8 PortId, u8 PinId, u8* PinValue)
{
	if((PortId<=3)&&(PinId<=7)&&(PinValue!=NULL))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			*PinValue = GET_BIT(PINA,PinId);
			break;
			
			case DIO_PORTB:
			*PinValue = GET_BIT(PINB,PinId);
			break;
			
			case DIO_PORTC:
			*PinValue = GET_BIT(PINC,PinId);
			break;
			
			case DIO_PORTD:
			*PinValue = GET_BIT(PIND,PinId);
			break;
		}
	}
	else
	{
		// Do Nothing
	}
}

void DIO_ActivePinPullUpResistance  (u8 PortID, u8 PinID)
{
	if((PortID<=3)&&(PinID<=7))
	{
	
	switch(PortID)
	{
		case DIO_PORTA: SET_BIT(PORTA,PinID); break;
		case DIO_PORTB: SET_BIT(PORTB,PinID); break;
		case DIO_PORTC: SET_BIT(PORTC,PinID); break;
		case DIO_PORTD: SET_BIT(PORTD,PinID); break;
	}
}
else
{
}
}


