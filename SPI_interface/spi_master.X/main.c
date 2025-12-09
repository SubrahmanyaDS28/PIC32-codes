#include <xc.h>
#include <stdint.h>
#include <stddef.h>
#include "initialize.h"
#include "pic32_config.h"
#include "uart2.h"
#include "spi3.h"

void main(void) {
    
    
    LATBbits.LATB6 = 1;     // Deselect slave initially (SS high)
    
    Init_SYS(NULL);
    
    LATGbits.LATG12 = 1;
    LATGbits.LATG13 = 1;
    LATGbits.LATG14 = 1;
    
    UART2_putchar('\n');
    UART2_putchar('~');
    UART2_putchar('~');
    UART2_putchar('~');
    UART2_putchar('\n');
    
    uint8_t tx = 0xFF;
    uint8_t rx;

    while (1)
    {
        
//        LATBbits.LATB6 = 0;                             // SS low (select slave)
//        for (volatile int i = 0; i < 50; i++) Nop();    // tiny delay
        
        rx = SPI3_Transfer(tx);                         // Send 0xA5, receive one byte
        
//        for (volatile int i = 0; i < 50; i++) Nop();    // tiny delay
//        LATBbits.LATB6 = 1;                             // SS high (deselect slave)
        
//        UART2_putStr("Sent: 0x");
        UART2_SendHex(tx);
//        UART2_putStr(" | Received: 0x");
//        UART2_SendHex(rx);
//        UART2_putchar('\n');

        
        // Increment TX value each time to test
//        tx++;
        
        
        LATGbits.LATG14 ^= 1;
        for (int i = 0; i < 2000; i++)
            for(int j = 0; j < 500; j++)
                Nop();// Delay
    }
}


