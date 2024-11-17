/*
 * UART_program.c
 *
 * Created: 8/2/2024 5:56:50 PM
 *  Author: waadr
 */ 
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "UART_interface.h"
#include "UART_private.h"

void UART_init(void)
{
	// Set Buad Rate = 9600
	CLR_BIT(UCSRA,U2X);
	UBRRL = 103;
	
	/* writing the UCSRC
	select UART MODE = Asynchronous
	configure no parity
	configure stop bits = 1
	configure data bits = 8
	configure no polarity */
	CLR_BIT(UCSRB,UCSZ2);
	UCSRC = 0b10000110;
	
	//Enable Tx
	SET_BIT(UCSRB,TXEN);
	
	//Enable Rx
	SET_BIT(UCSRB,RXEN);
	
}
void UART_TxChar(u8 TxData)
{
	UDR = TxData;
	
	// Busy Wait on Data Register empty flag
	while(0 == GET_BIT(UCSRA,UDRE));

}
void UART_RxChar(u8* RxData)
{
if(RxData!=NULL)
{
	// Busy Wait on Receive Complete flag
	while(0 == GET_BIT(UCSRA,RXC));
	
	*RxData = UDR;
}
}
void UART_sendString(u8* TxString)
{
	if(TxString!=NULL)
	{
		u8 counter = 0;
		while(TxString[counter]!='\0')
		{
			UART_TxChar(TxString[counter]);
			counter++;
		}
	}
}
void UART_Rx_String( u8* ptr_Rx_string)
{
	u8 count = 0;
	while(1)
	{
		UART_RxChar(&ptr_Rx_string[count]);
		if(ptr_Rx_string[count] == '#') /*Enter # after each string to indicate its over*/
		{
			break;
		}
		else
		{
			count++;
		}
	}
	ptr_Rx_string[count]= '\0';
}
void UART_Tx_NewLine()
{
	UART_TxChar(0x0d);//new line
	UART_TxChar(0x0a);
}