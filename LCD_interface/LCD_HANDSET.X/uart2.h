#ifndef __UART2_H__
#define __UART2_H__

    void UART2_putchar(char c);
    void UART2_putStr(unsigned char str[]);
    void UART2_SendHex(uint8_t data);
    void UART2_SendNumber(unsigned int number);
    void send_RS232(int number1, int number2, int number3, int number4);

#endif