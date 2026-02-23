#include <xc.h>
#include "initialize.h"
#include "constants.h"
#include "config.h"
#include "extern.h"


void Init_GPIO(void) {
   
 
   TRISGbits.TRISG12 = 0;    // LED_1
   TRISGbits.TRISG13 = 0;    // LED_2
   TRISGbits.TRISG14 = 0;    // LED_3
   
  
   TRISBbits.TRISB14 = 0; // RB14 has Direction1 output for Motor A
   TRISDbits.TRISD1  = 0; // RD1 has Direction2 output for Motor B
//   TRISGbits.TRISG11 = 0;
//   ANSELGbits.ANSG11 = 0;
   TRISBbits.TRISB13 = 0; // RB13 has Direction3 output for Motor C
   TRISFbits.TRISF7  = 0; // RF7 has Direction4 output for Motor D
   

   TRISAbits.TRISA7 = 0; // RA7 is used as PULSE OUT for MOTOR A
   TRISBbits.TRISB15 = 0; // RB15 is used as PULSE_OUT for MOTOR B
//   TRISCbits.TRISC11 = 0;
   ANSELCbits.ANSC11 = 0;
   TRISBbits.TRISB12 = 0; // RB12 is used as PULSE_OUT for MOTOR C
   TRISFbits.TRISF6  = 0; // RF7 is used as  PULSE_OUT for MOTOR D
  
   
  
    /* Unlock system for PPS configuration */
    SYSKEY = 0x00000000U;
    SYSKEY = 0xAA996655U;
    SYSKEY = 0x556699AAU;

    CFGCONbits.IOLOCK = 0U;

    /* PPS Input Remapping */
    U1RXR = 12;  // UART1 Rx using RF0
    INT2R = 8;   // INT2 is using RE14
    INT3R = 9;   // INT3 is using RD6 
    INT4R = 9;   // INT4 is using RD5
    INT1R = 5;   // INT1 is using RC9
      

    /* PPS Output Remapping */
    RPF1R = 1;     // UART1 Tx using RPF1
    
    /* Lock back the system after PPS configuration */
    
    CFGCONbits.IOLOCK = 1U;

    SYSKEY = 0x00000000U;

}
void Init_Limit_Switch_A (void){
      
  
   TRISDbits.TRISD6  = 1;   // RD6 used as External 3 interrupt
 
   
   INTCONbits.INT3EP = 1;  // Interrupt on falling edge for INT0 (RB0)
   IFS0bits.INT3IF = 0;    // Clear INT0 flag
   IEC0bits.INT3IE = 1;    // Enable INT0 interrupt
   
   IPC4SET = 0x40000U | 0x0U;  /* EXTERNAL_3:  Priority 1 / Subpriority 0 */
   IEC0bits.INT3IE = 1;      // Enable INT3 Interrupt
}

void Init_Limit_Switch_B (void){
    
   TRISEbits.TRISE14 = 1;   // RE14 used as External 2 interrupt
   ANSELEbits.ANSE14 = 0;  //  RE14 is used as Digital pin
   
    INTCONbits.INT2EP = 1;  // Interrupt on falling edge for INT2 (RE14)
    IFS0bits.INT2IF = 0;    // Clear INT1 flag
    
    IPC3SET = 0x400U | 0x0U;  /* EXTERNAL_2:  Priority 1 / Subpriority 0 */
    
    IEC0bits.INT2IE = 1;      // Enable INT2 Interrupt
  
}


void Init_Limit_Switch_C (void){
    
   TRISCbits.TRISC9 = 1;   // RC9 used as External 1 interrupt
   
    INTCONbits.INT1EP = 1;  // Interrupt on falling edge for INT2 (RE14)
    IFS0bits.INT1IF = 0;    // Clear INT1 flag
    
    IPC2SET = 0x4U | 0x0U;  /* EXTERNAL_1:  Priority 1 / Subpriority 0 */
    
    IEC0bits.INT1IE = 1;      // Enable INT1 Interrupt
  
}

void Init_Limit_Switch_D (void){
    
   TRISDbits.TRISD5 = 1;   // RD5 used as External 4 interrupt
   
    INTCONbits.INT3EP = 1;  // Interrupt on falling edge for INT2 (RE14)
    IFS0bits.INT3IF = 0;    // Clear INT1 flag
    
    IPC5SET = 0x4000000U | 0x0U;  /* EXTERNAL_4:  Priority 1 / Subpriority 0 */
    
    IEC0bits.INT4IE = 1;      // Enable INT2 Interrupt
  
}


   

