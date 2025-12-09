#ifndef __UART1_H__
#define __UART1_H__

    void UART1_putchar(char c);
    void UART1_putStr(unsigned char str[]);
    void UART1_SendNumber(unsigned int number);
    void send_RS232(int number1, int number2, int number3, int number4);

#endif