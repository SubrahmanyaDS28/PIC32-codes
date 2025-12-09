#ifndef LCD_H
#define LCD_H

void LCD_Init(void);
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);
void LCD_String(const char *str);
//void delay_ms(int ms);
void LCD_clear(void);
void LCD_PrintInt(int num);
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif