
#ifndef __EXTERN_H__
#define __EXTERN_H__

#include "config.h"

typedef unsigned int FLAG;

extern FLAG DISABLE_MOTOR;

extern FLAG COMMAND_RECEIVED;

extern unsigned char command[];

extern unsigned int command_length;

extern unsigned int command_i;


//extern FORWARD_LIMIT_SET;
//
//extern BACKWARD_LIMIT_SET;


#endif	/* __EXTERN_H__ */

