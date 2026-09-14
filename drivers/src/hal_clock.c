#include "hal_clock.h"

void HAL_CLOCK_Init(void)
{
    /* Enable PORT4 clock for pin multiplexing */
    CLOCK_EnableClock(kCLOCK_Port4);

    /* Enable GPIO4 clock for GPIO operation */
    CLOCK_EnableClock(kCLOCK_Gpio4);
}