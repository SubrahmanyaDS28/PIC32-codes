#include <xc.h>
#include <sys/attribs.h>
#include "uart2.h"
#include "constants.h"

//void __ISR(_UART1_RX_VECTOR, IPL1AUTO) UART1_RX_Handler(void) {
//    unsigned char temp;
//    static unsigned int STx_RECEIVED = FALSE;
//    temp = U1RXREG;
//    
//    UART1_putchar(temp);
//    
//    switch (temp) {
//        case STx:
//            command_i = 0;
//            STx_RECEIVED = TRUE;
//            break;
//            
//        case ETx:
//            command_length = command_i;
//            command[command_i] = '\0';
//            COMMAND_RECEIVED = TRUE;
//            STx_RECEIVED = FALSE;
//            break;
//            
//        default:
//            if(STx_RECEIVED)
//                command[command_i++] = temp;
//            else
//                UART1_putchar(NAK);
//    }
//    
//    IFS1CLR = _IFS1_U1RXIF_MASK;
//}

void __attribute__((interrupt(IPL3AUTO), vector(_SPI3_RX_VECTOR))) SPI3_RX_ISR(void)
{
    uint8_t dataIn = SPI3BUF;   // Read received data
    uint8_t dataOut = dataIn;   // For echo-back, modify if needed

    SPI3BUF = dataOut;          // Send next byte (echo)
    LATGbits.LATG14 = !LATGbits.LATG14;  // Toggle LED for visual check

    UART2_putStr("\n Received: 0x");
    UART2_SendHex(dataIn);
    UART2_putStr(" | Sent ACK: 0x");
    UART2_SendHex(dataOut);
    
    IFS6bits.SPI3RXIF = 0;      // Clear interrupt flag
}


