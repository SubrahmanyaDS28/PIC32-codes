#include <xc.h>
#include "initialize.h"
#include "constants.h"
#include "config.h"
//#include "extern.h"

void Init_GPIO(void) {


    TRISGbits.TRISG12 = 0; // LED_1
    TRISGbits.TRISG13 = 0; // LED_2
    TRISGbits.TRISG14 = 0; // LED_3

    TRISBbits.TRISB14 = 0; // RB14 has Direction1 output
    TRISDbits.TRISD1  = 0; // RD1 has Direction2 Output

    /* Unlock system for PPS configuration */
    SYSKEY = 0x00000000U;
    SYSKEY = 0xAA996655U;
    SYSKEY = 0x556699AAU;

    CFGCONbits.IOLOCK = 0U;

    /* PPS Input Remapping */
//    U1RXR = 12; // UART1 Rx using RF0
    U2RXR = 11; // UART2 Rx using RG0
    
//    INT2R = 8;   // INT2 is using RE14
    INT3R = 9;   // INT3 is using RD6 
    
    
//    INDX1R = 2;
////    HOME1R = 8; //E15 connected to home of QEI1
//    QEA1R = 2;  //B4 connected to A of QEI1
//    QEB1R = 5;  //A8 connected to B of QEI1
//      
//    
//    INDX2R = 12; //1100 e1
//    QEA2R = 6; //0110 c2
//    QEB2R = 6; //0110 c1
    

    /* PPS Output Remapping */

//    RPF1R = 1; // UART1 Tx using RPF1
    RPG1R = 2; // UART2 Tx using RPG1

    RPA7R = 6; // Re-programmable pin (RA7)connected to OC5 Output ////////////********(B12)*(OC8)*********//////////

    RPB15R = 5;// Re-programmable pin (RB15)connected to OC1 Output


    /* Lock back the system after PPS configuration */

    CFGCONbits.IOLOCK = 1U;

    SYSKEY = 0x00000000U;

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
    
    IPC14bits.U2RXIP = 3;
    IPC14bits.U2RXIS = 0;
    IPC14bits.U2TXIP = 1;
    IPC14bits.U2TXIS = 0;

    U2MODEbits.ON     = 1; // Enable UARTx Enable bits

}


void Init_Timer2(void) {

    
     T2CON = 0; // Timer reset

    T2CONbits.ON    = STOP; // Disable Timer2   
    T2CONbits.SIDL  = 0; // Disable Stop in Idle Mode bit
    T2CONbits.SYNC  = 0; // Disable Timer External Clock Input Synchronization Selection bit
    T2CONbits.TGATE = 0; // Disable Timer Gated Time Accumulation Enable bit
    T2CONbits.TCKPS = 6; // 1:64 pre-scale value
    T2CONbits.T32   = 0; // 32-bit Timer Mode Select bit
    T2CONbits.TCS   = 0; // Disable Timer Clock Source Select bit

    TMR2 = 0x0; // Timer2 Counter Clear

    PR2 = 37500; // SET Timer2 Period (100Hz)
//    PR2 = 0; // SET Timer2 Period (0Hz)

    //    IFS0bits.T2IF = 0;      // Reset Timer2 interrupt flag

    IEC0bits.T2IE = 1; // Disable Timer2_Interrupt

    IPC2bits.T2IP = 1;
    IPC2bits.T2IS = 0;
    //    IPC2SET = 0x400U | 0x0U;  /* TIMER_2:  Priority 1 / Subpriority 0 */

    T2CONbits.ON = START; // Timer2 STOP
}

