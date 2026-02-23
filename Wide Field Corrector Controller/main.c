#include <sys/attribs.h>
#include "pic32_config.h"
#include "initialize.h"
#include "config.h"
#include "uart1.h"
#include "constants.h"
#include "extern.h"
#include "stdio.h"

FLAG COMMAND_RECEIVED;

unsigned char command[20];

unsigned int command_length = 0;

unsigned int command_i;

char process_command(void);

char temp = 0;

FLAG INT_STATUS = 0; // External Interrupt status flag

volatile char limit_A = 0;
volatile char limit_B = 0;
volatile char limit_C = 0;
volatile char limit_D = 0;

volatile int MOTOR_A_COUNT = 0;
volatile int MOTOR_B_COUNT = 0;
volatile int MOTOR_C_COUNT = 0;
volatile int MOTOR_D_COUNT = 0;

volatile uint16_t I1 = 0, I2 = 0, I3 = 0, I4 = 0;

volatile char centering = 0;

volatile int TARGET_A = 0;
volatile int TARGET_B = 0;
volatile char tracking_target = 0;

void main() {
    unsigned int i, j = 5000;

    Init_SYS(NULL);

    UART1_putchar('~');
    UART1_putchar('~');
    UART1_putchar('~');

    
    
    while (1) {

        LED_1 = !LED_1;

        if(I1) I1--;
        else IEC0bits.INT3IE = 1;      // Enable INT3 Interrupt
        
        if(I2) I2--;
        else IEC0bits.INT2IE = 1;      // Enable INT2 Interrupt
        
        if(I3) I3--;
        else IEC0bits.INT1IE = 1;      // Enable INT1 Interrupt
        
        if(I4) I4--;
        else IEC0bits.INT4IE = 1;      // Enable INT4 Interrupt
        
        if (COMMAND_RECEIVED) {
            UART1_putchar(process_command());
            COMMAND_RECEIVED = FALSE;
        }

        if(centering){
            // Independently check Motor A
            if(MOTOR_A_COUNT >= 99000 && MOTOR_A_COUNT <= 101000){
                TIMER_MOTOR_A_ON = 0; // Stop Motor A, it is centered
            }
            
            // Independently check Motor B
            if(MOTOR_B_COUNT >= 99000 && MOTOR_B_COUNT <= 101000){
                TIMER_MOTOR_B_ON = 0; // Stop Motor B, it is centered
            }
            
            // Once BOTH motors are safely stopped in the center band, turn off the centering mode
            if(TIMER_MOTOR_A_ON == 0 && TIMER_MOTOR_B_ON == 0){
                centering = 0;
            }
        }
        
        if(tracking_target){
            // Check Motor A
            if (TIMER_MOTOR_A_ON) {
                // Stop if moving forward and reached target, OR moving backward and reached target
                if ((MOTOR_A_DIRECTION == FORWARD && MOTOR_A_COUNT >= TARGET_A) ||
                    (MOTOR_A_DIRECTION == BACKWARD && MOTOR_A_COUNT <= TARGET_A)) {
                    TIMER_MOTOR_A_ON = 0; 
                }
            }
            
            // Check Motor B
            if (TIMER_MOTOR_B_ON) {
                if ((MOTOR_B_DIRECTION == FORWARD && MOTOR_B_COUNT >= TARGET_B) ||
                    (MOTOR_B_DIRECTION == BACKWARD && MOTOR_B_COUNT <= TARGET_B)) {
                    TIMER_MOTOR_B_ON = 0; 
                }
            }
            
            // Turn off tracking mode when both motors have stopped
            if(TIMER_MOTOR_A_ON == 0 && TIMER_MOTOR_B_ON == 0){
                tracking_target = 0;
            }
        }
        
        
        if(j == 0){
//            send_RS232(MOTOR_A_COUNT, MOTOR_B_COUNT, MOTOR_C_COUNT, MOTOR_D_COUNT);
            j = 5000;
        }
        j--;   
        
        for (i = 0; i < 2000; i++)
            Nop();

    }

}

