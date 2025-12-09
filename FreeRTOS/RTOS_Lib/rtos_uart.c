#include "rtos_uart.h"
#include "task.h"
#include <string.h>

// Queue Handle
static QueueHandle_t xUARTQueue;

// Hardware Initialization (Adapted from your initialize.c)
static void UART2_Hardware_Init(void)
{
    // --- PPS Unlock & Mapping ---
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;

    U2RXR = 11; // UART2 Rx using RG0 (Input)
    RPG1R = 2;  // UART2 Tx using RPG1 (Output)

    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;

    // --- UART2 Config ---
    U2MODE = 0;         // Reset
    U2MODEbits.BRGH = 1; // High Speed
    
    // Baud Rate Calculation for 115200 with 60MHz PBCLK (Configured in main)
    // Formula: ((PBCLK / 4) / Baud) - 1
    // ((60,000,000 / 4) / 115200) - 1 = 129.2
    U2BRG = 129; 

    U2STAbits.UTXEN = 1; // Enable TX
    U2STAbits.URXEN = 1; // Enable RX
    U2MODEbits.ON = 1;   // Enable Module
}

// -----------------------------------------------------------
// The Gatekeeper Task
// -----------------------------------------------------------
// This task waits for data in the Queue and sends it to hardware.
void vUARTGatekeeperTask(void *pvParameters)
{
    char *pcMessageToPrint;

    for (;;)
    {
        // 1. Wait for a message to arrive in the Queue.
        // portMAX_DELAY means: "Sleep forever until data arrives".
        // This consumes ZERO CPU while waiting.
        xQueueReceive(xUARTQueue, &pcMessageToPrint, portMAX_DELAY);

        // 2. Data arrived! Send it to UART Hardware.
        while (*pcMessageToPrint != '\0')
        {
            // Wait for TX Buffer to be empty
            while (U2STAbits.UTXBF); 
            
            U2TXREG = *pcMessageToPrint;
            pcMessageToPrint++;
        }
    }
}

// -----------------------------------------------------------
// Public Functions (The "Library" part)
// -----------------------------------------------------------

void UART_Init_RTOS(void)
{
    // 1. Initialize Hardware
    UART2_Hardware_Init();

    // 2. Create Queue
    // We store POINTERS to strings (char *), not the strings themselves.
    // Depth 10: Can hold 10 pending messages.
    xUARTQueue = xQueueCreate(10, sizeof(char *));

    // 3. Create the Gatekeeper Task
    // Priority 0 (Low) is usually fine for logging.
    xTaskCreate(vUARTGatekeeperTask, "UART_Gate", 1024, NULL, 1, NULL);
}

void UART_Print(const char *string)
{
    // Send the address of the string to the Queue.
    // 0 means "Don't block if queue is full".
    xQueueSend(xUARTQueue, &string, 0);
}