//
//void Init_Timer3(void) {
//
//    T3CON = 0; // Timer reset
//
//    T3CONbits.ON    = STOP; // Disable Timer3 
//    T3CONbits.SIDL  = 0; // Disable Stop in Idle Mode bit
//    T3CONbits.SYNC  = 0; // Disable Timer External Clock Input Synchronization Selection bit
//    T3CONbits.TGATE = 0; // Disable Timer Gated Time Accumulation Enable bit
//    T3CONbits.TCKPS = 7; // 1:16 pre-scale value
//    T3CONbits.T32   = 0; // 32-bit Timer Mode Select bit
//    T3CONbits.TCS   = 0; // Disable Timer Clock Source Select bit
//
//    TMR3 = 0x0; // Timer3 Counter Clear
//
//    PR3 = 37500; // SET Timer3 Period (100Hz)
////    PR3 = 0; // SET Timer3 Period (0Hz)
//
//    IEC0bits.T3IE = 0; // Disable Timer2_Interrupt
//
//    T3CONbits.ON = START; // Timer3 STOP
//}

void Init_Timer3(void) {
    T3CON = 0;              // Stop timer and reset control register
    T3CONbits.TCKPS = 7;    // Set Prescaler to 1:256 (Matches your T3_PRESCALER define)
    T3CONbits.TCS = 0;      // Internal Peripheral Clock source
    T3CONbits.SIDL = 0;     // Continue operation in Idle mode
    
    TMR3 = 0;               // Clear the counter
    
    // Set Period to maximum (65535) to prevent premature resets.
    // This allows the timer to measure slow speeds without overflowing.
    PR3 = 0xFFFF;           

    // We do NOT enable T3IE (Timer 3 Interrupt) because you are using 
    // the INT3 External Interrupt to process the timer values.
    IPC3bits.T3IP = 0;      // Priority 0 (disabled)
    IEC0bits.T3IE = 0;      // Disable Timer 3 interrupt

    T3CONbits.ON = 1;       // Start Timer 3
}

void Init_OCMP5(void) {

    TRISAbits.TRISA7  = 0; // OCMP5 Output
//    ANSELAbits.ANSELA7 = 0;
    OC5CONbits.ON     = STOP; // Disable OCMP5 
    OC5CONbits.OCM    = 6; // Compare event toggles OCx pin
    OC5CONbits.OCTSEL = 0; // Output Compare Timer Select bit_Selected Timer2
    OC5CONbits.OC32   = 0; // 32-bit Compare Mode bit
    OC5CONbits.SIDL   = 0; // Disable Stop in Idle Mode bit

    OC5R = 1; // Compare value
//    OC5RS = 1; // Compare value

    OC5CONbits.ON = START; // Enable OCMP5
}

void Init_OCMP1(void) {

    TRISBbits.TRISB15 = 0; // OCMP5 Output

    OC1CONbits.ON     = STOP; // Disable OCMP1 
    OC1CONbits.OCM    = 6; // Compare event toggles OCx pin
    OC1CONbits.OCTSEL = 1; // Output Compare Timer Select bit_Selected Timer3
    OC1CONbits.OC32   = 0; // 32-bit Compare Mode bit
    OC1CONbits.SIDL   = 0; // Disable Stop in Idle Mode bit

    OC1R = 1; // Compare value


    OC1CONbits.ON = START; // Enable OCMP1
}


void Init_INT3_SlotSensor(void) {
    
    TRISDbits.TRISD6 = 1;  // Configure RD6 as a digital input pin for the slot sensor
    
    // Set the Edge Polarity for INT3
    // 1 = Trigger on Rising Edge (as specified in the report)
    // 0 = Trigger on Falling Edge
    INTCONbits.INT3EP = 1; 

    IPC4bits.INT3IP = 1; // Setting to Priority 1
    IPC4bits.INT3IS = 0; // Setting to Sub priority 0

    IFS0bits.INT3IF = 0; // Clear the INT3 Interrupt Flag so it doesn't trigger immediately

    IEC0bits.INT3IE = 1; // Enable the INT3 Interrupt
}


