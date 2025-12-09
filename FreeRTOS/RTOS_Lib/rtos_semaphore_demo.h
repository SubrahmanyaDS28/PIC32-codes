#ifndef RTOS_SEMAPHORE_DEMO_H
#define RTOS_SEMAPHORE_DEMO_H

void SemaphoreDemo_Init(void);

// Call this function to signal that an event happened
void Signal_Event_Occurred(void);

#endif