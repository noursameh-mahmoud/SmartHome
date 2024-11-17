/*
 * EEPROM_interface.h
 *
 * Created: 8/16/2024 8:33:38 PM
 *  Author: waadr
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#define EEPROM_FIXED_ADDRESS			0X50
#define EEPROM_SIZE                     2048

void EEPROM_init(void);
void EEPROM_writeByte(u16 wordAddress, u8 data);
void EEPROM_readByte(u16 wordAddress, u8* data);
void EEPROM_writePage(u16 baseAddress, u8* data, u8 dataSize);
void EEPROM_readPage(u16 baseAddress, u8* data, u8 dataSize);



#endif /* EEPROM_INTERFACE_H_ */