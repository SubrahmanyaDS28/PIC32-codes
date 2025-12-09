#include <xc.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "semphr.h"  // Required for Mutexes
#include "rtos_uart.h" // We use your new UART library to debug!

// 1. The Protected Resource (Global Variable)
static int Global_Counter = 0;

// 2. The Mutex Handle
static SemaphoreHandle_t xResourceMutex;

// -----------------------------------------------------------
// Helper Functions (The "Safe" Interface)
// -----------------------------------------------------------

void SharedData_Increment(int amount)
{
    // Try to take the key (Mutex). Wait forever if needed.
    if( xSemaphoreTake(xResourceMutex, portMAX_DELAY) == pdTRUE )
    {
        // --- CRITICAL SECTION START ---
        // Only one task can be here at a time.
        
        int temp = Global_Counter;
        
        // Artificially slow down to force conflicts if Mutex wasn't here
        // (In real life, this delay represents complex calculation)
        for(int i=0; i<1000; i++) Nop(); 
        
        Global_Counter = temp + amount;
        
        // --- CRITICAL SECTION END ---
        
        // Give the key back so others can use it
        xSemaphoreGive(xResourceMutex);
    }
}

int SharedData_Get(void)
{
    int value = 0;
    
    // Even reading needs protection to ensure we don't read
    // while someone else is half-way through writing.
    if( xSemaphoreTake(xResourceMutex, portMAX_DELAY) == pdTRUE )
    {
        value = Global_Counter;
        xSemaphoreGive(xResourceMutex);
    }
    return value;
}

// -----------------------------------------------------------
// Demo Tasks
// -----------------------------------------------------------

// Task A: Adds 1 repeatedly
void vTaskA(void *pvParameters)
{
    char buffer[50];
    for(;;)
    {
        SharedData_Increment(1);
        
        int current_val = SharedData_Get();
        sprintf(buffer, "Task A: Value is %d\r\n", current_val);
        UART_Print(buffer); // Use your existing UART library
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Task B: Adds 10 repeatedly
void vTaskB(void *pvParameters)
{
    char buffer[50];
    for(;;)
    {
        SharedData_Increment(10);
        
        int current_val = SharedData_Get();
        sprintf(buffer, "Task B: Value is %d\r\n", current_val);
        UART_Print(buffer);
        
        vTaskDelay(pdMS_TO_TICKS(105)); // Slightly different timing
    }
}

// -----------------------------------------------------------
// Initialization
// -----------------------------------------------------------
void MutexDemo_Init(void)
{
    // 1. Create the Mutex
    xResourceMutex = xSemaphoreCreateMutex();

    if( xResourceMutex != NULL )
    {
        // 2. Create the tasks that will fight over the resource
        xTaskCreate(vTaskA, "TaskA", 1024, NULL, 1, NULL);
        xTaskCreate(vTaskB, "TaskB", 1024, NULL, 1, NULL);
    }
}