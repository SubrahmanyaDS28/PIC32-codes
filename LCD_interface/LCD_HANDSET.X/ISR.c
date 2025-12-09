#include <xc.h>
#include <sys/attribs.h>
#include "uart2.h"
#include "constants.h"
#include "extern.h"


void __ISR(_RTCC_VECTOR, IPL3SOFT) RTCC_ISR(void)
{
    LATGbits.LATG14 ^= 1; // Toggle LED
    UART2_putStr("RTCC Alarm Triggered!\r\n");
    IFS0CLR = _IFS0_RTCCIF_MASK; // Clear interrupt flag
}

void __ISR(_UART2_RX_VECTOR, IPL1AUTO) UART1_RX_Handler(void) {
    
    unsigned char temp;
    static unsigned int STx_RECEIVED = FALSE;
    temp = U2RXREG;
    
    UART2_putchar(temp);
    
    switch (temp) {
        case STx:
            command_i = 0;
            STx_RECEIVED = TRUE;
            break;
            
        case ETx:
            command_length = command_i;
            command[command_i] = '\0';
            COMMAND_RECEIVED = TRUE;
            STx_RECEIVED = FALSE;
            break;
            
        default:
            if(STx_RECEIVED)
                command[command_i++] = temp;
            else
                UART2_putchar(NAK);
    }
    
    IFS1CLR = _IFS1_U2RXIF_MASK;
}


volatile uint8_t EAST_LIMIT = 0;
volatile uint8_t WEST_LIMIT = 0;
volatile uint8_t NORTH_LIMIT = 0;
volatile uint8_t SOUTH_LIMIT = 0;


volatile uint16_t last_state1 = 0x0;
void __ISR(_CHANGE_NOTICE_B_VECTOR, IPL3SRS) CN_B_Handler(void){
    uint32_t dummy3 = PORTB;               // 1) Latch PORTB
    
    uint16_t now1 = read_switches();
    UART2_SendHex(now1);
    uint16_t changed1 = now1 ^ last_state1; 
//    UART2_SendHex(changed1);
//    UART2_SendHex(s);
    if (direction_enabled){
        
            UART2_putStr(" heb\n");
            
        if (changed1 & 0x100) { // RA_E changed
            if (now1 & 0x100){
                RA_PULSE = PULSE_OFF;
//                DEC_PULSE = PULSE_OFF;
            }
            else if (!EAST_LIMIT) {
                
                MOTOR_DIRECTION_RA = EAST_DIRECTION;
                TIMER_WEST_EAST = TIMER_VALUE(HandSetFreq);
                RA_PULSE = PULSE_ON;
//                DEC_PULSE = PULSE_OFF; 
                
            UART2_putStr(" e\n");
            }
        }
        if (changed1 & 0x200) { // RA_W changed
            if (now1 & 0x200){
                RA_PULSE = PULSE_OFF;
//                DEC_PULSE = PULSE_OFF;
            }
            else if (!WEST_LIMIT) {
                MOTOR_DIRECTION_RA = WEST_DIRECTION;
                TIMER_WEST_EAST = TIMER_VALUE(HandSetFreq);
                RA_PULSE = PULSE_ON;
//                DEC_PULSE = PULSE_OFF;
            UART2_putStr(" w\n");
            }
        }
        if (changed1 & 0x400) { // DEC_N changed
            if (now1 & 0x400){
//                RA_PULSE = PULSE_OFF;
                DEC_PULSE = PULSE_OFF;
            }
            else if (!NORTH_LIMIT) {
                MOTOR_DIRECTION_DEC = NORTH_DIRECTION;
                TIMER_NORTH_SOUTH = TIMER_VALUE(HandSetFreq);
                DEC_PULSE = PULSE_ON;
//                RA_PULSE = PULSE_OFF;
                
            UART2_putStr(" n\n");
            }
        }
        if (changed1 & 0x800) { // DEC_S changed
            if (now1 & 0x800){
//                RA_PULSE = PULSE_OFF;
                DEC_PULSE = PULSE_OFF;
            }
            else if (!SOUTH_LIMIT) {
                MOTOR_DIRECTION_DEC = SOUTH_DIRECTION;
                TIMER_NORTH_SOUTH = TIMER_VALUE(HandSetFreq);
                DEC_PULSE = PULSE_ON;
//                RA_PULSE = PULSE_OFF;
            UART2_putStr(" s\n");
            }
        }
        last_state1 = now1; // 4) Save state
    }
    IFS1CLR = _IFS1_CNBIF_MASK; 
}
