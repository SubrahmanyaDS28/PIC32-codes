#include <xc.h>
#include "uart1.h"
#include "constants.h"

void UART1_putchar(char c){
    while (U1STAbits.TRMT == 0); // Wait till previously sent character is transmitted

	U1TXREG = c; // Transmit one character
}

void UART1_putStr(unsigned char str[]) {
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		UART1_putchar(str[i]);
}

void UART1_SendHex(uint8_t data)
{
    const char hexChars[] = "0123456789ABCDEF";

    UART1_putchar(hexChars[(data >> 4) & 0x0F]);  // high nibble
    UART1_putchar(hexChars[data & 0x0F]);         // low nibble
}

void UART1_SendNumber(unsigned int number) {
    char buffer[12];  // Enough for 32-bit int + null terminator
    int i = 0;

    // Convert number to ASCII (in reverse order)
    if (number == 0) {
        while (U1STAbits.UTXBF);  // Wait if TX buffer full
        U1TXREG = '0';
        return;
    }

    while (number > 0) {
        buffer[i++] = '0' + (number % 10);
        number /= 10;
    }

    // Send digits in correct order
    while (i--) {
        while (U1STAbits.UTXBF);  // Wait if TX buffer full
        U1TXREG = buffer[i];
    }

    // Optionally add newline
    while (U1STAbits.UTXBF); U1TXREG = '\r';
    while (U1STAbits.UTXBF); U1TXREG = '\n';
}


//void send_RS232(int number1, int number2, int number3, int number4) {
//	int i;
//	unsigned char string[] = {STx, 'R', '+', '0', '0', '0', '0', '0', '0', '0', '0', ',', '+', '0', '0', '0', '0', '0', ',', '+', '0', '0', '0', '0', '0', ',', '+', '0', '0', '0', '0', '0', '\n', ETx, '\0'};
//	//char string[]={'0','0','0','0',',','0','0','0','0','0',',','0','0','0','0','0',',','0','0','0','0','0','\0'};
//	if (number1 < 0) {
//		string[2] = '-';
//		number1 = -number1;
//	}
//	if (number2 < 0) {
//		string[12] = '-';
//		number2 = -number2;
//	}
//	if (number3 < 0) {
//		string[19] = '-';
//		number3 = -number3;
//	}
//	if (number4 < 0) {
//		string[26] = '-';
//		number4 = -number4;
//	}
//	for (i = 10; (number1 > 0 && i >= 3); number1 /= 10) {
//		string[i--] = number1 % 10 + '0'; //for getting ascii values
//	}
//
//	for (i = 17; (number2 > 0 && i >= 13); number2 /= 10) {
//		string[i--] = number2 % 10 + '0'; //for getting ascii values
//	}
//
//	for (i = 24; (number3 > 0 && i >= 20); number3 /= 10) {
//		string[i--] = number3 % 10 + '0'; //for getting ascii values
//	}
//
//	for (i = 31; (number4 > 0 && i >= 27); number4 /= 10) {
//		string[i--] = number4 % 10 + '0'; //for getting ascii values
//	}
//
//	UART1_putStr(string);
//}

