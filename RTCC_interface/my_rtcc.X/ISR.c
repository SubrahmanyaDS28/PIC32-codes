#include <xc.h>
#include <sys/attribs.h>
#include "uart2.h"
#include "constants.h"



void __ISR(_RTCC_VECTOR, IPL3SOFT) RTCC_ISR(void)
{
    LATGbits.LATG14 ^= 1; // Toggle LED
    UART2_putStr("RTCC Alarm Triggered!\r\n");
    IFS0CLR = _IFS0_RTCCIF_MASK; // Clear interrupt flag
}