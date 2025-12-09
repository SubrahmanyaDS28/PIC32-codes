#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <xc.h>

#define Fosc 120000000

//#define Fosc 80000000
//
#define Fcy Fosc/2

#define BAUDRATE 115200

#define TIMER_VALUE(freq) Fcy/(2 * freq) - 1

#define STx '*' // 02

#define ETx '#' // 03

#define LED_1  LATGbits.LATG12 
#define LED_2  LATGbits.LATG13
#define LED_3  LATGbits.LATG14


//#define RA_PULSE_OUT          LATAbits.LATA7
//#define DEC_PULSE_OUT         LATBbits.LATB15
//
//#define MOTOR_DIRECTION_RA    LATBbits.LATB14
//#define MOTOR_DIRECTION_DEC   LATDbits.LATD1
//
//#define BUTTON_EAST            PORTCbits.RC9
//#define BUTTON_WEST            PORTCbits.RC0 
//#define BUTTON_NORTH           PORTDbits.RD5
//#define BUTTON_SOUTH           PORTCbits.RC8
//#define BUTTON_HIGH_SPEED      PORTGbits.RG11
//#define BUTTON_LOW_SPEED       PORTEbits.RE12
//#define BUTTON_HANDSET_ENABLE  PORTFbits.RF13
//#define BUTTON_TRACK_ON        PORTFbits.RF12

#define RA_PULSE_OUT          LATAbits.LATA7
#define DEC_PULSE_OUT         LATBbits.LATB15

#define MOTOR_DIRECTION_RA    LATBbits.LATB14
#define MOTOR_DIRECTION_DEC   LATDbits.LATD1

//#define BUTTON_EAST            PORTCbits.RC9
//#define BUTTON_WEST            PORTCbits.RC0 
//#define BUTTON_NORTH           PORTDbits.RD5
//#define BUTTON_SOUTH           PORTCbits.RC8
//#define BUTTON_HIGH_SPEED      PORTGbits.RG11
//#define BUTTON_LOW_SPEED       PORTEbits.RE12
//#define BUTTON_HANDSET_ENABLE  PORTFbits.RF13
//#define BUTTON_TRACK_ON        PORTFbits.RF12

#define RA_PULSE  OC5CONbits.OCM
#define DEC_PULSE OC1CONbits.OCM 

#define PULSE_ON  0b011
#define PULSE_OFF 0b000

#define TIMER_WEST_EAST     PR2
#define TIMER_NORTH_SOUTH   PR3

#define SLEW_FREQUENCY 1100   //IN Hz
#define SET_FREQUENCY 900         //IN Hz
#define GUIDE_FREQUENCY 700    //IN Hz
#define FINE_GUIDE_FREQUENCY 500


#define EAST_DIRECTION  0
#define WEST_DIRECTION  1
#define NORTH_DIRECTION 0
#define SOUTH_DIRECTION 1


// --- Limit Switch Macros ---
#define RA_E_PORT   PORTCbits.RC8   // RA East  (C8)
#define RA_W_PORT   PORTCbits.RC9   // RA West  (C9)
#define DEC_N_PORT  PORTDbits.RD5   // DEC North (D5)
#define DEC_S_PORT  PORTDbits.RD6   // DEC South (D6)

#define SEL0 LATDbits.LATD8
#define SEL1 LATBbits.LATB5
#define SEL2 LATBbits.LATB6


#endif