#ifndef RTOS_UART_H
#define RTOS_UART_H

#include <xc.h>
#include "FreeRTOS.h"
#include "queue.h"

// Initialize UART and the Gatekeeper Task
void UART_Init_RTOS(void);

// The function your team will use to print
void UART_Print(const char *string);

#endif