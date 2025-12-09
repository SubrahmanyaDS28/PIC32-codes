#ifndef COMMANDS_H
#define COMMANDS_H

typedef enum {
    CMD_NONE,
    CMD_RASLE, CMD_RASLW, CMD_DECSLN, CMD_DECSLS,
    CMD_RASTE, CMD_RASTW, CMD_DECSTN, CMD_DECSTS,
    CMD_RAGE,  CMD_RAGW,  CMD_DECGN,  CMD_DECGS,
    CMD_RAFGE, CMD_RAFGW, CMD_DECFGN, CMD_DECFGS,
    CMD_HANDSET, CMD_CONSOLE, CMD_ON, CMD_OFF
} CommandID;

CommandID parse_command(const char *cmd);
void process_command(const char *cmd);
//uint16_t read_switches(void);

#endif
