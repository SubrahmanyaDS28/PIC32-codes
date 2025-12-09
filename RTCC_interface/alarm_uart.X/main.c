#include <xc.h>
#include <stdint.h>
#include "uart2.h"
#include "pic32_config.h"
#include "initialize.h"
#include <stdio.h>
#include "rtcc.h"
#include "constants.h"
#include "extern.h"
#include <string.h>

#define LED1 LATGbits.LATG12
#define LED2 LATGbits.LATG13
#define LED3 LATGbits.LATG14


char process_command(void);

FLAG COMMAND_RECEIVED;

unsigned char command[20];

unsigned int command_length = 0;

//unsigned int *load_buffer, *transfer_buffer;

unsigned int command_i;



void main(void)
{
    
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    
    Init_SYS(NULL);
    
    UART2_putchar('~');
    UART2_putchar('~');
    UART2_putchar('~');
    
    UART2_putStr("RTCC Started with LPRC\r\n");

    char buffer[64];

    while (1)
    {

        LED1 ^= 1;
        Read_RTCC_DateTime();
        
        if (COMMAND_RECEIVED){
           UART2_putchar(process_command());
           COMMAND_RECEIVED = FALSE;
        }
        
        for (volatile int i = 0; i < 12000000; i++); // crude delay ~1s
        
    }
}


char process_command(void) {
    unsigned int i = 0;
    char temp;
    
      switch (command[0]) {
            
        case 'a':
            if (command_length != 2)
                return NAK;
            else {
                int value = 0;
                for (i = 1; command[i] != '\0'; i++) {
					temp = command[i] - '0';
                    value = (value  * 10) + temp;                     
                }
                
                set_alarm_time(value);
            }
            
            break;
            
          case 's':
              if (command_length != 9)
                return NAK;
            else {
                  
                char hex_str[9];  // 8 chars for 32-bit hex + null
                strncpy(hex_str, &command[1], 8); // skip '*' and 'a'
                hex_str[8] = '\0';                  // null-terminate
  
                uint32_t alarm_time;
                alarm_time = (uint32_t) strtoul(hex_str, NULL, 16);
                
                set_alarm_to_particular_time(alarm_time);
                
            }
            
            break;
            
          case 't':
              if (command_length != 9)
                return NAK;
              else{
                  char hex_str[9];  // 8 chars for 32-bit hex + null
                strncpy(hex_str, &command[1], 8); // skip '*' and 'a'
                hex_str[8] = '\0';                  // null-terminate
  
                uint32_t new_time;
                new_time = (uint32_t) strtoul(hex_str, NULL, 16);
                
                UART2_SendNumber(new_time);
                set_time(new_time);
              }
              break;
              
          case 'd':
              if (command_length != 9)
                return NAK;
              else{
                  char hex_str[9];  // 8 chars for 32-bit hex + null
                strncpy(hex_str, &command[1], 8); // skip '*' and 'a'
                hex_str[8] = '\0';                  // null-terminate
  
                uint32_t new_date;
                new_date = (uint32_t) strtoul(hex_str, NULL, 16);
                
                set_date(new_date);
              }
              break;
        }
      return ACK;
    }