void Init_UART1(void) {

    TRISFbits.TRISF1  = 0;  // UART1 TX
    TRISFbits.TRISF0  = 1;  // UART1 RX      

    
    /* Set up UxMODE bits */
 
    U1MODEbits.STSEL = 0;    // Disable Stop Selection bit
    U1MODEbits.PDSEL = 0;    // Disable Parity and Data Selection bits
    U1MODEbits.BRGH  = 1;    // Enable High Baud Rate Enable bit
    U1MODEbits.RXINV = 0;    // Disable Receive Polarity Inversion bit
    U1MODEbits.ABAUD = 0;    // Disable Auto-Baud Enable bit
    U1MODEbits.LPBACK= 0;    // Disable UARTx Loopback Mode Select bit
    U1MODEbits.WAKE  = 0;    // Disable Wake-up on Start bit Detect During Sleep Mode bit
    U1MODEbits.SIDL  = 0;    // Disable Stop in Idle Mode bit
    U1MODEbits.RUNOVF= 0;    // Disable Run During Overflow Condition Mode bit    
    U1MODEbits.CLKSEL= 0;    // Disable UARTx Module BRG Clock Selection bits
    U1MODEbits.SLPEN = 0;    // Disable Run During Sleep Enable bit
    U1MODEbits.UEN   = 0b00; // Disable UARTx Enable bits
      
    
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1STAbits.UTXISEL = 0b00;
    U1STAbits.URXISEL = 0b00;
    U1BRG = 129;                // BAUD Rate register Setup (115200)
    
    IEC1bits.U1EIE  = 0;        // Error Interrupt Enable Control bit
    IEC1bits.U1TXIE = 0;        // Transmit Interrupt Enable Control bit

    IEC1bits.U1RXIE = 1;         // Enable UART1_RX Interrupt
    
    
    IPC9SET = 0x4000000U | 0x0U;  /* UART1_RX:  Priority 1 / Subpriority 0 */
    IPC10SET = 0x4U | 0x0U;  /* UART1_TX:  Priority 1 / Subpriority 0 */
   
    
    U1MODEbits.ON   = 1;         // Enable UARTx Enable bits

}


void Init_Timer2(void) {
    
    T2CON = 0;              // Timer reset
    
    T2CONbits.ON = STOP;    // Disable Timer2   
    T2CONbits.SIDL  = 0;    // Disable Stop in Idle Mode bit
    T2CONbits.SYNC  = 0;    // Disable Timer External Clock Input Synchronization Selection bit
    T2CONbits.TGATE = 0;    // Disable Timer Gated Time Accumulation Enable bit
    T2CONbits.TCKPS = 5;    // 1:8 pre-scale value
    T2CONbits.T32   = 1;    // 32-bit Timer Mode Select bit
    T2CONbits.TCS   = 0;    // Disable Timer Clock Source Select bit
   
    TMR2 = 0x0;             // Timer2 Counter Clear
  
    PR2 = 2000;            // SET Timer2 Period (25Hz)37500
    
    IFS0bits.T2IF = 0;   
    
    IEC0bits.T2IE = 1;      // Disable Timer2_Interrupt
    
    IPC2SET = 0x400U | 0x0U;  /* TIMER_2:  Priority 1 / Subpriority 0 */

     
    T2CONbits.ON = STOP;   // Timer2 STOP
}


void Init_Timer3(void) {

    T3CON = 0; // Timer reset

    T3CONbits.ON    = STOP; // Disable Timer3 
    T3CONbits.SIDL  = 0; // Disable Stop in Idle Mode bit
    T3CONbits.SYNC  = 0; // Disable Timer External Clock Input Synchronization Selection bit
    T3CONbits.TGATE = 0; // Disable Timer Gated Time Accumulation Enable bit
    T3CONbits.TCKPS = 5; // 1:32 pre-scale value
    T3CONbits.T32   = 0; // 32-bit Timer Mode Select bit
    T3CONbits.TCS   = 0; // Disable Timer Clock Source Select bit

    TMR3 = 0x0; // Timer3 Counter Clear

    PR3 = 2000; // SET Timer3 Period (25Hz)
    
    IFS0bits.T3IF = 0;
    
    IEC0bits.T3IE = 1; // Enable Timer3_Interrupt
    
    IPC3SET = 0x40000U | 0x0U;  /* TIMER_3:  Priority 1 / Subpriority 0 */
    
    T3CONbits.ON = STOP; // Timer3 STOP
}

void Init_Timer4(void) {
    
    T4CON = 0;              // Timer reset
    
    T4CONbits.ON = STOP;    // Disable Timer4   
    T4CONbits.SIDL  = 0;    // Disable Stop in Idle Mode bit
    T4CONbits.SYNC  = 0;    // Disable Timer External Clock Input Synchronization Selection bit
    T4CONbits.TGATE = 0;    // Disable Timer Gated Time Accumulation Enable bit
    T4CONbits.TCKPS = 5;    // 1:8 pre-scale value
    T4CONbits.T32   = 1;    // 32-bit Timer Mode Select bit
    T4CONbits.TCS   = 0;    // Disable Timer Clock Source Select bit
   
    TMR4 = 0x0;             // Timer4 Counter Clear
  
    PR4 = 2000;            // SET Timer4 Period (25Hz)37500
    
    IFS0bits.T4IF = 0;   
    
    IEC0bits.T4IE = 1;      // Disable Timer2_Interrupt
    
    IPC4SET = 0x4000000U | 0x0U;  /* TIMER_4:  Priority 1 / Subpriority 0 */
 
    T4CONbits.ON = STOP;   // Timer2 STOP
}

