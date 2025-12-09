#include <xc.h>
#include <stdint.h>
#include "delay.h"

#define SYS_FREQ       120000000UL
#define CORE_TIMER_FREQ (SYS_FREQ/2)  // 60 MHz
#define CYCLES_PER_MICROSECOND (CORE_TIMER_FREQ/1000000UL) // 60
#define CYCLES_PER_MILLISECOND (CORE_TIMER_FREQ/1000UL)    // 60000

void delay_us(uint32_t us)
{
    uint32_t start = _CP0_GET_COUNT();
    uint32_t ticks = us * CYCLES_PER_MICROSECOND;
    while ((_CP0_GET_COUNT() - start) < ticks);
}

void delay_ms(uint32_t ms)
{
    while (ms--)
        delay_us(1000);
}
