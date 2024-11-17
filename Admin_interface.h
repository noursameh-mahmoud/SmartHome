/*
 * Admin_interface.h
 *
 * Created: 06-Oct-24 5:49:16 PM
 *  Author: 
 */ 


#ifndef ADMIN_INTERFACE_H_
#define ADMIN_INTERFACE_H_

/* EEPROM LOCATIONS */

#define		ADMIN_USERNAME_LOC	0
#define		ADMIN_PASSWORD_LOC	4

#define		ADMIN_SIGNUP_LOC	501	//ADDRESS FOR CHECKING ADMIN FIRST TIME REGISTRY

#define		ADMIN_USERNAME_SIZE	4
#define		ADMIN_PASSWORD_SIZE	4


/** FUNCTIONS **/

void ADMIN_Set_UsernameAndPassword(void); //SIGN UP (FIRST TIME REGISTRY)
void ADMIN_LogIn(); 
void ADMIN_Add_User(); //THIS USER CAN LATER LOG IN (USING LCD+KPD OR REMOTELY)//store in EEPROM
void ADMIN_Remove_User();
void ADMIN_MODE_Init(void); //check if this is the first time 1-if yes call sign up / 2-if not call log in 
u8	 Compare_info(const u8* input_string, const u8* stored_string, u8 length_string);

/*STATUS*/
#define USER_FOUND		1
#define USER_NOT_FOUND	0

#endif /* ADMIN_INTERFACE_H_ */