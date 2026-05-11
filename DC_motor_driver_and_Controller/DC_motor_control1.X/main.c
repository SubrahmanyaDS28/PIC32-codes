#include <xc.h>
#include <stddef.h>
#include <sys/attribs.h>
#include <stdio.h>
#include "initialize.h"
#include "config.h"
#include "pic32_config.h"
#include "uart2.h"
#include "extern.h"
#include "constants.h"

// Assuming a 120 MHz SYSCLK based on your initialize.c comments.
// The PIC32 Core Timer (_CP0_GET_COUNT) runs at half the SYSCLK (60 MHz).
#define SYSCLK 120000000UL

char process_command(void);

FLAG COMMAND_RECEIVED;

unsigned char command[20];

unsigned int command_length = 0;

//unsigned int *load_buffer, *transfer_buffer;

unsigned int command_i;

// Blocking delay function using the Core Timer for precise timing
void delay_ms(uint32_t ms) {
    uint32_t start_time = _CP0_GET_COUNT();
    uint32_t ticks_to_wait = ms * (SYSCLK / 2 / 1000); 
    while ((_CP0_GET_COUNT() - start_time) < ticks_to_wait);
}
char msg[64];
int main(void) {
    // 1. Run your existing initialization
    
    Init_SYS(NULL);
    LED_1 = 1;

    UART2_putchar('~');
    UART2_putchar('~');
    UART2_putchar('~');
    
    // 2. Configure Timer 2 for the PWM Frequency
    T2CONbits.ON = 0;       // Stop Timer 2 to configure
    T2CONbits.TCKPS = 0;    // 1:1 Prescaler
    TMR2 = 0;               // Clear timer counter
    
    // Set PWM Period. 
    // Frequency = PBCLK / (Prescaler * (PR2 + 1))
    // For 20kHz with 60MHz PBCLK: PR2 = (60M / 20k) - 1 = 2999
    // For 1kHz with 60MHz PBCLK: PR2 = (60M / 1k) - 1 = 59999
    PR2 = 59999;             
    T2CONbits.ON = 1;       // Start Timer 2

    // 3. Configure OCMP5 for PWM Mode
    OC5CONbits.ON = 0;      // Stop OC5 to configure
    OC5CONbits.OCTSEL = 0;  // Select Timer 2 as the time base
    OC5CONbits.OCM = 6;     // OCM = 6 corresponds to PWM mode (Fault pin disabled)
    OC5R = 0;               // Initial Primary Compare
    OC5RS = 0;              // Start with 0% Duty Cycle
    OC5CONbits.ON = 1;      // Start OC5
    LED_1 = 0;
    // 4. Infinite loop changing pulse widths
    while (1) {
        LED_1 ^= 1;
//        OC5RS = (PR2 * 3) / 4;
        delay_ms(1000);
        
        
        if (COMMAND_RECEIVED){
           UART2_putchar(process_command());
           COMMAND_RECEIVED = FALSE;
        }
        
        sprintf(msg, "current RPM = %.2f, target RPM = %.2f \n", current_rpm, target_rpm);
        UART2_putStr((unsigned char *)msg);
    }

    return 0;
}


char process_command(void) {
//    unsigned int i = 0;
//    char temp;
    
      switch (command[0]) {
            
        case 'T':
            target_rpm = atof((char*)&command[1]);
            break;
             
        default:
            
            break;
    }
    return ACK;
}
