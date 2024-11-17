/*
 * LED_interface.h
 *
 * Created: 12/18/2023 4:15:43 PM
 *  Author: waadr
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

void LED_init (u8 LedPort, u8 LedPin);
void LED_on (u8 LedPort, u8 LedPin);
void LED_off (u8 LedPort, u8 LedPin);
void LED_toggle (u8 LedPort, u8 LedPin);



#endif /* LED_INTERFACE_H_ */