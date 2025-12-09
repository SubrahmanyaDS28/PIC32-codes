#include <xc.h>
#include <stdio.h>
#include "rtcc.h"
#include "uart2.h"
#include "lcd.h"

// Convert BCD to Decimal
uint8_t bcd_to_decimal(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void Read_RTCC_DateTime_UART(void){
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

void Read_RTCC_DateTime_LCD(void){
    uint32_t t = RTCTIME;
    uint32_t d = RTCDATE;

    // --- Time ---
    uint8_t hour_bcd = (t >> 24) & 0xFF;
    uint8_t min_bcd  = (t >> 16) & 0xFF;
    uint8_t sec_bcd  = (t >> 8)  & 0xFF;

    // --- Date ---
    uint8_t year_bcd = (d >> 24) & 0xFF;
    uint8_t month_bcd = (d >> 16) & 0xFF;
    uint8_t day_bcd = (d >> 8) & 0xFF;
    uint8_t weekday = d & 0xFF;

    // --- Convert BCD ? Decimal ---
    uint8_t hour = bcd_to_decimal(hour_bcd);
    uint8_t min  = bcd_to_decimal(min_bcd);
    uint8_t sec  = bcd_to_decimal(sec_bcd);
    uint8_t year = bcd_to_decimal(year_bcd);
    uint8_t month = bcd_to_decimal(month_bcd);
    uint8_t day = bcd_to_decimal(day_bcd);

    // --- Weekday names ---
    const char* weekday_str[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

    // --- String Buffers ---
    char time_str[9];   // "HH:MM:SS"
    char date_str[20];  // "DD-MM-YYYY,Day"

    // --- Format Strings ---
    sprintf(time_str, "%02u:%02u:%02u", hour, min, sec);
    sprintf(date_str, "%02u-%02u-20%02u,%s", day, month, year, weekday_str[weekday]);
    
    LCD_Command(0x01);
    LCD_SetCursor(0,0);
    LCD_String(date_str);  // you fill this from your RTC
    LCD_SetCursor(1,0);
    LCD_String(time_str);
}

void set_alarm_time (int value){
    
    SYSKEY = 0x0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RTCCONSET = _RTCCON_RTCWREN_MASK;  // Enable write

    // Disable alarm before setup
    RTCALRMbits.ALRMEN = 0;

    // Wait for sync bit to clear
    while (RTCALRMbits.ALRMSYNC);

    // Set alarm time and date ? optional (if you want exact match)
    ALRMTIME = 0x00000000;  // 00:00:00 in BCD
    ALRMDATE = 0x00000000;  // day/month/year (don?t care if using AMASK)

    // Configure RTCALRM
    RTCALRMbits.CHIME = 1;     // Repeat forever
    RTCALRMbits.AMASK = value; //input taken form uart.
    RTCALRMbits.ARPT = 0xFF;    // Repeat 256 times before rolling
    RTCALRMbits.PIV = 0;        // Alarm pulse initial value
    RTCALRMbits.ALRMEN = 1;     // Enable alarm

    // Enable interrupt
    IFS0CLR = _IFS0_RTCCIF_MASK;
    IEC0SET = _IEC0_RTCCIE_MASK;
    IPC7bits.RTCCIP = 3;

    SYSKEY = 0x0; // Lock
    
}

void set_alarm_to_particular_time (uint32_t alarm_time){
    SYSKEY = 0x0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    
    ALRMTIME = alarm_time;   //from uart
//    ALRMDATE = 0x25101705;   // Mask date for daily alarm

    // Configure alarm mask bits: compare hour, minute, second
    RTCALRM = (0b0110 << 8);
    RTCALRMbits.ALRMEN = 1;   // Enable alarm
    // Enable interrupt
    IFS0CLR = _IFS0_RTCCIF_MASK;
    IEC0SET = _IEC0_RTCCIE_MASK;
    IPC7bits.RTCCIP = 3;

    SYSKEY = 0x0; // Lock
}

void set_time (uint32_t new_time){
    // Unlock sequence
    SYSKEY = 0x0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    RTCCONbits.ON = 0;         // Disable RTCC to configure
    RTCCONbits.RTCCLKSEL = 0b00; // Use LPRC
    RTCCONbits.RTCWREN = 1;    // Allow writes

    // Set initial time/date (BCD)
    // Format: RTCTIME = 0xHHMMSS00;  RTCDATE = 0xYYMMDDWW;
    RTCTIME = new_time;      // 16:00:00
//    RTCDATE = 0x25101604;      // 2025/10/15 (Wed)

    RTCCONbits.ON = 1;         // Enable RTCC

    SYSKEY = 0x0;              // Lock back
}


void set_date (uint32_t new_date){
    // Unlock sequence
    SYSKEY = 0x0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    RTCCONbits.ON = 0;         // Disable RTCC to configure
    RTCCONbits.RTCCLKSEL = 0b00; // Use LPRC
    RTCCONbits.RTCWREN = 1;    // Allow writes

    // Set initial time/date (BCD)
    // Format: RTCTIME = 0xHHMMSS00;  RTCDATE = 0xYYMMDDWW;
//    RTCTIME = new_time;      // 16:00:00
    RTCDATE = new_date;      // 2025/10/15 (Wed)

    RTCCONbits.ON = 1;         // Enable RTCC

    SYSKEY = 0x0;              // Lock back
}