char process_command(void) {
    unsigned int i = 0;
    char temp;
    int counts = 0;

    switch (command[0]) {
        
        case 'Q': // Status Poll / Return Motor Counts
            if (command_length != 1)
                return NAK;
            else {
                char buffer[32];
                
                // Format the output string -> "Q:MotorA,MotorB"
                sprintf(buffer, "Q:%d,%d", MOTOR_A_COUNT, MOTOR_B_COUNT);
                
                UART1_putStr(buffer);
            }
            break;
            
            
        case '1': // North Step (Motor B Forward)
            counts = 0;
            for (i = 1; command[i] != '\0'; i++) {
                counts = (counts * 10) + (command[i] - '0');
            }
            TARGET_B = MOTOR_B_COUNT + counts;
            MOTOR_B_DIRECTION = FORWARD;
            TIMER_MOTOR_B_ON = 1;
            tracking_target = 1;
            UART1_putchar('1');
            break;
            
        case '2': // South Step (Motor B Backward)
            counts = 0;
            for (i = 1; command[i] != '\0'; i++) {
                counts = (counts * 10) + (command[i] - '0');
            }
            TARGET_B = MOTOR_B_COUNT - counts;
            MOTOR_B_DIRECTION = BACKWARD;
            TIMER_MOTOR_B_ON = 1;
            tracking_target = 1;
            UART1_putchar('2');
            break;
            
        case '3': // East Step (Motor A Forward)
            counts = 0;
            for (i = 1; command[i] != '\0'; i++) {
                counts = (counts * 10) + (command[i] - '0');
            }
            TARGET_A = MOTOR_A_COUNT + counts;
            MOTOR_A_DIRECTION = FORWARD;
            TIMER_MOTOR_A_ON = 1;
            tracking_target = 1;
            UART1_putchar('3');
            break;
            
        case '4': // West Step (Motor A Backward)
            counts = 0;
            for (i = 1; command[i] != '\0'; i++) {
                counts = (counts * 10) + (command[i] - '0');
            }
            TARGET_A = MOTOR_A_COUNT - counts;
            MOTOR_A_DIRECTION = BACKWARD;
            TIMER_MOTOR_A_ON = 1;
            tracking_target = 1;
            UART1_putchar('4');
            break;
            
            
        case 'Z': // Home or Initialize position

            if (command_length != 1)
                return NAK;

            else {
                //                IFS0bits.INT2IF = 0;
                
                MOTOR_A_DIRECTION = BACKWARD;
                MOTOR_B_DIRECTION = BACKWARD;
//                MOTOR_C_DIRECTION = FORWARD;
//                MOTOR_D_DIRECTION = BACKWARD;
                
               
                TIMER_MOTOR_A_ON = 1;
                TIMER_MOTOR_B_ON = 1;
//                TIMER_MOTOR_C_ON = 1;
//                TIMER_MOTOR_D_ON = 1;

//                centering = 0;
                UART1_putchar('H');
            }
              break;
            
        case 'c':
            if (command_length != 1)
                return NAK;
            
            else {
                // Determine direction for MOTOR A based on current position
                if (MOTOR_A_COUNT < 99000) {
                    MOTOR_A_DIRECTION = FORWARD;
                    TIMER_MOTOR_A_ON = 1;
                } else if (MOTOR_A_COUNT > 101000) {
                    MOTOR_A_DIRECTION = BACKWARD;
                    TIMER_MOTOR_A_ON = 1;
                } else {
                    TIMER_MOTOR_A_ON = 0; // Already centered
                }

                // Determine direction for MOTOR B based on current position
                if (MOTOR_B_COUNT < 99000) {
                    MOTOR_B_DIRECTION = FORWARD;
                    TIMER_MOTOR_B_ON = 1;
                } else if (MOTOR_B_COUNT > 101000) {
                    MOTOR_B_DIRECTION = BACKWARD;
                    TIMER_MOTOR_B_ON = 1;
                } else {
                    TIMER_MOTOR_B_ON = 0; // Already centered
                }

                // Turn on the centering monitoring loop if at least one motor is moving
                if (TIMER_MOTOR_A_ON == 1 || TIMER_MOTOR_B_ON == 1) {
                    centering = 1;
                }
            }
            break;
            
        case 'A': // FORWARD operation MOTOR-1

            if (command_length != 1)
                return NAK;

            else {
                
//                IFS0bits.INT2IF = 0;
//                IEC0bits.INT3IE = 0;
                
                MOTOR_A_DIRECTION = FORWARD;
                TIMER_MOTOR_A_ON = 1;

                UART1_putchar('A');
//                limit_A = 0;
            }

            break;
            //     
            
            case 'B': // BACKWARD operation MOTOR-1

            if (command_length != 1)
                return NAK;

            else {
//                IEC0bits.INT3IE = 1;
                
                if(limit_A == 0){
                    
//                IFS0bits.INT2IF = 0;
                MOTOR_A_DIRECTION = BACKWARD;
                TIMER_MOTOR_A_ON = 1;

                UART1_putchar('B');
                }
            }

            break;
            //      
            
            
            case 'C': // FORWARD operation MOTOR-2

            if (command_length != 1)
                return NAK;
            else {
//                IFS0bits.INT3IF = 0;
                MOTOR_B_DIRECTION = FORWARD;
                TIMER_MOTOR_B_ON = 1;
                
                UART1_putchar('C');
            }
            break;
            
            case 'D': // BACKWARD operation MOTOR-2

            if (command_length != 1)
                return NAK;
            else {
                
                if(limit_B == 0){
                    
//                IFS0bits.INT3IF = 0;
                MOTOR_B_DIRECTION = BACKWARD;
                TIMER_MOTOR_B_ON = 1;
                
                UART1_putchar('D');
                }
            }
            break;
            
            
            case 'E': // FORWARD operation MOTOR-3

            if (command_length != 1)
                return NAK;

            else {
                IFS0bits.INT2IF = 0;
                MOTOR_C_DIRECTION = BACKWARD;
                TIMER_MOTOR_C_ON = 1;

                UART1_putchar('E');
            }

            break;
            //     
            
            case 'F': // BACKWARD operation MOTOR-3

            if (command_length != 1)
                return NAK;

            else {
                
                if(limit_C == 0){
                IFS0bits.INT2IF = 0;
                MOTOR_C_DIRECTION = FORWARD;
                TIMER_MOTOR_C_ON = 1;

                UART1_putchar('F');
                }
            }

            break;
            //      

            
            case 'G': // FORWARD operation MOTOR-4

            if (command_length != 1)
                return NAK;

            else {
//                IFS0bits.INT2IF = 0;
                MOTOR_D_DIRECTION = FORWARD;
                TIMER_MOTOR_D_ON = 1;

                UART1_putchar('G');
            }

            break;
            //     
            
            case 'H': // BACKWARD operation MOTOR-4

            if (command_length != 1)
                return NAK;

            else {
                if(limit_D == 0){
//                IFS0bits.INT2IF = 0;
                MOTOR_D_DIRECTION = BACKWARD;
                TIMER_MOTOR_D_ON = 1;

                UART1_putchar('H');
                }
            }

            break;
     


        case 'S': // STOP operation

            if (command_length != 1)
                return NAK;
            else {
                TIMER_MOTOR_A_ON = 0;
                TIMER_MOTOR_B_ON = 0;
                TIMER_MOTOR_C_ON = 0;
                TIMER_MOTOR_D_ON = 0;
                UART1_putchar('S');
                centering = 0;
            }
            break;

        case 'P': // Parking Position
            if (command_length != 1)
                return NAK;
            
            else {
                // Set your desired absolute parking coordinates here
                TARGET_A = 50000; 
                TARGET_B = 50000; 

                // Determine direction for MOTOR A based on current position
                if (MOTOR_A_COUNT < TARGET_A) {
                    MOTOR_A_DIRECTION = FORWARD;
                    TIMER_MOTOR_A_ON = 1;
                } else if (MOTOR_A_COUNT > TARGET_A) {
                    MOTOR_A_DIRECTION = BACKWARD;
                    TIMER_MOTOR_A_ON = 1;
                } else {
                    TIMER_MOTOR_A_ON = 0; // Already parked
                }

                // Determine direction for MOTOR B based on current position
                if (MOTOR_B_COUNT < TARGET_B) {
                    MOTOR_B_DIRECTION = FORWARD;
                    TIMER_MOTOR_B_ON = 1;
                } else if (MOTOR_B_COUNT > TARGET_B) {
                    MOTOR_B_DIRECTION = BACKWARD;
                    TIMER_MOTOR_B_ON = 1;
                } else {
                    TIMER_MOTOR_B_ON = 0; // Already parked
                }

                // Turn on the tracking loop so they stop automatically
                if (TIMER_MOTOR_A_ON == 1 || TIMER_MOTOR_B_ON == 1) {
                    tracking_target = 1; 
                }
                
                UART1_putchar('P');
            }
            break;
            
            
        case 'R': // RESET COUNT operation

            if (command_length != 1)
                return NAK;

            else {
                MOTOR_A_COUNT = 0;
                MOTOR_B_COUNT = 0;
                MOTOR_C_COUNT = 0;
                MOTOR_D_COUNT = 0;


                UART1_putchar('R');
            }

            break;

            //        case 'f':                   // Setting frequency FxXXXX
//            			if (command_length != 5)
//            				return NAK;
//                        
//            			else {
//                            
//                            
//                            motor1_frequency = 0;
//                            for (i = 1; command[i] != '\0'; i++) {
//            					temp = command[i] - '0';
//                                motor1_frequency = (motor1_frequency  * 10) + temp;                     
//                            }
//                           TIMER_MOTOR_ON = 0;
//                           PR2 = Fcy/(16*motor1_frequency*2);
//                           TMR2 = 0x0; 
//                           TIMER_MOTOR_ON = 1;
//                        }
//                        break;
            //            
            
            
        case 'f':
            if (command_length != 1)
                return NAK;
            
            else {
                TIMER_MOTOR_A_ON = 0;
                TIMER_MOTOR_B_ON = 0;
                TIMER_MOTOR_C_ON = 0;
                TIMER_MOTOR_D_ON = 0;
                UART1_putchar('f');
                
                // Set Fast Speed Limits
                PR2 = 500;
                PR3 = 500;
                PR4 = 500;
                PR5 = 500;
                
                // RESET the running timers so they don't get stuck!
                TMR2 = 0;
                TMR3 = 0;
                TMR4 = 0;
                TMR5 = 0;
            }
            break;
            
        case 's':
            if (command_length != 1)
                return NAK;
            
            else {
                TIMER_MOTOR_A_ON = 0;
                TIMER_MOTOR_B_ON = 0;
                TIMER_MOTOR_C_ON = 0;
                TIMER_MOTOR_D_ON = 0;
                UART1_putchar('s');
                
                // Set Slow Speed Limits
                PR2 = 2000;
                PR3 = 2000;
                PR4 = 2000;
                PR5 = 2000;
                
                // RESET the running timers so they don't get stuck!
                TMR2 = 0;
                TMR3 = 0;
                TMR4 = 0;
                TMR5 = 0;
            }
            break;
            
    }
    return ACK;
}
//




