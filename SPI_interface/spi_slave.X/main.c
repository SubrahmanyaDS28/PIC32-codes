#include <xc.h>
#include <stdint.h>
#include "uart2.h"
#include "spi3.h"
#include "pic32_config.h"
#include "initialize.h"

void main(void)
{
    LATGbits.LATG12 = 1;
    LATGbits.LATG13 = 1;
    LATGbits.LATG14 = 1;
    
    Init_SYS(NULL);

    UART2_putStr("SPI3 Slave Ready\n");

    uint8_t rx, ack = 0xAC;  // ACK to send

    while (1)
    {
        
    }
}