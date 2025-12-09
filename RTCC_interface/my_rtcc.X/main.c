#include <xc.h>
#include <stdint.h>
#include "uart1.h"
#include "uart2.h"
#include "pic32_config.h"
#include "initialize.h"
#include <stdio.h>
#include "rtcc.h"

#define LED1 LATGbits.LATG12
#define LED2 LATGbits.LATG13
#define LED3 LATGbits.LATG14

void main(void)
{
    
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    
    Init_SYS(NULL);

    UART2_putStr("RTCC Started with LPRC\r\n");

    char buffer[64];

    while (1)
    {
//        while (RTCCONbits.RTCSYNC);  // Wait until not syncing
//        uint32_t t = RTCTIME;
//        uint8_t hour = (t >> 24) & 0xFF;
//        uint8_t min  = (t >> 16) & 0xFF;
//        uint8_t sec  = (t >> 8)  & 0xFF;

        LED1 ^= 1;
//        UART2_putStr("123");
        LED2 ^= 1;
//        
       Read_RTCC_DateTime();
        for (volatile int i = 0; i < 12000000; i++); // crude delay ~1s
            

        
    }
}
