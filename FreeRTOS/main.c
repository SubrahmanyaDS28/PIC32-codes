/*
 * Main Application
 * Hardware: PIC32MK1024MCM100
 * RTOS: FreeRTOS v202212
 */

// 1. INCLUDES
#include <xc.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pic32_config.h" // Your config bits file
#include "rtos_uart.h"
#include "rtos_mutex_demo.h"
#include "rtos_semaphore_demo.h"
#include "rtos_dynamic_demo.h"

// 2. HARDWARE DEFINITIONS
#define LED1_TRIS   TRISGbits.TRISG12
#define LED1_LAT    LATGbits.LATG12

#define LED2_TRIS   TRISGbits.TRISG13 
#define LED2_LAT    LATGbits.LATG13

#define LED3_TRIS   TRISGbits.TRISG14 
#define LED3_LAT    LATGbits.LATG14

// 3. TASK PROTOTYPES
// (It is good practice to prototype them if they are defined below main, 
//  but since they are above, this is just for reference)
void vBlinkTask1( void * pvParameters );
void vBlinkTask2( void * pvParameters );
void vBlinkTask3( void * pvParameters );

// 4. MAIN FUNCTION
int main( void )
{
    // --- Hardware Initialization ---
    
    // 1. Enable multi-vector interrupts (Required for FreeRTOS context switch)
    INTCONbits.MVEC = 1;
    
    // 2. Cache & Wait State Configuration for 120MHz
    // We must unlock the system to change CHECON
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    
    // PFMWS = 5 wait states are required for 120MHz on PIC32MK
    CHECONbits.PFMWS = 5; 
    
    // Enable Predictive Prefetch for better performance
    CHECONbits.PREFEN = 1;
    
    SYSKEY = 0; // Relock

    // --- FreeRTOS Initialization ---
    UART_Init_RTOS();
//    MutexDemo_Init();
//    SemaphoreDemo_Init();
//    DynamicTaskDemo_Init();
    
    // Create the Blink Task
//    xTaskCreate(
//        vBlinkTask,     // Function
//        "Blinky",       // Name
//        1024,           // Stack size
//        NULL,           // Parameters
//        1,              // Priority
//        NULL            // Handle
//    );
    // Create Tasks
    xTaskCreate( vBlinkTask1, "LED1", 1024, NULL, 1, NULL );
    xTaskCreate( vBlinkTask2, "LED2", 1024, NULL, 1, NULL );

    // Start the Scheduler
    vTaskStartScheduler();

    // Should never reach here
    while(1);
    return 0;
}

// 5. TASK IMPLEMENTATIONS

// Task 1
void vBlinkTask1( void * pvParameters )
{
    LED1_TRIS = 0;
    for( ;; )
    {
        LED1_LAT ^= 1;
        UART_Print("Task 1 Blinking\r\n"); // Print to Queue
        vTaskDelay( pdMS_TO_TICKS( 300 ) );
    }
}

// Task 2
void vBlinkTask2( void * pvParameters )
{
    LED2_TRIS = 0;
    for( ;; )
    {
        LED2_LAT ^= 1;
        UART_Print("Task 2 Blinking\r\n"); // Print to Queue
        vTaskDelay( pdMS_TO_TICKS( 200 ) );
    }
}

void vBlinkTask3( void * pvParameters )
{
    LED3_TRIS = 0; // Set as Output
    for( ;; )
    {
        LED3_LAT ^= 1;
        vTaskDelay( pdMS_TO_TICKS( 250 ) );
    }
}