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

CommandID parse_command(const char *cmd) {
    if      (strcmp(cmd, "RASLE") == 0) return CMD_RASLE;
    else if (strcmp(cmd, "RASLW") == 0) return CMD_RASLW;
    else if (strcmp(cmd, "DECSLN") == 0) return CMD_DECSLN;
    else if (strcmp(cmd, "DECSLS") == 0) return CMD_DECSLS;
    else if (strcmp(cmd, "RASTE") == 0) return CMD_RASTE;
    else if (strcmp(cmd, "RASTW") == 0) return CMD_RASTW;
    else if (strcmp(cmd, "DECSTN") == 0) return CMD_DECSTN;
    else if (strcmp(cmd, "DECSTS") == 0) return CMD_DECSTS;
    else if (strcmp(cmd, "RAGE")  == 0) return CMD_RAGE;
    else if (strcmp(cmd, "RAGW")  == 0) return CMD_RAGW;
    else if (strcmp(cmd, "DECGN") == 0) return CMD_DECGN;
    else if (strcmp(cmd, "DECGS") == 0) return CMD_DECGS;
    else if (strcmp(cmd, "RAFGE") == 0) return CMD_RAFGE;
    else if (strcmp(cmd, "RAFGW") == 0) return CMD_RAFGW;
    else if (strcmp(cmd, "DECFGN") == 0) return CMD_DECFGN;
    else if (strcmp(cmd, "DECFGS") == 0) return CMD_DECFGS;
    
    else if (strcmp(cmd, "HANDSET") == 0) return CMD_HANDSET;
    else if (strcmp(cmd, "CONSOLE") == 0) return CMD_CONSOLE;
    
    else if (strcmp(cmd, "ON") == 0) return CMD_ON;
    else if (strcmp(cmd, "OFF") == 0) return CMD_OFF;
    
    else return CMD_NONE;
}


void process_command(const char *cmd) {
    CommandID id = parse_command(cmd);
    
//    if(id == CMD_HANDSET){
//        handset_enabled = 1;
//    }
//    
//    if(id != CMD_HANDSET){
      switch (id) {
            
        case CMD_HANDSET:
            handset_enabled = 1;
            console = 0;
            break;
             
        case CMD_CONSOLE:
            handset_enabled = 0;
            console = 1;
            break;
            
        // --- RA Commands ---
        case CMD_RASLE:
            MOTOR_DIRECTION_RA = EAST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(SLEW_FREQUENCY);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;   // ensure DEC is off
            break;

        case CMD_RASLW:
            MOTOR_DIRECTION_RA = WEST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(SLEW_FREQUENCY);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;
            break;

        case CMD_RASTE:
            MOTOR_DIRECTION_RA = EAST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(SET_FREQUENCY);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;
            break;

        case CMD_RASTW:
            MOTOR_DIRECTION_RA = WEST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(SET_FREQUENCY);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;
            break;

        case CMD_RAGE:
            MOTOR_DIRECTION_RA = EAST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(GUIDE_FREQUENCY);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;
            break;

        case CMD_RAGW:
            MOTOR_DIRECTION_RA = WEST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(GUIDE_FREQUENCY);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;
            break;

        case CMD_RAFGE:
            MOTOR_DIRECTION_RA = EAST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(FINE_GUIDE_FREQUENCY);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;
            break;

        case CMD_RAFGW:
            MOTOR_DIRECTION_RA = WEST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(FINE_GUIDE_FREQUENCY);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;
            break;

        // --- DEC Commands ---
        case CMD_DECSLN:
            MOTOR_DIRECTION_DEC = NORTH_DIRECTION;
            TIMER_NORTH_SOUTH = TIMER_VALUE(SLEW_FREQUENCY);
            DEC_PULSE = PULSE_ON;
            RA_PULSE = PULSE_OFF;   // ensure RA is off
            break;

        case CMD_DECSLS:
            MOTOR_DIRECTION_DEC = SOUTH_DIRECTION;
            TIMER_NORTH_SOUTH = TIMER_VALUE(SLEW_FREQUENCY);
            DEC_PULSE = PULSE_ON;
            RA_PULSE = PULSE_OFF;
            break;

        case CMD_DECSTN:
            MOTOR_DIRECTION_DEC = NORTH_DIRECTION;
            TIMER_NORTH_SOUTH = TIMER_VALUE(SET_FREQUENCY);
            DEC_PULSE = PULSE_ON;
            RA_PULSE = PULSE_OFF;
            break;

        case CMD_DECSTS:
            MOTOR_DIRECTION_DEC = SOUTH_DIRECTION;
            TIMER_NORTH_SOUTH = TIMER_VALUE(SET_FREQUENCY);
            DEC_PULSE = PULSE_ON;
            RA_PULSE = PULSE_OFF;
            break;

        case CMD_DECGN:
            MOTOR_DIRECTION_DEC = NORTH_DIRECTION;
            TIMER_NORTH_SOUTH = TIMER_VALUE(GUIDE_FREQUENCY);
            DEC_PULSE = PULSE_ON;
            RA_PULSE = PULSE_OFF;
            break;

        case CMD_DECGS:
            MOTOR_DIRECTION_DEC = SOUTH_DIRECTION;
            TIMER_NORTH_SOUTH = TIMER_VALUE(GUIDE_FREQUENCY);
            DEC_PULSE = PULSE_ON;
            RA_PULSE = PULSE_OFF;
            break;

        case CMD_DECFGN:
            MOTOR_DIRECTION_DEC = NORTH_DIRECTION;
            TIMER_NORTH_SOUTH = TIMER_VALUE(FINE_GUIDE_FREQUENCY);
            DEC_PULSE = PULSE_ON;
            RA_PULSE = PULSE_OFF;
            break;

        case CMD_DECFGS:
            MOTOR_DIRECTION_DEC = SOUTH_DIRECTION;
            TIMER_NORTH_SOUTH = TIMER_VALUE(FINE_GUIDE_FREQUENCY);
            DEC_PULSE = PULSE_ON;
            RA_PULSE = PULSE_OFF;
            break;

        case CMD_ON:
            MOTOR_DIRECTION_RA = WEST_DIRECTION;
            TIMER_WEST_EAST = TIMER_VALUE(29.17);
            RA_PULSE = PULSE_ON;
            DEC_PULSE = PULSE_OFF;
            break;

        case CMD_OFF:
            RA_PULSE = PULSE_OFF;
            DEC_PULSE = PULSE_OFF;
            break;
            
            
              
        // --- No valid command ---
        case CMD_NONE:
        default:
            RA_PULSE = PULSE_OFF;
            DEC_PULSE = PULSE_OFF;
            handset_enabled = 0;
            break;
      }
    }
//}

