#ifndef TIMER_INTERRUPT_H
#define TIMER_INTERRUPT_H

#include "hal_ctimer.h"
#include "core_cm33.h"
// #include "MCXN236_COMMON.h"
#include "hal_gpio.h"
#include "hal_pinmux.h"
#include "hal_clock.h"

uint32_t HAL_ctimer_getTicks(void);
void HAL_ctimer_IncrementTick(void);
int main(void);


#endif /* TIMER_INTERRUPT_H */