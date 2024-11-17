/*
 * Admin_interface.c
 *
 * Created: 06-Oct-24 5:50:03 PM
 *  Author: w
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "KPD_interface.h"

#include "User_interface.h"
#include "HOME_interface.h"


#include "Admin_interface.h"


#define F_CPU 16000000UL
#include <util/delay.h>

u8 Users_count=0;

void ADMIN_MODE_Init(void)
{
	 u8* Selected_Option=0 ;
	 
			UART_sendString("ADMIN MODE.");
			_delay_ms(1000);
			
			UART_Tx_NewLine();
			
			UART_sendString("1-ADMIN SIGN UP 2-ADMIN LOG IN: ");
			
			UART_RxChar(&Selected_Option);
			
			UART_Tx_NewLine();
			
		if (Selected_Option=='1')
		{
			ADMIN_Set_UsernameAndPassword();
		}
		else if (Selected_Option=='2')
		{
			ADMIN_LogIn();
		}
		else
		{
			UART_Tx_NewLine();
			UART_sendString("Choose an option! ");
			UART_Tx_NewLine();
			
			_delay_ms(1000);
			ADMIN_MODE_Init();
		}
}

void ADMIN_Set_UsernameAndPassword()
{
	static u8 Sign_up_trial_check= 0 ;
	
	u8 Admin_Username[ADMIN_USERNAME_SIZE]={0};
	u8 Admin_Password[ADMIN_PASSWORD_SIZE]={0};
	
	u8 *ptr_stringRX = Admin_Username ;
	
	u8 index=0 ;
	
	EEPROM_readByte(ADMIN_SIGNUP_LOC,&Sign_up_trial_check); //CHECK THAT THE USERNAME LOCATION IS EMPTY
	
	
	if (Sign_up_trial_check==0)
	{
		EEPROM_writeByte(ADMIN_SIGNUP_LOC,1); //to indicate that the admin is registered 
		
		UART_sendString("Set admin Username: ");
		UART_Rx_String(Admin_Username);
		
		UART_Tx_NewLine();
		
		EEPROM_writePage(ADMIN_USERNAME_LOC,Admin_Username,ADMIN_USERNAME_SIZE);
		
		UART_sendString("Set admin Password: ");
		UART_Rx_String(Admin_Password);
		
		UART_Tx_NewLine();
		
		EEPROM_writePage(ADMIN_PASSWORD_LOC,Admin_Password,ADMIN_PASSWORD_SIZE);
		
		UART_sendString("ADMIN REGISTERED! ");
		UART_Tx_NewLine();
		
		ADMIN_LogIn();
	}
	else
	{
		UART_sendString("ADMIN SIGNED-UP!");
		UART_Tx_NewLine();
		ADMIN_LogIn();
	}
}

void ADMIN_LogIn()
{
	/*
		1- enter username
		2- check if username valid if not re-enter a valid one
		3- if username valid, enter password if not valid, give 3 trials before fire alarm 
		4- if username&&password are valid, "admin logged in"
		5- call admin home control
	*/
	u8 ADMIN_Username[ADMIN_USERNAME_SIZE]={0};
	u8 ADMIN_Password[ADMIN_PASSWORD_SIZE]={0};
	
	u8 ADMIN_STORED_Username[ADMIN_USERNAME_SIZE];
	u8 ADMIN_STORED_Password[ADMIN_PASSWORD_SIZE];
	
	EEPROM_readPage(ADMIN_USERNAME_LOC,ADMIN_STORED_Username,ADMIN_USERNAME_SIZE);
	EEPROM_readPage(ADMIN_PASSWORD_LOC,ADMIN_STORED_Password,ADMIN_PASSWORD_SIZE);
	
	u8 username_compare_result ;
	u8 password_compare_result ;
	
	u8 Trial_count=0 ;
	
	while(Trial_count<3)
	{
		UART_sendString("Enter ADMIN username: ");
		UART_Rx_String(ADMIN_Username);
		UART_Tx_NewLine();
		username_compare_result=Compare_info(ADMIN_Username,ADMIN_STORED_Username,ADMIN_USERNAME_SIZE);
		if (username_compare_result)
		{
			UART_sendString("Enter ADMIN password: ");
			UART_Rx_String(ADMIN_Password);
			UART_Tx_NewLine();
			password_compare_result=Compare_info(ADMIN_Password,ADMIN_STORED_Password,ADMIN_PASSWORD_SIZE);
			if (password_compare_result)
			{
				UART_sendString("ADMIN LOGGED IN!");
				UART_Tx_NewLine();
				Trial_count=0 ;
				
				ADMIN_HOME_Cntrl();
				return;
			}
			else Trial_count++;
		}
		else
		{
			UART_sendString("ENTER A VALID USERNAME! ");
			UART_Tx_NewLine();
			Trial_count++;
		}
	}
	if (Trial_count==3)
	{
		UART_sendString(" Too many failed attempts! Alarm activated. ");
		UART_Tx_NewLine();
		FIRE_ALARM();//stopping condition: physical reset button.
	}
	
}

