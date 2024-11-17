/*
 * BUZ_program.h
 *
 * Created: 2/7/2024 1:41:50 PM
 *  Author: waadr
 */ 


#ifndef BUZ_INTERFACE_H_
#define BUZ_INTERFACE_H_

void BUZ_init   (u8 BUZPort, u8 BUZPin);
void BUZ_on     (u8 BUZPort, u8 BUZPin);
void BUZ_off    (u8 BUZPort, u8 BUZPin);
void BUZ_toggle (u8 BUZPort, u8 BUZPin);




#endif /* BUZ_INTERFACE_H_ */