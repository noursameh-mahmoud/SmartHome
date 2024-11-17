/*
 * TMR0_interface.h
 *
 * Created: 7/13/2024 8:47:55 PM
 *  Author: waadr
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

void TMR0_init(void);
void TMR0_start(void);
void TMR0_setCallBackOVF(void(*ptrToFun) (void));
void TMR0_setCallBackCTC(void(*ptrToFun) (void));
void TMR0_setDutyCycleUsingFastPWM(u8 dutyCycle);



#endif /* TMR0_INTERFACE_H_ */