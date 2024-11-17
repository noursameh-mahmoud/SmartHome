/*
 * EXTI_interface.h
 *
 * Created: 3/11/2024 10:32:58 AM
 *  Author: waadr
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/* Macros For Interrupt Source */
#define EXTI_INT0                        0
#define EXTI_INT1                        1
#define EXTI_INT2                        2

/* Macros For Interrupt Trigger Edge */
#define EXTI_RISING_EDGE                 0
#define EXTI_FALLING_EDGE                1
#define EXTI_LOW_LEVEL                   2
#define EXTI_ANY_LOGICAL_CHANGE          3


void EXTI_enable(u8 interruptSource,u8 interruptTriggerEdge);
void EXTI_disable(u8 interruptSource);
void EXTI_setCallBackINT0(void (*ptrToFun)(void));
void EXTI_setCallBackINT1(void (*ptrToFun)(void));
void EXTI_setCallBackINT2(void (*ptrToFun)(void));



#endif /* EXTI_INTERFACE_H_ */