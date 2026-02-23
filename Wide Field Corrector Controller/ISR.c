#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "uart1.h"
#include "constants.h"
#include "interrupts.h"
#include "extern.h"




void __ISR(_UART1_RX_VECTOR, ipl1SRS) UART1_RX_Handler(void) {

    unsigned char temp;
    static unsigned int STx_RECEIVED = FALSE;

    temp = U1RXREG;

    UART1_putchar(temp);

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
            if (STx_RECEIVED)
                command[command_i++] = temp;
            else
                UART1_putchar(NAK);
    }

    IFS1bits.U1RXIF = 0; // clear Rx interrupt flag

}

void __attribute__((used)) __ISR(_EXTERNAL_3_VECTOR, ipl1SRS) EXTERNAL_3_Handler(void) {
   
    
    
    if(MOTOR_A_DIRECTION == BACKWARD){
        LED_3 = !LED_3;
        UART1_putchar('Y');
        TIMER_MOTOR_A_ON = 0;
        MOTOR_A_COUNT = 0;
        limit_A = 1;
    
        IEC0bits.INT3IE = 0;      // Disable INT3 Interrupt
        I1 = 200;
    }
    
    
    IFS0bits.INT3IF = 0;
}


void __attribute__((used)) __ISR(_EXTERNAL_2_VECTOR, ipl1SRS) EXTERNAL_2_Handler(void) {
    
    if(MOTOR_B_DIRECTION == BACKWARD){
        LED_2 = !LED_2;
    UART1_putchar('Z');
    TIMER_MOTOR_B_ON = 0;
    MOTOR_B_COUNT = 0;

    limit_B = 1;
    
    IEC0bits.INT2IE = 0;      // Disable INT2 Interrupt
    I2 = 200;
    }
    IFS0bits.INT2IF = 0;
}

void __attribute__((used)) __ISR(_EXTERNAL_1_VECTOR, ipl1SRS) EXTERNAL_1_Handler (void)
{
    if(MOTOR_C_DIRECTION == FORWARD){
    UART1_putchar('y');
    TIMER_MOTOR_C_ON = 0;
    MOTOR_C_COUNT = 0;

    limit_C = 1;
    
    IEC0bits.INT1IE = 0;      // Disable INT1 Interrupt
    I3 = 200;
    }
    IFS0bits.INT1IF = 0;
}

void __attribute__((used)) __ISR(_EXTERNAL_4_VECTOR, ipl1SRS) EXTERNAL_4_Handler (void)
{
    if(MOTOR_D_DIRECTION == BACKWARD){
    UART1_putchar('z');
    TIMER_MOTOR_D_ON = 0;
    MOTOR_D_COUNT = 0;

    limit_D = 1;
    
    IEC0bits.INT4IE = 0;      // Disable INT4 Interrupt
    I4 = 200;
    }
    IFS0bits.INT4IF = 0;
}


void __attribute__((used)) __ISR(_TIMER_2_VECTOR, ipl1SRS) TIMER_2_Handler(void) {

    if (MOTOR_A_DIRECTION == FORWARD) {
        MOTOR_A_COUNT++;
        limit_A = 0;
    }
    else if (MOTOR_A_DIRECTION == BACKWARD) {
        MOTOR_A_COUNT--;
    }

    // Optional: stop condition based on absolute count
    if (abs(MOTOR_A_COUNT) >= 200000) {
        TIMER_MOTOR_A_ON = 0;
        UART1_putchar('X');
    }
    else {
        MOTOR_A_PULSE = !MOTOR_A_PULSE; // Toggle pulse
    }

    IFS0bits.T2IF = 0; // Reset Timer2 interrupt flag
}

void __attribute__((used)) __ISR(_TIMER_3_VECTOR, ipl1SRS) TIMER_3_Handler(void) {
    if (MOTOR_B_DIRECTION == FORWARD) {
        MOTOR_B_COUNT++;
        limit_B = 0;
    }
    else if (MOTOR_B_DIRECTION == BACKWARD) {
        MOTOR_B_COUNT--;
    }

    // Optional: stop condition based on absolute count
    if (abs(MOTOR_B_COUNT) >= 200000) {
        TIMER_MOTOR_B_ON = 0;
        UART1_putchar('W');
    }
    else {
        MOTOR_B_PULSE = !MOTOR_B_PULSE; // Toggle pulse
    }

    IFS0bits.T3IF = 0; // Reset Timer2 interrupt flag
}

void __attribute__((used)) __ISR(_TIMER_4_VECTOR, ipl1SRS) TIMER_4_Handler(void) {
   if (MOTOR_C_DIRECTION == FORWARD) {
        MOTOR_C_COUNT++;
        limit_C = 0;
    }
    else if (MOTOR_C_DIRECTION == BACKWARD) {
        MOTOR_C_COUNT--;
    }

    // Optional: stop condition based on absolute count
    if (abs(MOTOR_C_COUNT) >= 100000) {
        TIMER_MOTOR_C_ON = 0;
    }
    else {
        MOTOR_C_PULSE = !MOTOR_C_PULSE; // Toggle pulse
    }

    IFS0bits.T4IF = 0; // Reset Timer4 interrupt flag
}

void __attribute__((used)) __ISR(_TIMER_5_VECTOR, ipl1SRS) TIMER_5_Handler(void) {
    if (MOTOR_D_DIRECTION == FORWARD) {
        MOTOR_D_COUNT++;
        limit_D = 0;
    }
    else if (MOTOR_D_DIRECTION == BACKWARD) {
        MOTOR_D_COUNT--;
    }

    // Optional: stop condition based on absolute count
    if (abs(MOTOR_D_COUNT) >= 100000) {
        TIMER_MOTOR_D_ON = 0;
    }
    else {
        MOTOR_D_PULSE = !MOTOR_D_PULSE; // Toggle pulse
    }

    IFS0bits.T5IF = 0; // Reset Timer4 interrupt flag
}