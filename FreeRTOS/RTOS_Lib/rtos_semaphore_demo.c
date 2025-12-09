#include <xc.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "rtos_uart.h" // For printing

// 1. The Semaphore Handle
static SemaphoreHandle_t xWorkSemaphore;

// -----------------------------------------------------------
// The "Handler" Task (The one doing the work)
// -----------------------------------------------------------
void vHandlerTask(void *pvParameters)
{
    for(;;)
    {
        // 1. Block (Sleep) until the semaphore is given.
        // portMAX_DELAY means wait forever.
        if( xSemaphoreTake(xWorkSemaphore, portMAX_DELAY) == pdTRUE )
        {
            // 2. We got the signal! Do the work now.
            UART_Print("Handler: Signal Received! Processing Data...\r\n");
            
            // Simulate work (e.g., processing an ADC buffer)
            vTaskDelay(pdMS_TO_TICKS(100)); 
            
            UART_Print("Handler: Job Done. Going back to sleep.\r\n");
        }
    }
}

// -----------------------------------------------------------
// The "Trigger" Task (Simulating an Event/ISR)
// -----------------------------------------------------------
void vPeriodicTriggerTask(void *pvParameters)
{
    for(;;)
    {
        // Wait 3 seconds
        vTaskDelay(pdMS_TO_TICKS(3000));
        
        UART_Print("Trigger: Event Happened! Giving Semaphore.\r\n");
        
        // Give the signal
        Signal_Event_Occurred();
    }
}

// -----------------------------------------------------------
// Public Functions
// -----------------------------------------------------------

void Signal_Event_Occurred(void)
{
    // Give the semaphore. This unblocks vHandlerTask immediately.
    xSemaphoreGive(xWorkSemaphore);
}

void SemaphoreDemo_Init(void)
{
    // 1. Create a Binary Semaphore
    // It is empty by default.
    xWorkSemaphore = xSemaphoreCreateBinary();

    if( xWorkSemaphore != NULL )
    {
        // 2. Create the Handler (High Priority to react fast)
        xTaskCreate(vHandlerTask, "Handler", 1024, NULL, 2, NULL);
        
        // 3. Create the Simulator Trigger (Low Priority)
        xTaskCreate(vPeriodicTriggerTask, "Trigger", 1024, NULL, 1, NULL);
    }
}