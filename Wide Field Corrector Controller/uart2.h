#ifndef __UART2_H__
    #define __UART2_H__

    void UART2_putchar(char c);
    void UART2_putStr(unsigned char str[]);
    void send_RS232A(int number1, int number2, int number3, int number4);

#endif