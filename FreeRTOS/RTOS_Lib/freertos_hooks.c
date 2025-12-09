/*
 * freertos_hooks.c
 * Contains FreeRTOS application callbacks (Hooks) and Error Traps.
 */

#include <xc.h>
#include "FreeRTOS.h"
#include "task.h"

// ----------------------------------------------------------------------------
// Memory Allocation Failed Hook
// ----------------------------------------------------------------------------
// Called if pvPortMalloc() fails because there is insufficient heap size.
void vApplicationMallocFailedHook( void )
{
    // OPTIONAL: Toggle a specific "Error LED" here to alert the user.
    taskDISABLE_INTERRUPTS();
    for( ;; );
}

// ----------------------------------------------------------------------------
// Stack Overflow Hook
// ----------------------------------------------------------------------------
// Called if a task uses more stack space than allocated.
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    // OPTIONAL: Print pcTaskName to UART if available
    taskDISABLE_INTERRUPTS();
    for( ;; );
}

// ----------------------------------------------------------------------------
// Assert Called
// ----------------------------------------------------------------------------
// Called if a configASSERT() statement fails.
void vAssertCalled( const char * pcFile, unsigned long ulLine )
{
    volatile unsigned long ul = 0;

    ( void ) pcFile;
    ( void ) ulLine;

    taskDISABLE_INTERRUPTS();
    for( ;; )
    {
        // Debugging Tip:
        // If you are stuck here, hover over 'pcFile' and 'ulLine' variables
        // in the debugger to see exactly which file caused the error.
        while( ul == 0 )
        {
            portNOP();
        }
    }
}