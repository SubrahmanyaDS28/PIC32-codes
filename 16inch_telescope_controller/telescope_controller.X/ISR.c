#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "uart2.h"
#include "constants.h"
#include "interrupts.h"
#include "extern.h"
#include "command.h"
#include "constants.h"

volatile uint8_t last_state = 0x0;

volatile uint16_t HandSetFreq = SET_FREQUENCY; 

volatile uint8_t EAST_LIMIT = 0;
volatile uint8_t WEST_LIMIT = 0;
volatile uint8_t NORTH_LIMIT = 0;
volatile uint8_t SOUTH_LIMIT = 0;

// ---------------- CN for PORTC ---------------- //
void __ISR(_CHANGE_NOTICE_C_VECTOR, IPL2SRS) CN_C_Handler(void) {
    uint32_t dummy = PORTC;              // latch PORTC

    uint8_t now = read_switches();
    uint8_t changed = now ^ last_state;

    if (changed & 0x01) { // RA_E changed
        if (now & 0x01){
            UART2_putStr("RC\n");
            EAST_LIMIT = 0;
        } 
        else {
            RA_PULSE = PULSE_OFF;
            DEC_PULSE = PULSE_OFF;
            UART2_putStr("RE\n");
            EAST_LIMIT = 1;
        }
    }
    if (changed & 0x02) { // RA_W changed
        if (now & 0x02) {
            UART2_putStr("RC\n");
            WEST_LIMIT = 0;
        }
        else{
            RA_PULSE = PULSE_OFF;
            DEC_PULSE = PULSE_OFF;
            UART2_putStr("RW\n");
            WEST_LIMIT = 1;
        }
    }

    last_state = now;
    IFS1CLR = _IFS1_CNCIF_MASK;          // clear CN flag for PORTC
}

// --- ISR for PORTD CN ---
void __ISR(_CHANGE_NOTICE_D_VECTOR, IPL2SRS) CN_D_Handler(void) {
    uint32_t dummy1 = PORTD;               // 1) Latch PORTD

    uint8_t now = read_switches();        // 3) Read combined state
    uint8_t changed = now ^ last_state;   // Detect changes

    if (changed & 0x04) { // DEC_N (RD5)
        if (now & 0x04) {
            UART2_putStr("DC\n");
            NORTH_LIMIT = 0;
        }
        else{
            RA_PULSE = PULSE_OFF;
            DEC_PULSE = PULSE_OFF; 
            UART2_putStr("DN\n");
            NORTH_LIMIT = 1;
        }
    }
    if (changed & 0x08) { // DEC_S (RD6)
        if (now & 0x08) {
            UART2_putStr("DC\n");
            SOUTH_LIMIT = 0;
        }
        else{
            RA_PULSE = PULSE_OFF;
            DEC_PULSE = PULSE_OFF; 
            UART2_putStr("DS\n");
            SOUTH_LIMIT = 1;
        }
    }

    last_state = now; // 4) Save state
    IFS1CLR = _IFS1_CNDIF_MASK;           // 2) Clear CN flag
}

volatile uint16_t last_state1 = 0x0;
void __ISR(_CHANGE_NOTICE_B_VECTOR, IPL3SRS) CN_B_Handler(void){
    uint32_t dummy3 = PORTB;               // 1) Latch PORTB
    
    uint16_t now1 = read_switches();
    UART2_SendHex(now1);
    uint16_t changed1 = now1 ^ last_state1; 
//    UART2_SendHex(changed1);
//    UART2_SendHex(s);
    if (handset_enabled){
        
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

volatile uint16_t last_stateF = 0x0;
void __ISR(_CHANGE_NOTICE_F_VECTOR, IPL1SRS) CN_F_Handler(void){
//    UART2_putStr(" FFFF \n");
    uint32_t dummy4 = PORTF;               // 1) Latch PORTF
    
    uint16_t nowF = read_switches();
//    UART2_SendHex(nowF);
    uint16_t changedF = nowF ^ last_stateF;
    
    
    
        
        UART2_putStr(" hef\n");
        if (changedF & 0x10) { // RA_E changed
            if (nowF & 0x10){
                HandSetFreq = 800;
                UART2_SendNumber(HandSetFreq);
                UART2_putStr(" f2\n");
            }
            
            else {
                HandSetFreq = 1100;
                UART2_SendNumber(HandSetFreq);
                UART2_putStr(" f1\n");
                
                
                RA_PULSE = PULSE_OFF;
                DEC_PULSE = PULSE_OFF;
            }
        }
        if (changedF & 0x20) { // RA_W changed
            if (nowF & 0x20){
                HandSetFreq = 800;
                UART2_SendNumber(HandSetFreq);
                UART2_putStr(" f2\n");
                
                RA_PULSE = PULSE_OFF;
                DEC_PULSE = PULSE_OFF;
                if(console == 1){
                    handset_enabled = 0;
                }
                else {
                    handset_enabled = 1;
                }
            }
            else  {
                
                if (handset_enabled){
                    if(!WEST_LIMIT){
                        MOTOR_DIRECTION_RA = WEST_DIRECTION;
                        TIMER_WEST_EAST = TIMER_VALUE(30);
                        RA_PULSE = PULSE_ON;
                        DEC_PULSE = PULSE_OFF;
                    }
            
                handset_enabled = 0;
            }
        }
        }
        last_stateF = nowF; // 4) Save state
            
    IFS1CLR = _IFS1_CNFIF_MASK; 
}

void __ISR(_UART2_RX_VECTOR, IPL1AUTO) UART2_RX_Handler(void) {
    static uint8_t idx = 0;
    char c = U2RXREG;
    
    while (U2STAbits.TRMT == 0); // Wait till previously sent character is transmitted

	U2TXREG = c;
    
    if (c == '\n') { 
        uart_buffer[idx] = '\0';
        idx = 0;
        uart_flag = 1;
    } else {
        uart_buffer[idx++] = c;
        if (idx >= sizeof(uart_buffer)) idx = 0;
    }
    IFS1CLR = _IFS1_U2RXIF_MASK;
}


//void __attribute__((used)) __ISR(_EXTERNAL_2_VECTOR, ipl1SRS) EXTERNAL_2_Handler (void)
//{
//    LED_2 = !LED_2;
//    UART1_putchar('R');
//    IFS0bits.INT2IF = 0;
//        
//
//}
//
//void __attribute__((used)) __ISR(_EXTERNAL_3_VECTOR, ipl1SRS) EXTERNAL_3_Handler (void)
//{
//    LED_3 = !LED_3;
//    UART1_putchar('D');
//    IFS0bits.INT3IF = 0;
//   
//}