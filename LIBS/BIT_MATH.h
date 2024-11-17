/*
Author: waad rabie
Date: 29/10/2023
SWC: BIT_MATH.h
Version: 1.0
*/
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT_NUM)    REG|=(1<<BIT_NUM)
#define CLR_BIT(REG,BIT_NUM)    REG&=(~(1<<BIT_NUM))
#define TOG_BIT(REG,BIT_NUM)    REG^=(1<<BIT_NUM)
#define GET_BIT(REG,BIT_NUM)    ((REG>>BIT_NUM)&1)

#endif 