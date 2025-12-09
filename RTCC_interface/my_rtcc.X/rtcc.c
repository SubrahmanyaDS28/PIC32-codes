#include <xc.h>
#include "rtcc.h"
#include "uart2.h"


void Read_RTCC_DateTime(void){
     while (RTCCONbits.RTCSYNC);  // Wait until safe to read

    uint32_t t = RTCTIME;
    uint32_t d = RTCDATE;

    // --- Time ---
    uint8_t hour = (t >> 24) & 0xFF;
    uint8_t min  = (t >> 16) & 0xFF;
    uint8_t sec  = (t >> 8)  & 0xFF;

    // --- Date ---
    uint8_t year = (d >> 24) & 0xFF;
    uint8_t month = (d >> 16) & 0xFF;
    uint8_t day = (d >> 8) & 0xFF;
    uint8_t weekday = d & 0xFF;

    // Weekday string lookup
    const char *weekdays[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };

    UART2_putStr("time : ");
    UART2_SendHex(hour);
    UART2_putchar(':');
    UART2_SendHex(min);
    UART2_putchar(':');
    UART2_SendHex(sec);
    UART2_putchar('\n');

    UART2_putStr("date : ");
    UART2_SendHex(day);
    UART2_putchar(':');
    UART2_SendHex(month);
    UART2_putchar(':');
    UART2_putStr("20");
    UART2_SendHex(year);
    UART2_putchar(' ');
    UART2_putStr(weekdays[weekday]);
    UART2_putchar('\n');
    UART2_putchar('\n');
}


