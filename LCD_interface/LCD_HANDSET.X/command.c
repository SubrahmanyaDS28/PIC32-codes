#include <string.h>
#include "command.h"
#include "constants.h"   // your motor directions, pulses, timers, etc.
#include "config.h"

uint16_t read_switches(void) {
    uint16_t s = 0;
    if (PORTCbits.RC8) s |= 0x01;  // RA_E
    if (PORTCbits.RC9) s |= 0x02;  // RA_W
    if (PORTDbits.RD5) s |= 0x04;  // DEC_N
    if (PORTDbits.RD6) s |= 0x08;  // DEC_S
    
//    if (PORTEbits.RE12) s |= 0x10;
//    if (PORTEbits.RE13) s |= 0x20;
//    if (PORTEbits.RE14) s |= 0x40;
//    if (PORTEbits.RE15) s |= 0x80;
    
    if (PORTFbits.RF6) s |= 0x10;
    if (PORTFbits.RF7) s |= 0x20;
    
    if (PORTBbits.RB10) s |= 0x100;  // RA_E
    if (PORTBbits.RB11) s |= 0x200;  // RA_W
    if (PORTBbits.RB12) s |= 0x400;  // DEC_N
    if (PORTBbits.RB13) s |= 0x800;  // DEC_S
    
    
    return s;
}
