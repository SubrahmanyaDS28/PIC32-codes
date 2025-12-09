#include <xc.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "uart2.h"
#include "initialize.h"
#include "config.h"
#include "encoder.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Parallel Encoder output
// counts per one full revolution (17-bit)
#define COUNTS_PER_REV ((uint32_t)1 << 17)   // 131072

double EncoderToDEC(uint32_t counts)
{
    double deg = ((double)counts / (double)COUNTS_PER_REV) * 360.0;  // 0?360
    deg -= 180.0;  // shift center ? now ?180° to +180°, 0° = zenith
    return deg;
}

void DEC_To_DMS(double dec_deg, int16_t *deg, uint8_t *min, uint8_t *sec)
{
    int16_t d = (int16_t)dec_deg;
    double frac = fabs(dec_deg - d);
    *deg = d;
    *min = (uint8_t)(frac * 60.0);
    *sec = (uint8_t)((frac * 3600.0) - (*min * 60.0));
}

double EncoderToRA(uint32_t counts)
{
    double hr = ((double)counts / (double)COUNTS_PER_REV) * 24.0; // 0?24h
    hr -= 12.0;  // shift to ?12h?+12h, 0h = zenith
    return hr;
}


void RA_To_HMS(double ra_hr, int8_t *hour, uint8_t *min, uint8_t *sec)
{
    int8_t h = (int8_t)ra_hr;
    double frac = fabs(ra_hr - h);
    *hour = h;
    *min = (uint8_t)(frac * 60.0);
    *sec = (uint8_t)((frac * 3600.0) - (*min * 60.0));
}


// --------------------
// Convert encoder counts -> RA h:m:s
// RA: 24 hours = 360 degrees = COUNTS_PER_REV counts
// total_seconds = counts * (24*3600) / COUNTS_PER_REV
// --------------------
void counts_to_ra_hms(uint32_t counts, uint8_t *hours, uint8_t *minutes, uint8_t *seconds)
{
    // Guard counts
    if (counts >= COUNTS_PER_REV) counts %= COUNTS_PER_REV;

    // Use 64-bit intermediate to avoid overflow
    uint64_t total_seconds = (uint64_t)counts * (24ULL * 3600ULL) / (uint64_t)COUNTS_PER_REV;

    *hours = (uint8_t)(total_seconds / 3600ULL);            // 0..23
    uint64_t rem = total_seconds % 3600ULL;
    *minutes = (uint8_t)(rem / 60ULL);
    *seconds = (uint8_t)(rem % 60ULL);
}

// --------------------
// Convert encoder counts -> angle deg:min:sec
// 360 degrees = COUNTS_PER_REV counts
// total_arcseconds = counts * (360*3600) / COUNTS_PER_REV
// --------------------
void counts_to_deg_dms(uint32_t counts, uint16_t *degrees, uint8_t *minutes, uint8_t *seconds)
{
    if (counts >= COUNTS_PER_REV) counts %= COUNTS_PER_REV;

    // compute total arcseconds (360 * 3600 = 1,296,000 arcseconds)
    uint64_t total_arcsec = (uint64_t)counts * (360ULL * 3600ULL) / (uint64_t)COUNTS_PER_REV;

    *degrees = (uint16_t)(total_arcsec / 3600ULL);     // 0..359
    uint64_t rem = total_arcsec % 3600ULL;
    *minutes = (uint16_t)(rem / 60ULL);
    *seconds = (uint16_t)(rem % 60ULL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quadrature Encoder output


char msg[100];

void Convert_RA_to_HMS_Centered_QEI1(uint16_t pos)
{
    // Convert counts to hours (centered at 0)
    double hours = (pos * 24.0) / 40000.0;

    // Normalize: wrap range to -12h ... +12h (so zenith = 0)
    if (hours > 12.0)
        hours -= 24.0;
    else if (hours < -12.0)
        hours += 24.0;

    // Convert fractional hours to H:M:S
    int h = (int)hours;
    double frac_h = fabs(hours - h);
    int m = (int)(frac_h * 60.0);
    double s = (frac_h * 3600.0) - (m * 60.0);

    // Print result
    sprintf(msg, "RA_E %s%d:%02d:%05.2f\n", (hours < 0 ? "-" : ""), abs(h), m, s);
    UART2_putStr(msg);
}


void Convert_DEC_to_DMS_Centered_QEI2(int16_t pos)
{
    // Convert counts to degrees (centered at 0)
    double degrees = (pos * 360.0) / 10000.0;

    // Normalize: wrap range to -180° ... +180° (0 at zenith)
    if (degrees > 180.0)
        degrees -= 360.0;
    else if (degrees < -180.0)
        degrees += 360.0;

    // Convert fractional degrees to D:M:S
    int d = (int)degrees;
    double frac_d = fabs(degrees - d);
    int m = (int)(frac_d * 60.0);
    double s = (frac_d * 3600.0) - (m * 60.0);

    // Print result
    sprintf(msg, "DEC_E %s%d° %02d' %05.2f\"\n", (degrees < 0 ? "-" : ""), abs(d), m, s);
    UART2_putStr(msg);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Set_Select(uint8_t sel)
{
    SEL0 = (sel >> 0) & 1;
    SEL1 = (sel >> 1) & 1;
    SEL2 = (sel >> 2) & 1;

    // short settling delay (a few cycles)
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");
}

// ============================
// READ 8-BIT BUS
// ============================
uint8_t Read_EncoderBus(void)
{
    uint8_t value = 0;

    if (!PORTCbits.RC11) value |= (1 << 0);
    if (!PORTGbits.RG11) value |= (1 << 1);
    if (!PORTCbits.RC0)  value |= (1 << 2);
    if (!PORTFbits.RF13) value |= (1 << 3);
    if (!PORTFbits.RF12) value |= (1 << 4);
    if (!PORTDbits.RD14) value |= (1 << 5);
    if (!PORTDbits.RD15) value |= (1 << 6);
    if (!PORTEbits.RE15) value |= (1 << 7);

    return value;
}

// ============================
// READ 17-BIT ENCODER VALUE
// baseSelect = select base for that encoder (like 0 for ENC1, 4 for ENC2)
// ============================
uint32_t Read_17bit_Encoder(uint8_t baseSelect)
{
    uint8_t lowByte, highByte, bit17;
    uint32_t value = 0;
//    LED_2 ^= 1;
    
    
    // LSB
    Set_Select(baseSelect + 0);
//    UART2_putStr("LSB : ");
//    for(int i = 0; i< 18000000; i++)
//        Nop();
//    LED_2 ^= 1;
    lowByte = Read_EncoderBus();
    
    
    // MSB
    Set_Select(baseSelect + 1);
//    UART2_putStr("MSB : ");
//    for(int i = 0; i< 18000000; i++)
//        Nop();
//    LED_2 ^= 1;
    highByte = Read_EncoderBus();

    
    // 17th bit
    Set_Select(baseSelect + 3);
//    UART2_putStr("17TH : \n");
//    for(int i = 0; i< 18000000; i++)
//        Nop();
    bit17 = Read_EncoderBus() & 0x01; // assuming bit0 carries the single bit

    
    // Combine ? 17-bit result
    value = ((uint32_t)highByte << 8) | lowByte;
    value |= ((uint32_t)bit17 << 16);

    return value;
}

