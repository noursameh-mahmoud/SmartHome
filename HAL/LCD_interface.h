/*
 * LCD_interface.h
 *
 * Created: 3/5/2024 6:54:41 PM
 *  Author: waadr
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define  LCD_SHIFT_LEFT   1
#define  LCD_SHIFT_RIGHT  2

#define  LCD_LINE_ONE     1
#define  LCD_LINE_TWO     2

void LCD_init(void);
void LCD_sendchar(u8 data);
void LCD_sendcomand(u8 cmnd);
void LCD_clear(void);
void LCD_writeString(u8* string);
void LCD_shift(u8 shifttingDirection);
void LCD_goToSpecificPosition(u8 LineNumber, u8 position);
void LCD_writeNumber(u32 number);


#endif /* LCD_INTERFACE_H_ */