u8	 Compare_info(const u8* input_string, const u8* stored_string, u8 length_string)
{
	u8 iteration ;
	
	for ( iteration=0 ; iteration<length_string ; iteration++)
	 {
		if (input_string[iteration] != stored_string[iteration]) 
		{
			return 0; //STRINGS ARE NOT EQUAL
		}

		if (input_string[iteration]=='\0' || stored_string[iteration]=='\0') // CHECK IF THE END OF STRING IS REACHED
		{
			break; //REACHED THE END OF A STRING OR BOTH STRINGS
		}
	}
	return 1; //STRINGS ARE EQUAL
}

void ADMIN_Add_User()
{
	u8 USER_username[USER_USERNAME_SIZE] = {0};
	u8 USER_password[USER_PASSWORD_SIZE] = {0};
	
	// Read the current number of users from EEPROM
	EEPROM_readByte(ADDRESS_NUM_OF_USERS, &Users_count);
	
	if (Users_count > MAX_NUM_OF_USERS || Users_count == 0xFF) // Uninitialized EEPROM data
	{
		EEPROM_writeByte(ADDRESS_NUM_OF_USERS, 0); // Initialize to zero users
		_delay_ms(5);
	}


	// Check if the user limit is reached
	if (Users_count >= MAX_NUM_OF_USERS)
	{
		UART_sendString("USER LIMIT REACHED!");
		UART_Tx_NewLine();
		UART_sendString("REMOVE USERS TO ADD MORE.");
		UART_Tx_NewLine();
		return;
	}

	// Prompt the admin for username and password
	UART_sendString("Set User's Username: ");
	UART_Rx_String(USER_username);
	UART_Tx_NewLine();

	UART_sendString("Set User's Password: ");
	UART_Rx_String(USER_password);
	UART_Tx_NewLine();

	// Increment the number of users before calculating addresses
	Users_count++;
	u16 Next_USER_username_address = USER_1_USERNAME_LOC + ((Users_count - 1) * USER_USERNAME_SIZE);
	u16 Next_USER_password_address = USER_1_PASSWORD_LOC + ((Users_count - 1) * USER_PASSWORD_SIZE);

	// Store the username and password in EEPROM
	EEPROM_writePage(Next_USER_username_address, USER_username, USER_USERNAME_SIZE);
	_delay_ms(5);
	EEPROM_writePage(Next_USER_password_address, USER_password, USER_PASSWORD_SIZE);
	_delay_ms(5);

	// Update the number of users in EEPROM
	EEPROM_writeByte(ADDRESS_NUM_OF_USERS, Users_count);
	_delay_ms(5);

	// Confirmation message
	UART_sendString("USER ADDED SUCCESSFULLY.");
	UART_Tx_NewLine();
	
	ADMIN_HOME_Cntrl();
	return;
}

