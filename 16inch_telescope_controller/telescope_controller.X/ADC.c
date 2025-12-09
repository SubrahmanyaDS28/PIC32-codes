#include <xc.h>
#include <stdio.h>
#include "ADC.h"
#include "adc_common.h"
#include "uart2.h"

#define ADCHS_CHANNEL_32  (32U)

// *****************************************************************************
// *****************************************************************************
// Section: ADCHS Implementation
// *****************************************************************************
// *****************************************************************************




void ADCHS_Initialize(void)
{
    ADCCON1bits.ON = 0;

//    TRISCbits.TRISC11 = 1;
//    ANSELCbits.ANSC11 = 1;

    ADCCON1 = 0x600000U;
    ADCCON2 = 0x0U;
    ADCCON3 = 0x1000000U;

    ADCTRGMODE = 0x0U;

    ADCTRG1 = 0x0U; 
    ADCTRG2 = 0x0U; 
    ADCTRG3 = 0x0U; 
    ADCTRG4 = 0x0U; 
    ADCTRG5 = 0x0U; 
    ADCTRG6 = 0x0U; 
    ADCTRG7 = 0x0U; 

    ADCTRGSNS = 0x0U;

    ADCIMCON1 = 0x000000U;
    ADCIMCON2 = 0x0U; 
    ADCIMCON3 = 0x0U; 
    ADCIMCON4 = 0x0U; 

    ADCCSS1 = 0x0U;
    ADCCSS2 = 0x0U; 

    // Turn ON ADC
    ADCCON1bits.ON = 1;

    while(ADCCON2bits.BGVRRDY == 0U);
    while(ADCCON2bits.REFFLT != 0U);

    // ======== ENABLE ALL ADC CORES ========
    ADCANCONbits.ANEN0 = 1;
    ADCANCONbits.ANEN1 = 1;
    ADCANCONbits.ANEN2 = 1;
    ADCANCONbits.ANEN3 = 1;
    ADCANCONbits.ANEN4 = 1;
    ADCANCONbits.ANEN5 = 1;
    ADCANCONbits.ANEN7 = 1;

    while(!ADCANCONbits.WKRDY0);
    while(!ADCANCONbits.WKRDY1);
    while(!ADCANCONbits.WKRDY2);
    while(!ADCANCONbits.WKRDY3);
    while(!ADCANCONbits.WKRDY4);
    while(!ADCANCONbits.WKRDY5);
    while(!ADCANCONbits.WKRDY7);

    ADCCON3bits.DIGEN0 = 1;
    ADCCON3bits.DIGEN1 = 1;
    ADCCON3bits.DIGEN2 = 1;
    ADCCON3bits.DIGEN3 = 1;
    ADCCON3bits.DIGEN4 = 1;
    ADCCON3bits.DIGEN5 = 1;
    ADCCON3bits.DIGEN7 = 1;
    // =====================================

    ADCHS_ModulesEnable(ADCHS_MODULE0_MASK);
    ADCHS_ModulesEnable(ADCHS_MODULE1_MASK);
    ADCHS_ModulesEnable(ADCHS_MODULE2_MASK);
    ADCHS_ModulesEnable(ADCHS_MODULE3_MASK);
    ADCHS_ModulesEnable(ADCHS_MODULE4_MASK);
    ADCHS_ModulesEnable(ADCHS_MODULE5_MASK);
    ADCHS_ModulesEnable(ADCHS_MODULE7_MASK);
}



/* Enable ADCHS channels */
void ADCHS_ModulesEnable (ADCHS_MODULE_MASK moduleMask)
{
    ADCCON3 |= ((uint32_t)moduleMask << 16);
}

/* Disable ADCHS channels */
void ADCHS_ModulesDisable (ADCHS_MODULE_MASK moduleMask)
{
    ADCCON3 &= ~(((uint32_t)moduleMask << 16));
}


void ADCHS_ChannelResultInterruptEnable (ADCHS_CHANNEL_NUM channel)
{
    if (channel < ADCHS_CHANNEL_32)
    {
        ADCGIRQEN1 |= 0x01UL << channel;
    }
    else
    {
        ADCGIRQEN2 |= 0x01UL << (channel - 32U);
    }
}

void ADCHS_ChannelResultInterruptDisable (ADCHS_CHANNEL_NUM channel)
{
    if (channel < ADCHS_CHANNEL_32)
    {
        ADCGIRQEN1 &= ~(0x01UL << channel);
    }
    else
    {
        ADCGIRQEN2 &= ~(0x01UL << (channel - 32U));
    }
}

void ADCHS_ChannelEarlyInterruptEnable (ADCHS_CHANNEL_NUM channel)
{
    if (channel < ADCHS_CHANNEL_32)
    {
        ADCEIEN1 |= (0x01UL << channel);
    }
    else
    {
        ADCEIEN2 |= (0x01UL << (channel - 32U));
    }
}

void ADCHS_ChannelEarlyInterruptDisable (ADCHS_CHANNEL_NUM channel)
{
    if (channel < ADCHS_CHANNEL_32)
    {
        ADCEIEN1 &= ~(0x01UL << channel);
    }
    else
    {
        ADCEIEN2 &= ~(0x01UL << (channel - 32U));
    }
}

void ADCHS_GlobalEdgeConversionStart(void)
{
    ADCCON3bits.GSWTRG = 1;
}

void ADCHS_GlobalLevelConversionStart(void)
{
    ADCCON3bits.GLSWTRG = 1;
}

void ADCHS_GlobalLevelConversionStop(void)
{
    ADCCON3bits.GLSWTRG = 0;
}

void ADCHS_ChannelConversionStart(ADCHS_CHANNEL_NUM channel)
{
    ADCCON3bits.ADINSEL = (uint8_t)channel;
    ADCCON3bits.RQCNVRT = 1;
}


/*Check if conversion result is available */
bool ADCHS_ChannelResultIsReady(ADCHS_CHANNEL_NUM channel)
{
    bool status = false;
    if (channel < ADCHS_CHANNEL_32)
    {
        status = (((ADCDSTAT1 >> channel) & 0x01U) != 0U);
    }
    else
    {
        status = (((ADCDSTAT2 >> (channel - 32U)) & 0x01U) != 0U);
    }
    return status;
}

/* Read the conversion result */
uint16_t ADCHS_ChannelResultGet(ADCHS_CHANNEL_NUM channel)
{
    return (uint16_t)(*((&ADCDATA0) + (channel << 2)));

}





bool ADCHS_EOSStatusGet(void)
{
    return (bool)(ADCCON2bits.EOSRDY);
}


#define ADC_VREF        (3.3f)
#define ADC_MAX_COUNT   (4095.0f)
void Read_Focus_ADC(void){
    // Start conversion on AN11 (Channel 11)
    ADCHS_ChannelConversionStart(ADCHS_CH11);

    // Wait until the result is ready
    while (!ADCHS_ChannelResultIsReady(ADCHS_CH11));

    // Read conversion result (this will read from ADCDATA11)
    uint16_t rawValue = ADCHS_ChannelResultGet(ADCHS_CH11);
    
    float voltage = (rawValue * ADC_VREF) / ADC_MAX_COUNT;
    
    char msg[50];
    sprintf(msg, "ADC %f V\r\n", voltage);
    UART2_putStr(msg);
}