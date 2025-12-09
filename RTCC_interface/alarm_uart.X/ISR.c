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