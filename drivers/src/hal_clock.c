#include "hal_clock.h"

void HAL_CLOCK_Init(clock_ip_name_t clk)
{
    // Enable the clock for specific IP
    CLOCK_EnableClock(clk);

}