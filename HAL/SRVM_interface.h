/*
 * SRVM_interface.h
 *
 * Created: 7/30/2024 1:47:35 AM
 *  Author: waadr
 */ 


#ifndef SRVM_INTERFACE_H_
#define SRVM_INTERFACE_H_


#define SRVM_ANGLE_N90			1
#define SRVM_ANGLE_0			2
#define SRVM_ANGLE_90			3


void SRVM_init(void);
void SRVM_on  (u8 angle);
void SRVM_off (void);


#endif /* SRVM_INTERFACE_H_ */