/*
 * KPD_interface.h
 *
 * Created: 3/7/2024 8:45:22 PM
 *  Author: waadr
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define KPD_NOT_PRESSED    0xFF

void KPD_init(void);
u8 KPD_getValue(void);


#endif /* KPD_INTERFACE_H_ */