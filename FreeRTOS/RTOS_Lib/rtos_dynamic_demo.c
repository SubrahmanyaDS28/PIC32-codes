#include <xc.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "rtos_uart.h" // Using our trusty UART library

// Handle to track the temporary task
static TaskHandle_t xWorkerHandle = NULL;

// -----------------------------------------------------------
// The "Worker" Task (Temporary)
// -----------------------------------------------------------
void vWorkerTask(void *pvParameters)
{
    // This task doesn't know it's going to be deleted.
    // It just does its job.
    int count = 0;
    char buffer[50];

    UART_Print("  [Worker]: I am alive! Starting work...\r\n");

    for(;;)
    {
        count++;
        sprintf(buffer, "  [Worker]: Working... Count = %d\r\n", count);
        UART_Print(buffer);
        
        vTaskDelay(pdMS_TO_TICKS(1000)); // Work every 1 second
    }
}

// -----------------------------------------------------------
// The "Manager" Task (Permanent)
// -----------------------------------------------------------
void vManagerTask(void *pvParameters)
{
    for(;;)
    {
        // --- PHASE 1: Create the Worker ---
        UART_Print("[Manager]: Creating the Worker Task now.\r\n");
        
        xTaskCreate(
            vWorkerTask, 
            "Worker", 
            1024, 
            NULL, 
            1, 
            &xWorkerHandle // Save the ID so we can kill it later
        );

        // --- PHASE 2: Let it run for 5 seconds ---
        vTaskDelay(pdMS_TO_TICKS(5000));

        // --- PHASE 3: Delete the Worker ---
        if( xWorkerHandle != NULL )
        {
            UART_Print("[Manager]: Time's up! Deleting Worker Task.\r\n");
            
            vTaskDelete(xWorkerHandle); // Kill the specific task
            xWorkerHandle = NULL;       // Clear the handle for safety
        }
        
        UART_Print("[Manager]: Worker deleted. Freeing heap memory.\r\n");

        // --- PHASE 4: Wait before restarting ---
        UART_Print("[Manager]: Waiting 3 seconds before next cycle...\r\n\r\n");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// -----------------------------------------------------------
// Initialization
// -----------------------------------------------------------
void DynamicTaskDemo_Init(void)
{
    // Only create the Manager. The Manager will create the Worker.
    xTaskCreate(vManagerTask, "Manager", 1024, NULL, 2, NULL);
}