#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <xc.h>

#define Fosc 120000000

#define Fcy Fosc/2

#define BAUDRATE 115200

//#define TIMER_VALUE(freq) Fcy/(8.0 * freq)

#define STx '*' // 02

#define ETx '#' // 03

#define LED_1  LATGbits.LATG12 
#define LED_2  LATGbits.LATG13
#define LED_3  LATGbits.LATG14

#define MOTOR_A_DIRECTION  LATBbits.LATB14
//#define MOTOR_A_DIRECTION  LATGbits.LATG11
#define MOTOR_B_DIRECTION  LATDbits.LATD1
#define MOTOR_C_DIRECTION  LATBbits.LATB13
#define MOTOR_D_DIRECTION  LATFbits.LATF7

#define MOTOR_A_PULSE  PORTAbits.RA7
//#define MOTOR_A_PULSE  PORTCbits.RC11
#define MOTOR_B_PULSE  PORTBbits.RB15
#define MOTOR_C_PULSE  PORTBbits.RB12
#define MOTOR_D_PULSE  PORTFbits.RF6

#define TIMER_MOTOR_A_ON T2CONbits.ON
#define TIMER_MOTOR_B_ON T3CONbits.ON 
#define TIMER_MOTOR_C_ON T4CONbits.ON 
#define TIMER_MOTOR_D_ON T5CONbits.ON 


#define FORWARD  1
#define BACKWARD 0

#define TIMER_2     PR2
#define TIMER_3     PR3
#define TIMER_4     PR4
#define TIMER_5     PR5


#endif