//
//void Init_QEI1 (void)
//{
//    TRISBbits.TRISB4 = 1;
//    TRISAbits.TRISA8 = 1;
//    TRISAbits.TRISA4 = 1;
//
////    ANSELBbits.ANSB4 = 0;
//    ANSELAbits.ANSA8 = 0;
//    ANSELAbits.ANSA4 = 0;
//   
//    QEI1CONbits.CCM   = 0;  // Disable Counter Control Mode Selection bits
//    QEI1CONbits.GATEN = 0;  // Disable External Count Gate Enable bit
//    QEI1CONbits.CNTPOL= 0;  // Disable Position, Velocity, and Index Counter/Timer Direction Select bit
//    QEI1CONbits.INTDIV= 0;  // 1:1 prescale value
//    QEI1CONbits.IMV   = 0;  // Index match occurs when QEB = 0 and QEA = 0
//    QEI1CONbits.PIMOD = 0;  // Index input event does not affect position counter
//    QEI1CONbits.QEISIDL=0;  // Continue module operation in Idle mode
//    
//
//    QEI1IOCbits.QEAPOL = 0;  // Disable QEAx Input Polarity Select bit
//    QEI1IOCbits.QEBPOL = 0;  // Disable QEBx Input Polarity Select bit
//    QEI1IOCbits.IDXPOL = 0;  // Disable INDXx Input Polarity Select bit
//    QEI1IOCbits.HOMPOL = 0;  // Disable HOMEx Input Polarity Select bit
//    QEI1IOCbits.SWPAB  = 0;  // Disable Swap QEA and QEB Inputs bit
//    QEI1IOCbits.OUTFNC = 3;  // The CNTCMPx pin goes high when POSxCNT ? QEIxLEC or POSxCNT ? QEIxGEC
//    QEI1IOCbits.QFDIV  = 0;  // QEA/QEB/INDX/HOMEx Digital Input Filter Clock Divide Select bits
//    QEI1IOCbits.FLTREN = 0;  // QEA/QEB/INDX/HOMEx Digital Filter Enable bit
//     
////     
//    QEI1ICC = 40000U;           // QEI1 Low Compare value
//    QEI1CMPL = 0U;          // QEI1 High Compare value
//    
//    POS1CNT = 0;
////    MAX1CNT = 0xFFFF;       // 16-bit max
////    QEI1ICC  = 0xFFFF;      // disable compare reset
//    QEI1CMPL = 0;
//
//    QEI1STATbits.PCHEQIEN  = 1;  // Enable Position Counter Greater Than or Equal Compare Interrupt Enable bit
//    QEI1STATbits.PCLEQIEN  = 0;  // Disable Position Counter Less Than or Equal Compare Status bit
//    QEI1STATbits.POSOVIEN  = 0;  // Disable Position Counter Overflow Interrupt Enable bit
//    QEI1STATbits.PCIIEN    = 0;  // Disable Position Counter (Homing) Initialization Process Complete Interrupt Enable bit 
//    QEI1STATbits.VELOVIEN  = 0;  // Disable Velocity Counter Overflow Interrupt Enable bit
//    QEI1STATbits.HOMIEN    = 0;  // Disable Home Input Event Interrupt Enable bit
//    QEI1STATbits.IDXIEN    = 0;  // Disable Index Input Event Interrupt Enable bit
//    
//    QEI1STATbits.PCHEQIRQ  = 0;  // Disable Position Counter Greater Than or Equal Compare Status 
//    QEI1STATbits.PCLEQIRQ  = 0;  // Disable Position Counter Greater Than or Equal Compare Interrupt Enable bit
//    QEI1STATbits.POSOVIRQ  = 0;  // Disable Position Counter Less Than or Equal Compare Status bit
//    QEI1STATbits.PCIIRQ    = 0;  // Disable Position Counter (Homing) Initialization Process Complete Status bit
//    QEI1STATbits.VELOVIRQ  = 0;  // Disable Velocity Counter Overflow Status bit
//    QEI1STATbits.HOMIRQ    = 0;  // Disable Status Flag for Home Event Status bit
//    QEI1STATbits.IDXIRQ    = 0;  // Disable Status Flag for Index Event Status bit
//    
//    IEC5SET = _IEC5_QEI1IE_MASK;
//    
//     
//    IPC42SET = 0x400U | 0x0U;   /* QEI1:  Priority 1 / Subpriority 0 */
//    
//    QEI1CONbits.QEIEN = 1;       // QEI1 START
//}
//
//
//void Init_QEI2 (void)
//{
//    
//    TRISCbits.TRISC2 = 1;
//    TRISCbits.TRISC1 = 1;
//    TRISEbits.TRISE1 = 1;
//
//    ANSELCbits.ANSC2 = 0;
//    ANSELCbits.ANSC1 = 0;
//    ANSELEbits.ANSE1 = 0;
//   
//    QEI2CONbits.CCM   = 0;  // Disable Counter Control Mode Selection bits
//    QEI2CONbits.GATEN = 0;  // Disable External Count Gate Enable bit
//    QEI2CONbits.CNTPOL= 0;  // Disable Position, Velocity, and Index Counter/Timer Direction Select bit
//    QEI2CONbits.INTDIV= 0;  // 1:1 prescale value
//    QEI2CONbits.IMV   = 0;  // Index match occurs when QEB = 0 and QEA = 0
//    QEI2CONbits.PIMOD = 0;  // Index input event does not affect position counter
//    QEI2CONbits.QEISIDL=0;  // Continue module operation in Idle mode
//    
//
//    QEI2IOCbits.QEAPOL = 0;  // Disable QEAx Input Polarity Select bit
//    QEI2IOCbits.QEBPOL = 0;  // Disable QEBx Input Polarity Select bit
//    QEI2IOCbits.IDXPOL = 0;  // Disable INDXx Input Polarity Select bit
//    QEI2IOCbits.HOMPOL = 0;  // Disable HOMEx Input Polarity Select bit
//    QEI2IOCbits.SWPAB  = 0;  // Disable Swap QEA and QEB Inputs bit
//    QEI2IOCbits.OUTFNC = 3;  // The CNTCMPx pin goes high when POSxCNT ? QEIxLEC or POSxCNT ? QEIxGEC
//    QEI2IOCbits.QFDIV  = 0;  // QEA/QEB/INDX/HOMEx Digital Input Filter Clock Divide Select bits
//    QEI2IOCbits.FLTREN = 0;  // QEA/QEB/INDX/HOMEx Digital Filter Enable bit
//     
//     
////     
//    QEI2ICC = 10000U;           // QEI1 Low Compare value
//    QEI2CMPL = 0U;          // QEI1 High Compare value
//    
//    POS2CNT = 0;
////    MAX2CNT = 0xFFFF;       // 16-bit max
////    QEI2ICC  = 0xFFFF;      // disable compare reset
//    QEI2CMPL = 0;
//
//    QEI2STATbits.PCHEQIEN  = 1;  // Enable Position Counter Greater Than or Equal Compare Interrupt Enable bit
//    QEI2STATbits.PCLEQIEN  = 0;  // Disable Position Counter Less Than or Equal Compare Status bit
//    QEI2STATbits.POSOVIEN  = 0;  // Disable Position Counter Overflow Interrupt Enable bit
//    QEI2STATbits.PCIIEN    = 0;  // Disable Position Counter (Homing) Initialization Process Complete Interrupt Enable bit 
//    QEI2STATbits.VELOVIEN  = 0;  // Disable Velocity Counter Overflow Interrupt Enable bit
//    QEI2STATbits.HOMIEN    = 0;  // Disable Home Input Event Interrupt Enable bit
//    QEI2STATbits.IDXIEN    = 0;  // Disable Index Input Event Interrupt Enable bit
//    
//    QEI2STATbits.PCHEQIRQ  = 0;  // Disable Position Counter Greater Than or Equal Compare Status 
//    QEI2STATbits.PCLEQIRQ  = 0;  // Disable Position Counter Greater Than or Equal Compare Interrupt Enable bit
//    QEI2STATbits.POSOVIRQ  = 0;  // Disable Position Counter Less Than or Equal Compare Status bit
//    QEI2STATbits.PCIIRQ    = 0;  // Disable Position Counter (Homing) Initialization Process Complete Status bit
//    QEI2STATbits.VELOVIRQ  = 0;  // Disable Velocity Counter Overflow Status bit
//    QEI2STATbits.HOMIRQ    = 0;  // Disable Status Flag for Home Event Status bit
//    QEI2STATbits.IDXIRQ    = 0;  // Disable Status Flag for Index Event Status bit
//    
//    IEC5SET = _IEC5_QEI2IE_MASK;
//    
//     
////    IPC42SET = 0x400U | 0x0U;   /* QEI1:  Priority 1 / Subpriority 0 */
//    IPC42bits.QEI2IP = 1;
//    IPC42bits.QEI2IS = 0;
//    
//    QEI2CONbits.QEIEN = 1;       // QEI1 START
//    
//}



