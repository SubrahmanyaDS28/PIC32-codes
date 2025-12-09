#ifndef RTOS_MUTEX_DEMO_H
#define RTOS_MUTEX_DEMO_H

void MutexDemo_Init(void);

// These functions will be safe to call from ANY task
void SharedData_Increment(int amount);
int  SharedData_Get(void);

#endif