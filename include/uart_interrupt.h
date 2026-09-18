#ifndef UART_INTERRUPT_H
#define UART_INTERRUPT_H

#include <stdint.h>

#include "hal_clock.h"
#include "hal_pinmux.h"
#include "hal_gpio.h"
#include "hal_lpuart.h"
#include "MCXN236.h"                  /* Device specific peripheral access layer header file */
// #include "MCXN236_COMMON.h"

#define RX_BUFFER_SIZE 32U

int uart_interrupt_main(void);


#endif /* UART_INTERRUPT_H */