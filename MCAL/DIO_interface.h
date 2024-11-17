/*
 * DIO_interface.h
 *
 * Created: 12/11/2023 7:29:00 PM
 *  Author: waadr
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
#define DIO_PORTA       0
#define DIO_PORTB       1
#define DIO_PORTC       2
#define DIO_PORTD       3

#define DIO_PIN0       0
#define DIO_PIN1       1
#define DIO_PIN2       2
#define DIO_PIN3       3
#define DIO_PIN4       4
#define DIO_PIN5       5
#define DIO_PIN6       6
#define DIO_PIN7       7

#define  DIO_PIN_INPUT   0
#define  DIO_PIN_OUTPUT  1


#define  DIO_PIN_LOW     0
#define  DIO_PIN_HIGH    1



void DIO_SetPinDirection (u8 PortID, u8 PinID, u8 PinDirection);
void DIO_SetPinValue     (u8 PortID, u8 PinID, u8 PinValue);
void DIO_TooglePinValue  (u8 PortID, u8 PinID);
void DIO_getPinValue(u8 PortId, u8 PinId, u8* PinValue);
//u8  DIO_GetPinValue       (u8 PortID, u8 PinID);
void DIO_ActivePinPullUpResistance  (u8 PortID, u8 PinID);






#endif /* DIO_INTERFACE_H_ */