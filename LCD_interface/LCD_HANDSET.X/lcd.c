#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#include "delay.h"

// LCD Control Pins
#define LCD_RS LATCbits.LATC0
#define LCD_EN LATGbits.LATG11

#define LCD_RW LATCbits.LATC11

// LCD Data Pins (4-bit mode)
#define LCD_D4 LATEbits.LATE12
#define LCD_D5 LATEbits.LATE13
#define LCD_D6 LATFbits.LATF12
#define LCD_D7 LATFbits.LATF13

// TRIS Control
#define LCD_RS_TRIS TRISCbits.TRISC0
#define LCD_EN_TRIS TRISGbits.TRISG11
#define LCD_RW_TRIS TRISCbits.TRISC11
#define LCD_D4_TRIS TRISEbits.TRISE12
#define LCD_D5_TRIS TRISEbits.TRISE13
#define LCD_D6_TRIS TRISFbits.TRISF12
#define LCD_D7_TRIS TRISFbits.TRISF13


// Delay ~1ms @ ~120MHz core clock
//void delay_ms(int ms) {
//      for (int i = 0; i < ms * 4000; i++) {
////              asm("nop");
//          Nop();
//      }
//}

void LCD_EnablePulse(void) {
      LCD_EN = 1;
      delay_ms(1);
      LCD_EN = 0;
      delay_ms(1);
}

void LCD_Send4Bits(unsigned char nibble) {
      LCD_D4 = (nibble >> 0) & 1;
      LCD_D5 = (nibble >> 1) & 1;
      LCD_D6 = (nibble >> 2) & 1;
      LCD_D7 = (nibble >> 3) & 1;
      LCD_EnablePulse();
}

void LCD_Command(unsigned char cmd) {
      LCD_RS = 0;
      LCD_Send4Bits(cmd >> 4);
      LCD_Send4Bits(cmd & 0x0F);
      delay_ms(2);
}

void LCD_Char(unsigned char data) {
      LCD_RS = 1;
      LCD_Send4Bits(data >> 4);
      LCD_Send4Bits(data & 0x0F);
      delay_ms(2);
}

void LCD_String(const char *str) {
      while (*str) {
              LCD_Char(*str++);
      }
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address;

    // Calculate DDRAM address
    switch (row)
    {
        case 0: address = 0x00 + col; break; // First line
        case 1: address = 0x40 + col; break; // Second line
        case 2: address = 0x14 + col; break; // Third line (for 20x4)
        case 3: address = 0x54 + col; break; // Fourth line (for 20x4)
        default: address = 0x00; break;       // Default to top-left
    }

    // Set DDRAM address command: 0x80 | address
    LCD_Command(0x80 | address);
}

void LCD_clear(void){
    LCD_Command(0x01); // Clear display
}

void LCD_PrintInt(int num)
{
    char buffer[12];          // Enough for 32-bit integer (-2147483648)
    sprintf(buffer, "%d", num);  // Convert integer to string
    LCD_String(buffer);          // Send string to LCD
}

void LCD_Init(void) {
      // Set pins to output
      LCD_RS_TRIS = 0;
      LCD_EN_TRIS = 0;
      LCD_RW_TRIS = 0;
      LCD_D4_TRIS = 0;
      LCD_D5_TRIS = 0;
      LCD_D6_TRIS = 0;
      LCD_D7_TRIS = 0;
      
      LCD_RW = 0;
      
      ANSELCbits.ANSC0 = 0; 
      ANSELGbits.ANSG11 = 0; 
      ANSELCbits.ANSC11 = 0; 
      ANSELEbits.ANSE12 = 0; 
      ANSELEbits.ANSE13 = 0; 
      ANSELFbits.ANSF12 = 0; 
      ANSELFbits.ANSF13 = 0;
      
      delay_ms(20); // LCD power-up delay

      LCD_RS = 0;
      LCD_Send4Bits(0x03); delay_ms(5);
      LCD_Send4Bits(0x03); delay_ms(5);
      LCD_Send4Bits(0x03); delay_ms(1);
      LCD_Send4Bits(0x02); // Set 4-bit mode

      LCD_Command(0x28); // Function set: 4-bit, 2-line, 5x8
      LCD_Command(0x0C); // Display ON, cursor OFF
      LCD_Command(0x06); // Entry mode: Increment
      LCD_Command(0x01); // Clear display
      delay_ms(2);
}