void Init_Timer5(void) {
    
    T5CON = 0;              // Timer reset
    
    T5CONbits.ON = STOP;    // Disable Timer5   
    T5CONbits.SIDL  = 0;    // Disable Stop in Idle Mode bit
    T5CONbits.SYNC  = 0;    // Disable Timer External Clock Input Synchronization Selection bit
    T5CONbits.TGATE = 0;    // Disable Timer Gated Time Accumulation Enable bit
    T5CONbits.TCKPS = 5;    // 1:8 pre-scale value
    T5CONbits.T32   = 1;    // 32-bit Timer Mode Select bit
    T5CONbits.TCS   = 0;    // Disable Timer Clock Source Select bit
   
    TMR5 = 0x0;             // Timer5 Counter Clear
  
    PR5 = 2000;            // SET Timer5 Period (25Hz)37500
    
    IFS0bits.T5IF = 0;   
    
    IEC0bits.T5IE = 1;      // Disable Timer2_Interrupt
    
    IPC6SET = 0x4U | 0x0U;  /* TIMER_5:  Priority 1 / Subpriority 0 */
 
    T5CONbits.ON = STOP;   // Timer2 STOP
}





/*-----DO NOT MODIFY----*/
void Init_EVIC(void) {
    INTCONSET = _INTCON_MVEC_MASK;
    

    /* Configure Shadow Register Set */
    PRISS = 0x76543210;
    

    while (PRISS != 0x76543210U)
    {
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
    PMD1bits.ADCMD  = 1;    // ADC1-ADC7
    PMD1bits.DAC1MD = 1;    // CDAC_1
    PMD1bits.DAC2MD = 1;    // CDAC_2    
    PMD1bits.CTMUMD = 1;    // CTMU
    PMD1bits.EEMD   = 1;    // Data EEPROM
    PMD1bits.DAC3MD = 1;    // CDAC_3
    
//    PMD2 = 0x17001fU;
    PMD2bits.CMP1MD = 1;    // Comparator_1
    PMD2bits.CMP2MD = 1;    // Comparator_2
    PMD2bits.CMP4MD = 1;    // Comparator_4
    PMD2bits.CMP5MD = 1;    // Comparator_5
    PMD2bits.OPA1MD = 1;    // Op amp_1
    PMD2bits.OPA2MD = 1;    // Op amp_2
    PMD2bits.OPA3MD = 1;    // Op amp_3
    PMD2bits.OPA5MD = 1;    // Op amp_4
    PMD2bits.CMP3MD = 0;    // Comparator_3
    
    
//    PMD3 = 0xfffffU;
    PMD3bits.IC10MD = 1;    // Input Capture_10
    PMD3bits.IC11MD = 1;    // Input Capture_11
    PMD3bits.IC12MD = 1;    // Input Capture_12
    PMD3bits.IC13MD = 1;    // Input Capture_13
    PMD3bits.IC14MD = 1;    // Input Capture_14
    PMD3bits.IC15MD = 1;    // Input Capture_15
    PMD3bits.IC16MD = 1;    // Input Capture_16
    PMD3bits.IC1MD  = 1;    // Input Capture_1
    PMD3bits.IC2MD  = 1;    // Input Capture_2
    PMD3bits.IC3MD  = 1;    // Input Capture_3
    PMD3bits.IC4MD  = 1;    // Input Capture_4
    PMD3bits.IC5MD  = 1;    // Input Capture_5
    PMD3bits.IC6MD  = 1;    // Input Capture_6
    PMD3bits.IC7MD  = 1;    // Input Capture_7
    PMD3bits.IC8MD  = 1;    // Input Capture_8
    PMD3bits.IC9MD  = 1;    // Input Capture_9
    PMD3bits.OC10MD = 1;    // Output Compare_10
    PMD3bits.OC11MD = 1;    // Output Compare_11
    PMD3bits.OC12MD = 1;    // Output Compare_12
    PMD3bits.OC13MD = 1;    // Output Compare_13
    PMD3bits.OC14MD = 1;    // Output Compare_14
    PMD3bits.OC15MD = 1;    // Output Compare_15
    PMD3bits.OC16MD = 1;    // Output Compare_16
    PMD3bits.OC1MD  = 1;    // Output Compare_1
    PMD3bits.OC2MD  = 1;    // Output Compare_2
    PMD3bits.OC3MD  = 1;    // Output Compare_3
    PMD3bits.OC4MD  = 1;    // Output Compare_4
    PMD3bits.OC5MD  = 1;    // Output Compare_5
    PMD3bits.OC6MD  = 1;    // Output Compare_6
    PMD3bits.OC7MD  = 1;    // Output Compare_7
    PMD3bits.OC8MD  = 1;    // Output Compare_8
    PMD3bits.OC9MD  = 1;    // Output Compare_9
   
    
//    PMD4 = 0xfff01ffU;
    PMD4bits.PWM10MD = 1;   // PWM_10
    PMD4bits.PWM11MD = 1;   // PWM_11    
    PMD4bits.PWM12MD = 1;   // PWM_12
    PMD4bits.PWM1MD  = 1;   // PWM_1
    PMD4bits.PWM2MD  = 1;   // PWM_2
    PMD4bits.PWM3MD  = 1;   // PWM_3
    PMD4bits.PWM4MD  = 1;   // PWM_4
    PMD4bits.PWM5MD  = 1;   // PWM_5
    PMD4bits.PWM6MD  = 1;   // PWM_6
    PMD4bits.PWM7MD  = 1;   // PWM_7
    PMD4bits.PWM8MD  = 1;   // PWM_8
    PMD4bits.PWM9MD  = 1;   // PWM_9
    PMD4bits.T1MD    = 1;   // Timer_1
    PMD4bits.T2MD    = 0;   // Timer_2 enabled
    PMD4bits.T3MD    = 0;   // Timer_3 enabled
    PMD4bits.T4MD    = 0;   // Timer_4 enabled
    PMD4bits.T5MD    = 0;   // Timer_5 enabled
    PMD4bits.T6MD    = 1;   // Timer_6
    PMD4bits.T7MD    = 1;   // Timer_7
    PMD4bits.T8MD    = 1;   // Timer_8
    PMD4bits.T9MD    = 1;   // Timer_9
    
    
//    PMD5 = 0xf30f3f3bU;
    PMD5bits.CAN1MD  = 1;   // CAN_1
    PMD5bits.CAN2MD  = 1;   // CAN_2
    PMD5bits.CAN3MD  = 1;   // CAN_3
    PMD5bits.CAN4MD  = 1;   // CAN_4
    PMD5bits.I2C1MD  = 1;   // I2C_1
    PMD5bits.I2C2MD  = 1;   // I2C_2
    PMD5bits.I2C3MD  = 1;   // I2C_3
    PMD5bits.I2C4MD  = 1;   // I2C_4
    PMD5bits.SPI1MD  = 1;   // SPI_1
    PMD5bits.SPI2MD  = 1;   // SPI_2
    PMD5bits.SPI3MD  = 1;   // SPI_3
    PMD5bits.SPI4MD  = 1;   // SPI_4
    PMD5bits.SPI5MD  = 1;   // SPI_5
    PMD5bits.SPI6MD  = 1;   // SPI_6
    PMD5bits.U1MD    = 0;   // UART_1
    PMD5bits.U2MD    = 1;   // UART_2
    PMD5bits.U4MD    = 1;   // UART_4
    PMD5bits.U5MD    = 1;   // UART_5
    PMD5bits.U6MD    = 1;   // UART_6
    PMD5bits.USB1MD  = 1;   // USB_1
    PMD5bits.USB2MD  = 1;   // USB_2
    PMD5bits.U3MD    = 1;   // UART_3
    
//    PMD6 = 0xf0d0000U;
    
    PMD6bits.PMPMD  = 1;    // Parallel Master Port
    PMD6bits.QEI1MD = 1;    // QEI_1
    PMD6bits.QEI2MD = 1;    // QEI_2
    PMD6bits.QEI3MD = 1;    // QEI_3
    PMD6bits.QEI4MD = 1;    // QEI_4 
    PMD6bits.QEI5MD = 1;    // QEI_5
    PMD6bits.QEI6MD = 1;    // QEI_6
    PMD6bits.REFO1MD= 0;    // Reference Clock_1
    PMD6bits.REFO2MD= 0;    // Reference Clock_2
    PMD6bits.REFO3MD= 0;    // Reference Clock_3
    PMD6bits.REFO4MD= 0;    // Reference Clock_4
        
//    PMD7 = 0x0U;
    PMD7bits.DMAMD  = 0;    // DMA 
   

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
    
    Init_Timer4();
    
    Init_Timer5();
     
    Init_UART1();
     
    Init_Limit_Switch_A();  
    
    Init_Limit_Switch_B();
    
    Init_Limit_Switch_C(); 
    
    Init_Limit_Switch_D(); 
    
    Init_EVIC();

    /* Enable global interrupts */
    (void) __builtin_enable_interrupts();

}

