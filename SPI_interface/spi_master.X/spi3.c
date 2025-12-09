#include <xc.h>
#include <stdint.h>
#include "spi3.h"

uint8_t SPI3_Transfer(uint8_t data)
{
    while (SPI3STATbits.SPITBF);   // Wait if transmit buffer is full
//    LATBbits.LATB6 = 0;  
    SPI3BUF = data;                // Send data
    while (!SPI3STATbits.SPIRBF);  // Wait for receive buffer full
//    LATBbits.LATB6 = 1;  
    return SPI3BUF;                // Return received byte
}