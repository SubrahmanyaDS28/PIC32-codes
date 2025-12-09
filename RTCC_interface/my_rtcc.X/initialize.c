#include <xc.h>
#include "initialize.h"
//#include "constants.h"
//#include "config.h"
//#include "extern.h"

void Init_GPIO(void) {


    TRISGbits.TRISG12 = 0; // LED_1
    TRISGbits.TRISG13 = 0; // LED_2
    TRISGbits.TRISG14 = 0; // LED_3


    /* Unlock system for PPS configuration */
    SYSKEY = 0x00000000U;
    SYSKEY = 0xAA996655U;
    SYSKEY = 0x556699AAU;

    CFGCONbits.IOLOCK = 0U;

    /* PPS Input Remapping */
//    U1RXR = 12; // UART1 Rx using RF0
    U2RXR = 11; // UART2 Rx using RG0
    
//    SDI1R = 5; // SDI1 to C7
    
    SDI3R = 9; // SDI3 to D5
    SCK3R = 3 ; // SCK3 to B10
    SS3R = 0; // CS3 to B6
    /* PPS Output Remapping */

//    RPF1R = 1; // UART1 Tx using RPF1
    RPG1R = 2; // UART2 Tx using RPG1
    
//    RPC15R = 3; //CS1 to C15
//    RPA15R = 3; //SDO1 to A15
    
//    RPB6R = 14; //CS3 to B6
    RPC0R = 14; //SDO3 to C0 
//    RPB10R = 14; //SCK3 to B10
    //for SCK1 no need to do PPS it is always connected to B7(72)

    /* Lock back the system after PPS configuration */

    CFGCONbits.IOLOCK = 1U;

    SYSKEY = 0x00000000U;

}

void Init_UART1(void) {

    TRISFbits.TRISF1 = 0; // UART1 TX
    TRISFbits.TRISF0 = 1; // UART1 RX      


    /* Set up UxMODE bits */

    U1MODEbits.STSEL  = 0; // Disable Stop Selection bit
    U1MODEbits.PDSEL  = 0; // Disable Parity and Data Selection bits
    U1MODEbits.BRGH   = 1; // Enable High Baud Rate Enable bit
    U1MODEbits.RXINV  = 0; // Disable Receive Polarity Inversion bit
    U1MODEbits.ABAUD  = 0; // Disable Auto-Baud Enable bit
    U1MODEbits.LPBACK = 0; // Disable UARTx Loopback Mode Select bit
    U1MODEbits.WAKE   = 0; // Disable Wake-up on Start bit Detect During Sleep Mode bit
    U1MODEbits.SIDL   = 0; // Disable Stop in Idle Mode bit
    U1MODEbits.RUNOVF = 0; // Disable Run During Overflow Condition Mode bit    
    U1MODEbits.CLKSEL = 0; // Disable UARTx Module BRG Clock Selection bits
    U1MODEbits.SLPEN  = 0; // Disable Run During Sleep Enable bit
    U1MODEbits.UEN    = 0b00; // Disable UARTx Enable bits

    U1STAbits.UTXEN   = 1;
    U1STAbits.URXEN   = 1;
    U1STAbits.UTXISEL = 0b00;
    U1STAbits.URXISEL = 0b00;
    U1BRG             = 129; // BAUD Rate register Setup (115200)

    IEC1bits.U1EIE    = 0; // Error Interrupt Enable Control bit
    IEC1bits.U1TXIE   = 0; // Transmit Interrupt Enable Control bit

    IEC1bits.U1RXIE   = 1; // Enable UART1_RX Interrupt

    IPC9SET = 0x4000000U | 0x0U; /* UART1_RX:  Priority 1 / Subpriority 0 */
    IPC10SET = 0x4U | 0x0U; /* UART1_TX:  Priority 1 / Subpriority 0 */
    
    U1MODEbits.ON     = 1; // Enable UARTx Enable bits

}


