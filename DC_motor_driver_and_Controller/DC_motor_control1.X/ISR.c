#include <xc.h>
#include <stdint.h>
#include <sys/attribs.h>
#include "config.h"
#include "uart2.h"
#include <stdio.h>
#include "extern.h"
#include "constants.h"

// --- System Definitions ---
#define PBCLK 60000000UL          // Assuming 60MHz Peripheral Clock (120MHz SYSCLK / 2)
#define T3_PRESCALER 256.0f       // Timer 3 prescaler [cite: 256]
#define T3_FREQ (PBCLK / T3_PRESCALER)
#define SLOTS_PER_REV 48.0f       // Replace with your slotted wheel's actual count

// --- Control Variables ---
volatile uint32_t dt_ticks = 0;
volatile float current_rpm = 0.0f;
volatile float target_rpm = 500.0f; 
//char msg[10];


// INT3 ISR for Slot Sensor on RD6
void __ISR(_EXTERNAL_3_VECTOR, ipl1SRS) INT3_ISR(void) {
    // 1. Capture the elapsed ticks since the last slot
    dt_ticks = TMR3;
//    UART2_SendNumber(dt_ticks);
    // 2. Reset Timer 3 immediately for the next measurement
    TMR3 = 0; 
    
    // 3. Calculate instantaneous RPM
    // (Ticks/sec) / (Ticks/slot) = slots/sec -> * 60 = slots/min -> / SLOTS_PER_REV = RPM
    if (dt_ticks > 0) {
        current_rpm = (T3_FREQ / (float)dt_ticks) * (60.0f / SLOTS_PER_REV);
//        sprintf(msg, "%.2f", current_rpm);
//        UART2_putStr(msg);
        
    }
    LED_2 ^= 1;
    // 4. Clear the INT3 interrupt flag
    IFS0CLR = _IFS0_INT3IF_MASK; 
}

// --- PI Constants & Polynomial Coefficients ---
#define KP 0.0188f
#define KI 0.3f

volatile float integral_sum = 0.0f;

// Timer 2 ISR for Control Loop (100 Hz)
void __ISR(_TIMER_2_VECTOR, ipl1SRS) Timer2_ISR(void) {
    
    // 1. Calculate Error
    float error = target_rpm - current_rpm;
    
    // 2. Proportional Term
    float p_term = KP * error;
    
    // 3. Integral Term (with Anti-Windup)
    integral_sum += (KI * error);
    
    // Prevent the integral accumulator from winding up beyond physical limits
    if (integral_sum > 100.0f) integral_sum = 100.0f;
    if (integral_sum < 0.0f)   integral_sum = 0.0f;
    
    // 4. Feedforward Term (Based on your polynomial fit) [cite: 202]
    // Duty = 7.8673e-05 * x^2 - 8.5837e-02 * x + 74.730
    float ff_term = (0.000078673f * target_rpm * target_rpm) - 
                    (0.085837f * target_rpm) + 
                    74.730f;
    
    // 5. Compute Total Control Effort (Duty Cycle %)
    float total_duty = p_term + integral_sum + ff_term;
    
    // 6. Deadband and Output Limiter [cite: 156, 158]
    if (total_duty > 100.0f) total_duty = 100.0f;
    if (total_duty < 0.0f)   total_duty = 0.0f; // Alternatively, apply your deadband logic here
    
    // 7. Update Hardware PWM (OC5RS)
    // Convert the 0-100% total_duty into the hardware range defined by PR2 (37500)
    OC5RS = PR2 - (uint32_t)((total_duty / 100.0f) * PR2);
//    LED_2 = 1;
    // 8. Clear the Timer 2 interrupt flag
    IFS0CLR = _IFS0_T2IF_MASK; 
}

void __ISR(_UART2_RX_VECTOR, IPL3SRS) UART2_RX_Handler(void) {
    unsigned char temp;
    static unsigned int STx_RECEIVED = FALSE;
    temp = U2RXREG;
    LED_3 ^= 1;
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