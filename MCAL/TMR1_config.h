/*
 * TMR1_config.h
 *
 * Created: 7/14/2024 10:00:26 PM
 *  Author: waadr
 */ 


#ifndef TMR1_CONFIG_H_
#define TMR1_CONFIG_H_


/* Options FOR TMR1 Mode:
1- TMR1_NORMAL_MODE_0
2- TMR1_CTC_MODE_4
3- TMR1_FAST_PWM_MODE_14
*/
#define TMR1_MODE                           TMR1_FAST_PWM_MODE_14
#define TMR1_PRELOAD_VALUE                  4816
#define TMR1_OVER_FLOW_COUNTER              20

#define TMR1_OUTPUT_COMPARE_VALUE_A			62499
#define TMR1_CTC_COUNTER			        40




#endif /* TMR1_CONFIG_H_ */