//void Encoder_Inputs_Init(void)
//{
//    // 8-bit parallel data bus (shared between encoders)
//    TRISCbits.TRISC11 = 1;
//    TRISGbits.TRISG11 = 1;
//    TRISCbits.TRISC0  = 1;
//    TRISFbits.TRISF13 = 1;
//    TRISFbits.TRISF12 = 1;
//    TRISDbits.TRISD14 = 1;
//    TRISDbits.TRISD15 = 1;
//    TRISEbits.TRISE15 = 1;
//
//    
//    ANSELCbits.ANSC11 = 0;
//    ANSELGbits.ANSG11 = 0;
//    ANSELCbits.ANSC0  = 0;
//    ANSELFbits.ANSF13 = 0;
//    ANSELFbits.ANSF12 = 0;
//    ANSELDbits.ANSD14 = 0;
//    ANSELDbits.ANSD15 = 0;
//    ANSELEbits.ANSE15 = 0;
//
//    // Enable internal pull-ups where supported
//    CNPUCbits.CNPUC11 = 1;
//    CNPUGbits.CNPUG11 = 1;
//    CNPUCbits.CNPUC0  = 1;
//    CNPUFbits.CNPUF13 = 1;
//    CNPUFbits.CNPUF12 = 1;
//    CNPUDbits.CNPUD14 = 1;
//    CNPUDbits.CNPUD15 = 1;
//    CNPUEbits.CNPUE15 = 1;
//    
//    
//    // Enable CN
////    CNENCbits.CNIEC11 = 1;
////    CNENGbits.CNIEG11 = 1;
////    CNENCbits.CNIEC0  = 1;
////    CNENFbits.CNIEF13 = 1;
////    CNENFbits.CNIEF12 = 1;
////    CNENDbits.CNIED14 = 1;
////    CNENDbits.CNIED15 = 1;
////    CNENEbits.CNIEE15 = 1;
//}
//
//void Encoder_Select_Init(void)
//{
//    TRISDbits.TRISD8 = 0;
//    TRISBbits.TRISB5 = 0;
//    TRISBbits.TRISB6 = 0;
//
//    SEL0 = 0;
//    SEL1 = 0;
//    SEL2 = 0;
//}

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
    PMD4bits.T2MD    = 0; // Timer_2
    PMD4bits.T3MD    = 0; // Timer_3
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
    PMD5bits.SPI3MD  = 1; // SPI_3
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

    Init_Timer2();

    Init_Timer3();

    Init_OCMP5();

    Init_OCMP1();
    
    Init_INT3_SlotSensor();
            
    Init_UART2();
    
    Init_EVIC();

    /* Enable global interrupts */
    (void) __builtin_enable_interrupts();

}