/*void ADMIN_Add_User()
{
	u8 USER_username[USER_USERNAME_SIZE]={0};
	u8 USER_password[USER_PASSWORD_SIZE]={0};
			
	u16 Next_USER_username_address =USER_1_USERNAME_LOC + (Users_count*(USER_USERNAME_SIZE));
	u16 Next_USER_password_address =USER_1_PASSWORD_LOC + (Users_count*(USER_PASSWORD_SIZE));
	
	EEPROM_readByte(ADDRESS_NUM_OF_USERS,&Users_count); //CHECK THAT THE NUMBER OF USERS IS LESS THAN THE MAXM ALLOWED
	
		UART_sendString("Set User's Username: ");
		UART_Rx_String(USER_username);
		
		UART_Tx_NewLine();
		
		UART_sendString("Set User's Password: ");
		UART_Rx_String(USER_password);
		
		UART_Tx_NewLine();
		
		if (Users_count >= MAX_NUM_OF_USERS)
		{
			UART_sendString("USER LIMIT REACHED!");
			UART_Tx_NewLine();
			UART_sendString("REMOVE USERS TO ADD MORE.");
			UART_Tx_NewLine();
			
			return;
		}
		
		Users_count++ ;

		EEPROM_writePage(Next_USER_username_address,USER_username,USER_USERNAME_SIZE);
		_delay_ms(5);
		EEPROM_writePage(Next_USER_password_address,USER_password,USER_PASSWORD_SIZE);
		_delay_ms(5);
		
		EEPROM_writeByte(ADDRESS_NUM_OF_USERS,Users_count);
		_delay_ms(5);
		UART_sendString("USER ADDED SUCCESSFULY.");
		UART_Tx_NewLine();
		ADMIN_HOME_Cntrl();

		return;
		
}*/

void ADMIN_Remove_User()
{
	u8 USER_username[USER_USERNAME_SIZE];
	u8 USER_password[USER_PASSWORD_SIZE];
	
	
	u8 Username_Local_compare[USER_USERNAME_SIZE];
	
	
		UART_sendString("Enter username: ");
		UART_Rx_String(USER_username);
		
		UART_Tx_NewLine();
		
		EEPROM_readByte(ADDRESS_NUM_OF_USERS,&Users_count);
		
		if (Users_count==0)
		{
			UART_sendString("NO USERS ADDED.");
			UART_Tx_NewLine();
			return;
		}
		
		u8	user_location=USER_1_USERNAME_LOC ; //start comparing from the first location
		u8 status=0;
		
		/* iterate on each user and compare, if they match shift each user to its prior location and count-- */
		for(u8 iteration=0;iteration<Users_count;iteration++)
		{
			EEPROM_readPage(user_location,Username_Local_compare,USER_USERNAME_SIZE);
			u8 compare_output= Compare_info(USER_username,Username_Local_compare,USER_USERNAME_SIZE);
			
			if (compare_output==USER_FOUND)
			{
				status=USER_FOUND;
				u16 next_user_location ;
				for (u8 location=iteration+1;location<Users_count;location++)
				{
					next_user_location=user_location+location*(USER_USERNAME_SIZE);
					
					u8 NextUser_username[USER_USERNAME_SIZE];
					u8 NextUser_password[USER_PASSWORD_SIZE];
					
					//copy the info of the user after the removed one
					EEPROM_readPage(next_user_location,NextUser_username, USER_USERNAME_SIZE);
					_delay_ms(5);
					EEPROM_readPage(next_user_location+24 ,NextUser_password, USER_PASSWORD_SIZE);
					_delay_ms(5);
					
					//paste it in the location just before it,, replace the removed one
					EEPROM_writePage(user_location, NextUser_username, USER_USERNAME_SIZE);
					_delay_ms(5);
					EEPROM_writePage(user_location+24, NextUser_password, USER_PASSWORD_SIZE);
					_delay_ms(5);
					
					user_location= next_user_location ; //Repeat the process for the next user
				}
				Users_count-- ; // one user removed
				EEPROM_writeByte(ADDRESS_NUM_OF_USERS,Users_count);//update user count
				_delay_ms(5);
				UART_sendString("USER REMOVED SUCCESSFULLY!");
				UART_Tx_NewLine();
				return; //exit the for loop
			}
			
			user_location = user_location+USER_USERNAME_SIZE;//if output of compare does not equal 1,, move to the next location
		
		 }
	if(status==USER_NOT_FOUND)
		{
			UART_sendString("USER DOES NOT EXIST!");
			UART_Tx_NewLine();
			return;
		}
}
