/*
 * UART_interface.h
 *
 * Created: 8/2/2024 5:55:58 PM
 *  Author: waadr
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_init(void);
void UART_TxChar(u8 TxData);
void UART_RxChar(u8* RxData);
void UART_sendString(u8* TxString);
void UART_Rx_String( u8* ptr_Rx_string);
void UART_Tx_NewLine();


#endif /* UART_INTERFACE_H_ */