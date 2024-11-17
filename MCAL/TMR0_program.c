/*
 * TMR0_program.c
 *
 * Created: 7/13/2024 8:48:47 PM
 *  Author: waadr
 */ 
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TMR0_interface.h"
#include "TMR0_config.h"
#include "TMR0_private.h"


static void (*private_pCallBackOVF)(void)=NULL;
static void (*private_pCallBackCTC)(void)=NULL;

void TMR0_init(void)
{
	
	#if TMR0_MODE	==	TMR0_NORMAL_MODE
	// Select Mode = Normal Mode
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	
	// Enable OVF Interrupt
	SET_BIT(TIMSK,TOIE0);
	
	// Init Timer With Preload Value
	TCNT0 = TMR0_PRELOAD_VALUE;
	
	#elif TMR0_MODE	==	TMR0_CTC_MODE
	//Select Mode = CTC Mode
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	
	// Enable OC Interrupt
	SET_BIT(TIMSK,OCIE0);
	
	//Init Timer With Compare Match Value
	OCR0 = TMR0_OUTPUT_COMPARE_VALUE;
	
	#elif TMR0_MODE	==	TMR0_FAST_PWM_MODE
	// Select Mode = Fast PWM Mode
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	
	// Select Non Inverting Mode
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	
	#endif
	
	
}
void TMR0_start(void)
{
	// Select Prescaler Value = 64
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
}
void TMR0_setCallBackOVF(void(*ptrToFun)(void))
{
	
	if(ptrToFun!=NULL)
	{
		private_pCallBackOVF = ptrToFun;
	}
}


void TMR0_setCallBackCTC(void(*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackCTC = ptrToFun;
	}
}

void TMR0_setDutyCycleUsingFastPWM(u8 dutyCycle)
{
	// under condition non inverting fast pwm
	if(dutyCycle<=100)
	{
		OCR0 = (((dutyCycle*256)/100)-1);
	}
}





void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static u16 ovfCounter = 0;
	ovfCounter++;
	
	if(TMR0_OVER_FLOW_COUNTER == ovfCounter)
	{
		// Set Preload Value
		TCNT0 = TMR0_PRELOAD_VALUE;
		
		// Clear Counter
		ovfCounter = 0;
		
		//call action
		if(private_pCallBackOVF!=NULL)
		{
			private_pCallBackOVF();
		}
	}
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static u16 ctcCounter = 0;
	ctcCounter++;
	
	if(TMR0_CTC_COUNTER == ctcCounter)
	{
		// Clear Counter
		ctcCounter = 0;
		
		//call action
		if(private_pCallBackCTC!=NULL)
		{
			private_pCallBackCTC();
		}
	}
}