void Init_UART2(void) {

    TRISGbits.TRISG1 = 0; // UART2 TX
    TRISGbits.TRISG0 = 1; // UART2 RX      


    /* Set up UxMODE bits */

    U2MODEbits.STSEL  = 0; // Disable Stop Selection bit
    U2MODEbits.PDSEL  = 0; // Disable Parity and Data Selection bits
    U2MODEbits.BRGH   = 1; // Enable High Baud Rate Enable bit
    U2MODEbits.RXINV  = 0; // Disable Receive Polarity Inversion bit
    U2MODEbits.ABAUD  = 0; // Disable Auto-Baud Enable bit
    U2MODEbits.LPBACK = 0; // Disable UARTx Loopback Mode Select bit
    U2MODEbits.WAKE   = 0; // Disable Wake-up on Start bit Detect During Sleep Mode bit
    U2MODEbits.SIDL   = 0; // Disable Stop in Idle Mode bit
    U2MODEbits.RUNOVF = 0; // Disable Run During Overflow Condition Mode bit    
    U2MODEbits.CLKSEL = 0; // Disable UARTx Module BRG Clock Selection bits
    U2MODEbits.SLPEN  = 0; // Disable Run During Sleep Enable bit
    U2MODEbits.UEN    = 0b00; // Disable UARTx Enable bits

    U2STAbits.UTXEN   = 1;
    U2STAbits.URXEN   = 1;
    U2STAbits.UTXISEL = 0b00;
    U2STAbits.URXISEL = 0b00;
    U2BRG             = 129; // BAUD Rate register Setup (115200)

    IEC1bits.U2EIE    = 0; // Error Interrupt Enable Control bit
    IEC1bits.U2TXIE   = 0; // Transmit Interrupt Enable Control bit

    IEC1bits.U2RXIE   = 1; // Enable UART1_RX Interrupt

//    IPC9SET = 0x4000000U | 0x0U; /* UART1_RX:  Priority 1 / Subpriority 0 */
//    IPC10SET = 0x4U | 0x0U; /* UART1_TX:  Priority 1 / Subpriority 0 */
    
    IPC14bits.U2RXIP = 1;
    IPC14bits.U2TXIP = 1;

    U2MODEbits.ON     = 1; // Enable UARTx Enable bits

}


void RTCC_Init_Internal(void)
{
    // Unlock sequence
    SYSKEY = 0x0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    RTCCONbits.ON = 0;         // Disable RTCC to configure
    RTCCONbits.RTCCLKSEL = 0b00; // Use LPRC
    RTCCONbits.RTCWREN = 1;    // Allow writes

    // Set initial time/date (BCD)
    // Format: RTCTIME = 0xHHMMSS00;  RTCDATE = 0xYYMMDDWW;
    RTCTIME = 0x23590000;      // 16:00:00
    RTCDATE = 0x25101604;      // 2025/10/15 (Wed)

    RTCCONbits.ON = 1;         // Enable RTCC

    SYSKEY = 0x0;              // Lock back
}

void RTCC_AlarmInit(void)
{
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
    RTCALRMbits.AMASK = 0b0011; // Every minute
    RTCALRMbits.ARPT = 0xFF;    // Repeat 256 times before rolling
    RTCALRMbits.PIV = 0;        // Alarm pulse initial value
    RTCALRMbits.ALRMEN = 1;     // Enable alarm

    // Enable interrupt
    IFS0CLR = _IFS0_RTCCIF_MASK;
    IEC0SET = _IEC0_RTCCIE_MASK;
    IPC7bits.RTCCIP = 3;

    SYSKEY = 0x0; // Lock
}


/*-----DO NOT MODIFY----*/
void Init_EVIC(void) {
    INTCONSET = _INTCON_MVEC_MASK;

    /* Configure Shadow Register Set */
    PRISS = 0x76543210;


    while (PRISS != 0x76543210U) {
        /* Wait for PRISS value to take effect */
    }

}

