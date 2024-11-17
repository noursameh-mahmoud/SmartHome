/*
 * User_interface.c
 *
 * Created: 06-Oct-24 6:31:30 PM
 *  Author: 
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "KPD_interface.h"
#include "HOME_interface.h"

#include "User_interface.h"
#include "Admin_interface.h"


#define F_CPU 16000000UL
#include <util/delay.h>

u8 USER_LogIn()
{
	u8 USER_STORED_Username[USER_USERNAME_SIZE] = {0};
	u8 USER_STORED_Password[USER_PASSWORD_SIZE] = {0};
	
	u16 username_address = 0;
	u16 password_address = 0;
	
	u8 username_compare_result = 0;
	u8 password_compare_result = 0;
	
	u8 trials = 3;  // Maximum login attempts
	u8 count = '3'; // ASCII value for trial display
	u8 Users_count = 0;
	
	// Read the number of registered users
	EEPROM_readByte(ADDRESS_NUM_OF_USERS, &Users_count);
	_delay_ms(5);
	
	if (Users_count == 0)
	{
		UART_sendString("No users registered!");
		return 0; // Login failed
	}
	
	// Prompt user to choose input method
	u8 input_mode = 0;
	UART_sendString("Choose mode: ");
	UART_Tx_NewLine();
	UART_sendString("1-Bluetooth 2-Keypad ");
	UART_Tx_NewLine();
	UART_RxChar(&input_mode);
	UART_Tx_NewLine();
	
	u8 USER_Username[USER_USERNAME_SIZE] = {0};
	u8 USER_Password[USER_PASSWORD_SIZE] = {0};
	
	// Attempt login
	while (trials > 0)
	{
		// Clear buffers for each trial
		memset(USER_Username, 0, USER_USERNAME_SIZE);
		memset(USER_Password, 0, USER_PASSWORD_SIZE);
		
		u8 key = 0;
		u8 i = 0;

		// Input username
		if (input_mode == '1') // UART input
		{
			UART_sendString("Enter USERNAME: ");
			UART_Rx_String(USER_Username);
			UART_Tx_NewLine();
		}
		else // Keypad input
		{
			LCD_clear();
			LCD_writeString("Enter USERNAME:");
			LCD_goToSpecificPosition(2, 0);
			
			i = 0;
			while (i < USER_USERNAME_SIZE)
			{
				key = KPD_getValue();
				if (key != 0xff)
				{
					if (key == '#') break; // '#' as "Enter" key
					USER_Username[i] = key;
					LCD_sendchar(key);
					i++;
					_delay_ms(200); // Debounce delay
				}
			}
			USER_Username[i] = '\0'; // Null-terminate
		}
		
		// Input password
		if (input_mode == '1') // UART input
		{
			UART_sendString("Enter PASSWORD: ");
			UART_Rx_String(USER_Password);
			UART_Tx_NewLine();
		}
		else // Keypad input
		{
			LCD_clear();
			LCD_writeString("Enter PASSWORD:");
			LCD_goToSpecificPosition(2, 0);
			
			i = 0;
			while (i < USER_PASSWORD_SIZE)
			{
				key = KPD_getValue();
				if (key != 0xff)
				{
					if (key == '#') break; // '#' as "Enter" key
					USER_Password[i] = key;
					LCD_sendchar('*'); // Mask password
					i++;
					_delay_ms(200); // Debounce delay
				}
			}
			USER_Password[i] = '\0'; // Null-terminate
		}

		// Verify credentials
		for (u8 user_index = 0; user_index < Users_count; user_index++)
		{
			username_address = USER_1_USERNAME_LOC + (user_index * USER_USERNAME_SIZE);
			password_address = USER_1_PASSWORD_LOC + (user_index * USER_PASSWORD_SIZE);

			EEPROM_readPage(username_address, USER_STORED_Username, USER_USERNAME_SIZE);
			_delay_ms(5);

			EEPROM_readPage(password_address, USER_STORED_Password, USER_PASSWORD_SIZE);
			_delay_ms(5);

			username_compare_result = Compare_info(USER_Username, USER_STORED_Username, USER_USERNAME_SIZE);
			password_compare_result = Compare_info(USER_Password, USER_STORED_Password, USER_PASSWORD_SIZE);

			if (username_compare_result && password_compare_result)
			{
				return 1; // Successful login
			}
		}

		// Invalid input, decrement trials
		trials--;
		count--; // ASCII decrement for display
		UART_sendString("Invalid input. ");
		UART_TxChar(count);
		UART_sendString(" trials left.");
		UART_Tx_NewLine();

		LCD_clear();
		LCD_writeString("Invalid input");
		LCD_goToSpecificPosition(2, 0);
		LCD_sendchar(count);
		LCD_writeString(" trials left");
	}

	// All trials exhausted

	return 0;
}


void USER_MODE_Init()
{
	
	if (USER_LogIn()==1)
	{
		
		UART_sendString("User logged in successfully!");
		UART_Tx_NewLine();
		
		LCD_clear();
		LCD_writeString("User logged in!");
		
		UART_sendString("1-Bluetooth 2-Keypad ");
		UART_Tx_NewLine();
		
		u8 input_Uart_mode=0 ;
		UART_RxChar(&input_Uart_mode);
		UART_Tx_NewLine();
		if ( input_Uart_mode == '1' )
		{
			USER_HOME_Cntrl_remotely();
		}
		else
		{
			USER_HOME_Cntrl_lcd();
		}
		
		LCD_writeString("1-Bluetooth 2-Keypad ");
		u8 input_LCD_mode=0xFF ;
		while (1)
		{
			input_LCD_mode=KPD_getValue();
			if (input_LCD_mode!=0xFF)
			{
				break;
			}
		}
		LCD_clear();
		if ( input_LCD_mode == '1' )
		{
			USER_HOME_Cntrl_remotely();
		}
		else
		{
			USER_HOME_Cntrl_lcd();
		}
		
		
	}
	
	else {
		UART_sendString("Access denied.");
		UART_Tx_NewLine();
		UART_sendString("Alarm triggered due to too many failed attempts.");
		UART_Tx_NewLine();
		
		LCD_writeString("Access denied.");
		_delay_ms(2000);
		LCD_sendcomand(0x01);
		LCD_writeString("Too many failed");
		LCD_goToSpecificPosition(2,0);
		LCD_writeString(" attempts!");
		_delay_ms(1000);
		LCD_clear();
		LCD_writeString("Alarm triggered.");
		_delay_ms(2000);
		LCD_clear();
		FIRE_ALARM();
	}

}