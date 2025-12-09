#include <sys/attribs.h>
#include <stdio.h>
#include "pic32_config.h"
#include "initialize.h"
#include "config.h"
#include "uart2.h"
#include "constants.h"
#include "extern.h"
#include "command.h"
#include "encoder.h"
#include "ADC.h"
#include "adc_common.h"

int main() {
    unsigned int i, j;

    Init_SYS(NULL);

    ADCHS_Initialize();
    
    UART2_putchar('~');
    UART2_putchar('~');
    UART2_putchar('~');

    LED_1 = 1;
    LED_2 = 1;
    LED_3 = 1;
    
    uint32_t encoder1_value = 0;
    uint32_t encoder2_value = 0;
    
    int8_t ra_h;
    uint8_t ra_m, ra_s;
    int16_t dec_d;
    uint8_t dec_m, dec_s;
        
    char msg[100];
    
//    int k = 0;
    while (1) {
        
//        uint32_t encoder1_counts = Read_17bit_Encoder(0); // RA
//        uint32_t encoder2_counts = Read_17bit_Encoder(4); // DEC
//
//        double ra_hours = EncoderToRA(encoder1_counts);
//        double dec_degs = EncoderToDEC(encoder2_counts);
//
//        RA_To_HMS(ra_hours, &ra_h, &ra_m, &ra_s);
//        DEC_To_DMS(dec_degs, &dec_d, &dec_m, &dec_s);
//        
//        sprintf(msg, "RA_E  %03d:%02d:%02d\r\n", ra_h, ra_m, ra_s);
//        UART2_putStr(msg);
//
//        sprintf(msg, "DEC_E %03d° %02d' %02d\"\r\n", dec_d, dec_m, dec_s);
//        UART2_putStr(msg);
        
        uint32_t posRA = (uint32_t)POS1CNT;  // Get current position
        Convert_RA_to_HMS_Centered_QEI1(posRA);           // Convert to hours, minutes, seconds
//
        uint16_t posDEC = (uint16_t)POS2CNT;
        Convert_DEC_to_DMS_Centered_QEI2(posDEC);           // Convert to Degree, minutes, seconds
//        sprintf(msg, "RA_E %d\n", posRA);
//        UART2_putStr(msg);
//        sprintf(msg, "DEC_E %d\n", posDEC);
//        UART2_putStr(msg);
        
        Read_Focus_ADC();
        
//        UART2_SendNumber(k);
//        k = k + 10;
        LED_3 = !LED_3;
        if (uart_flag) {
            uart_flag = 0;
            process_command(uart_buffer);
        }
        if(handset_enabled){
            LED_1 = 1;
            LED_2 = 0;
        }
        else{
            LED_1 = 0;
            LED_2 = 1;
        }
        
//        if(PORTAbits.RA4){
//            LED_1 = 1;
//            LED_2 = 1;
//            LED_3 = 1;
//            for (i = 0; i < 3000; i++)
//                for (j = 0; j < 3000; j++)
//                    Nop();
//            LED_1 = 0;
//            LED_2 = 0;
//            LED_3 = 0;
//            for (i = 0; i < 3000; i++)
//                for (j = 0; j < 3000; j++)
//                    Nop();
//            LED_1 = 1;
//            LED_2 = 1;
//            LED_3 = 1;
//            for (i = 0; i < 3000; i++)
//                for (j = 0; j < 3000; j++)
//                    Nop();
//            LED_1 = 0;
//            LED_2 = 0;
//            LED_3 = 0;
//            for (i = 0; i < 3000; i++)
//                for (j = 0; j < 3000; j++)
//                    Nop();
//        }
        
        // other tasks...
        for (i = 0; i < 3000; i++)
            for (j = 0; j < 3000; j++)
                Nop();
    }
}

