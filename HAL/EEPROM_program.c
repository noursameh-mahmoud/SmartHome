/*
 * EEPROM_program.c
 *
 * Created: 8/16/2024 8:33:04 PM
 *  Author: waadr
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TWI_interface.h"
#include "TWI_private.h"

/* HAL */
#include "EEPROM_interface.h"

void EEPROM_init(void)
{
	TWI_initMaster();
}
void EEPROM_writeByte(u16 wordAddress, u8 data)
{
	u8 deviceAddress = (wordAddress>>8)|EEPROM_FIXED_ADDRESS;
	
	// Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddWithWrite(deviceAddress);
	
	// Send word address
	TWI_sendMasterDataByte((u8)wordAddress);
	
	// Send byte data
	TWI_sendMasterDataByte(data);
	
	// Send stop condition
	TWI_sendStopCondition();
	
	// Self-timed Write Cycle delay
	_delay_ms(5);
}
void EEPROM_readByte(u16 wordAddress, u8* data)
{
	 if(data!=NULL)
	 {
		 u8 deviceAddress = (wordAddress>>8)|EEPROM_FIXED_ADDRESS;
		 
		 // Send start condition
		 TWI_sendStartCondition();
		 
		 // Send slave address with write operation
		 TWI_sendSlaveAddWithWrite(deviceAddress);
		 
		 // Send word address
		 TWI_sendMasterDataByte((u8)wordAddress);
		 
		 // Send repeated start condition in order to switch i2c operation
		 TWI_sendRepStartCondition();
		 
		 // Send slave address with read operation
		 TWI_sendSlaveAddWithRead(deviceAddress);
		 
		 // Read byte data
		 TWI_receiveMasterDataByteWithNack(data);
		 
		 // Send stop condition
		 TWI_sendStopCondition();
		 
		 // Self-timed Write Cycle delay
		 _delay_ms(5);
	 }
}

void EEPROM_writePage(u16 baseAddress, u8* data, u8 dataSize)
{
	if((data!=NULL)&&(dataSize<=16))
	{
		u8 deviceAddress = (baseAddress>>8)|EEPROM_FIXED_ADDRESS;
		
		// Send start condition
		TWI_sendStartCondition();
		
		// Send slave address with write operation
		TWI_sendSlaveAddWithWrite(deviceAddress);
		
		// Send word address
		TWI_sendMasterDataByte((u8)baseAddress);
		
		u8 counter;
		for(counter=0;counter<dataSize;counter++)
		{
			// Send byte data
			TWI_sendMasterDataByte(data[counter]);
		}
		
		// Send stop condition
		TWI_sendStopCondition();
		
		// Self-timed Write Cycle delay
		_delay_ms(5);
	}
}


void EEPROM_readPage(u16 baseAddress, u8* data, u8 dataSize)
{
	if((data!=NULL)&&(dataSize<=16))
	{
		u8 deviceAddress = (baseAddress>>8)|EEPROM_FIXED_ADDRESS;
		
		// Send start condition
		TWI_sendStartCondition();
		
		// Send slave address with write operation
		TWI_sendSlaveAddWithWrite(deviceAddress);
		
		// Send word address
		TWI_sendMasterDataByte((u8)baseAddress);
		
		// Send repeated start condition in order to switch i2c operation
		TWI_sendRepStartCondition();
		
		// Send slave address with read operation
		TWI_sendSlaveAddWithRead(deviceAddress);
		
		u8 counter;
		for(counter=0;counter<dataSize-1;counter++)
		{
			// Read byte data
			TWI_receiveMasterDataByteWithAck(&data[counter]);
		}
		
		// Read last byte data
		TWI_receiveMasterDataByteWithNack(&data[counter]);
		
		// Send stop condition
		TWI_sendStopCondition();
		
		// Self-timed Write Cycle delay
		_delay_ms(5);
	}
}