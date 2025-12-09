#include "constants.h"

volatile char uart_buffer[16];
volatile uint8_t uart_flag = 0;

volatile uint8_t handset_enabled = 0;
volatile uint8_t console = 1;