void Init_Clocks(void) {

    /* unlock system for clock configuration */
    SYSKEY = 0x00000000U;
    SYSKEY = 0xAA996655U;
    SYSKEY = 0x556699AAU;

    /* Peripheral Module Disable Configuration */


    CFGCONbits.PMDLOCK = 0;

    //    PMD1 = 0x371U;
    PMD1bits.ADCMD  = 1; // ADC1-ADC7
    PMD1bits.DAC1MD = 1; // CDAC_1
    PMD1bits.DAC2MD = 1; // CDAC_2    
    PMD1bits.CTMUMD = 1; // CTMU
    PMD1bits.EEMD   = 1; // Data EEPROM
    PMD1bits.DAC3MD = 1; // CDAC_3

    //    PMD2 = 0x17001fU;
    PMD2bits.CMP1MD = 1; // Comparator_1
    PMD2bits.CMP2MD = 1; // Comparator_2
    PMD2bits.CMP4MD = 1; // Comparator_4
    PMD2bits.CMP5MD = 1; // Comparator_5
    PMD2bits.OPA1MD = 1; // Op amp_1
    PMD2bits.OPA2MD = 1; // Op amp_2
    PMD2bits.OPA3MD = 1; // Op amp_3
    PMD2bits.OPA5MD = 1; // Op amp_4
    PMD2bits.CMP3MD = 1; // Comparator_3


    //    PMD3 = 0xfffffU;
    PMD3bits.IC10MD = 1; // Input Capture_10
    PMD3bits.IC11MD = 1; // Input Capture_11
    PMD3bits.IC12MD = 1; // Input Capture_12
    PMD3bits.IC13MD = 1; // Input Capture_13
    PMD3bits.IC14MD = 1; // Input Capture_14
    PMD3bits.IC15MD = 1; // Input Capture_15
    PMD3bits.IC16MD = 1; // Input Capture_16
    PMD3bits.IC1MD  = 1; // Input Capture_1
    PMD3bits.IC2MD  = 1; // Input Capture_2
    PMD3bits.IC3MD  = 1; // Input Capture_3
    PMD3bits.IC4MD  = 1; // Input Capture_4
    PMD3bits.IC5MD  = 1; // Input Capture_5
    PMD3bits.IC6MD  = 1; // Input Capture_6
    PMD3bits.IC7MD  = 1; // Input Capture_7
    PMD3bits.IC8MD  = 1; // Input Capture_8
    PMD3bits.IC9MD  = 1; // Input Capture_9
    PMD3bits.OC10MD = 1; // Output Compare_10
    PMD3bits.OC11MD = 1; // Output Compare_11
    PMD3bits.OC12MD = 1; // Output Compare_12
    PMD3bits.OC13MD = 1; // Output Compare_13
    PMD3bits.OC14MD = 1; // Output Compare_14
    PMD3bits.OC15MD = 1; // Output Compare_15
    PMD3bits.OC16MD = 1; // Output Compare_16
    PMD3bits.OC1MD  = 0; // Output Compare_1
    PMD3bits.OC2MD  = 1; // Output Compare_2
    PMD3bits.OC3MD  = 1; // Output Compare_3
    PMD3bits.OC4MD  = 1; // Output Compare_4
    PMD3bits.OC5MD  = 0; // Output Compare_5
    PMD3bits.OC6MD  = 1; // Output Compare_6
    PMD3bits.OC7MD  = 1; // Output Compare_7
    PMD3bits.OC8MD  = 1; // Output Compare_8
    PMD3bits.OC9MD  = 1; // Output Compare_9


    //    PMD4 = 0xfff01ffU;
    PMD4bits.PWM10MD = 1; // PWM_10
    PMD4bits.PWM11MD = 1; // PWM_11    
    PMD4bits.PWM12MD = 1; // PWM_12
    PMD4bits.PWM1MD  = 1; // PWM_1
    PMD4bits.PWM2MD  = 1; // PWM_2
    PMD4bits.PWM3MD  = 1; // PWM_3
    PMD4bits.PWM4MD  = 1; // PWM_4
    PMD4bits.PWM5MD  = 1; // PWM_5
    PMD4bits.PWM6MD  = 1; // PWM_6
    PMD4bits.PWM7MD  = 1; // PWM_7
    PMD4bits.PWM8MD  = 1; // PWM_8
    PMD4bits.PWM9MD  = 1; // PWM_9
    PMD4bits.T1MD    = 1; // Timer_1
    PMD4bits.T2MD    = 1; // Timer_2
    PMD4bits.T3MD    = 1; // Timer_3
    PMD4bits.T4MD    = 1; // Timer_4
    PMD4bits.T5MD    = 1; // Timer_5
    PMD4bits.T6MD    = 1; // Timer_6
    PMD4bits.T7MD    = 1; // Timer_7
    PMD4bits.T8MD    = 1; // Timer_8
    PMD4bits.T9MD    = 1; // Timer_9


    //    PMD5 = 0xf30f3f3bU;
    PMD5bits.CAN1MD  = 1; // CAN_1
    PMD5bits.CAN2MD  = 1; // CAN_2
    PMD5bits.CAN3MD  = 1; // CAN_3
    PMD5bits.CAN4MD  = 1; // CAN_4
    PMD5bits.I2C1MD  = 1; // I2C_1
    PMD5bits.I2C2MD  = 1; // I2C_2
    PMD5bits.I2C3MD  = 1; // I2C_3
    PMD5bits.I2C4MD  = 1; // I2C_4
    PMD5bits.SPI1MD  = 1; // SPI_1
    PMD5bits.SPI2MD  = 1; // SPI_2
    PMD5bits.SPI3MD  = 0; // SPI_3
    PMD5bits.SPI4MD  = 1; // SPI_4
    PMD5bits.SPI5MD  = 1; // SPI_5
    PMD5bits.SPI6MD  = 1; // SPI_6
    PMD5bits.U1MD    = 1; // UART_1
    PMD5bits.U2MD    = 0; // UART_2
    PMD5bits.U4MD    = 1; // UART_4
    PMD5bits.U5MD    = 1; // UART_5
    PMD5bits.U6MD    = 1; // UART_6
    PMD5bits.USB1MD  = 1; // USB_1
    PMD5bits.USB2MD  = 1; // USB_2
    PMD5bits.U3MD    = 1; // UART_3

    //    PMD6 = 0xf0d0000U;

    PMD6bits.PMPMD   = 1; // Parallel Master Port
    PMD6bits.QEI1MD  = 1; // QEI_1
    PMD6bits.QEI2MD  = 1; // QEI_2
    PMD6bits.QEI3MD  = 1; // QEI_3
    PMD6bits.QEI4MD  = 1; // QEI_4 
    PMD6bits.QEI5MD  = 1; // QEI_5
    PMD6bits.QEI6MD  = 1; // QRI_6
    PMD6bits.REFO1MD = 0; // Reference Clock_1
    PMD6bits.REFO2MD = 0; // Reference Clock_2
    PMD6bits.REFO3MD = 0; // Reference Clock_3
    PMD6bits.REFO4MD = 0; // Reference Clock_4

    //    PMD7 = 0x0U;
    PMD7bits.DMAMD   = 0; // DMA 


    CFGCONbits.PMDLOCK = 1;

    /* Lock system since done with clock configuration */
    SYSKEY = 0x33333333U;
}




void Init_SYS(void* data) {

    /* Start out with interrupts disabled before configuring any modules */
    (void) __builtin_disable_interrupts();


    Init_Clocks();

    /* Configure CP0.K0 for optimal performance (cached instruction pre-fetch) */
    __builtin_mtc0(16, 0, (__builtin_mfc0(16, 0) | 0x3U));

    /* Configure Wait States and Prefetch */
    CHECONbits.PFMWS = 2;
    CHECONbits.PREFEN = 1;

    Init_GPIO();

//    Init_UART1();
    Init_UART2();

    Init_EVIC();
    
    RTCC_Init_Internal();    /* Enable global interrupts */
    
    RTCC_AlarmInit();
            
    (void) __builtin_enable_interrupts();

}

