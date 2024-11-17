/*
 * GI_program.c
 *
 * Created: 3/11/2024 1:25:35 PM
 *  Author: waadr
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "GI_interface.h"
#include "GI_private.h"






void GI_enable(void)
{
	SET_BIT(SREG,I);
}
void GI_disable(void)
{
	CLR_BIT(SREG,I);
}