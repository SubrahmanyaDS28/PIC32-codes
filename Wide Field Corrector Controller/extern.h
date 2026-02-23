
#ifndef __EXTERN_H__
#define __EXTERN_H__

#include "config.h"

typedef unsigned int FLAG;

extern FLAG DISABLE_MOTOR;

extern FLAG COMMAND_RECEIVED;

extern unsigned char command[];

extern unsigned int command_length;

extern unsigned int command_i;

extern FLAG INT_STATUS;

extern volatile int MOTOR_A_COUNT;

extern volatile int MOTOR_B_COUNT;

extern volatile int MOTOR_C_COUNT;

extern volatile int MOTOR_D_COUNT;

extern volatile char limit_A;
extern volatile char limit_B;
extern volatile char limit_C;
extern volatile char limit_D;

extern volatile uint16_t I1, I2, I3, I4;

#endif	/* __EXTERN_H__ */

