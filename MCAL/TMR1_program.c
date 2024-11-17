/*
 * TMR1_program.c
 *
 * Created: 7/14/2024 10:02:23 PM
 *  Author: waadr
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TMR1_interface.h"
#include "TMR1_config.h"
#include "TMR1_private.h"


static void (*private_pCallBackOVF)(void)=NULL;
static void (*private_pCallBackCTC)(void)=NULL;

void TMR1_init(void)
{
	#if TMR1_MODE	==	TMR1_NORMAL_MODE_0
	// Select Mode = Normal Mode 0
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	// Init Timer With Preload Value
	TCNT1_u16 = TMR1_PRELOAD_VALUE;
	
	// Enable OVF Interrupt
	SET_BIT(TIMSK,TOIE1);
	
	#elif TMR1_MODE	==	TMR1_CTC_MODE_4
	// Select Mode = CTC Mode 4
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	// Enable CTC Interrupt
	SET_BIT(TIMSK,OCIE1A);
	
	//Init Timer With Compare Match Value
	OCR1A_u16 = TMR1_OUTPUT_COMPARE_VALUE_A;
	
	#elif TMR1_MODE	==	TMR1_FAST_PWM_MODE_14
	// Select Mode = FAST PWM Mode 14
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	// Select Non Inverting Mode
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	
	#endif
}

void TMR1_start(void)
{
	// Select Prescaler Value = 64
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
}
void TMR1_stop(void)
{
	// Select Prescaler Value = 64
	CLR_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
}


void TMR1_setCallBackOVF(void(*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackOVF = ptrToFun;
	}
}
void TMR1_setCallBackCTC(void(*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackCTC = ptrToFun;
	}
}
void TMR1_setFastPWM_usingMode14(f32 dutyCycle, u16 frequency_hz)
{
	if(dutyCycle <= 100)
	{
		// under condition non inverting fast pwm & tick time 4 MS
		
		ICR1_u16  = ((1000000UL/frequency_hz)/4)-1;
		
		OCR1A_u16 = ((dutyCycle*(ICR1_u16+1))/100.0)-1;
	}
}


void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	static u8 ovfCounter = 0;
	ovfCounter++;
	
	if(TMR1_OVER_FLOW_COUNTER == ovfCounter)
	{
		// Set Preload Value
		TCNT1_u16 = TMR1_PRELOAD_VALUE;
		
		// Clear Counter
		ovfCounter = 0;
		
		//call action
		if(private_pCallBackOVF!=NULL)
		{
			private_pCallBackOVF();
		}
	}
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	static u8 ctcCounter = 0;
	ctcCounter++;
	
	if(TMR1_CTC_COUNTER == ctcCounter)
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