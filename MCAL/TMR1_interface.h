/*
 * TMR1_interface.h
 *
 * Created: 7/14/2024 10:00:57 PM
 *  Author: waadr
 */ 


#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_


void TMR1_init(void);
void TMR1_start(void);
void TMR1_stop(void);
void TMR1_setCallBackOVF(void(*ptrToFun)(void));
void TMR1_setCallBackCTC(void(*ptrToFun)(void));
void TMR1_setFastPWM_usingMode14(f32 dutyCycle, u16 frequency_hz);



#endif /* TMR1_INTERFACE_H_ */