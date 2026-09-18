#ifndef UART_POLL_H
#define UART_POLL_H

#include <stdint.h>

#include "hal_clock.h"
#include "hal_pinmux.h"
#include "hal_gpio.h"
#include "hal_lpuart.h"
#include "MCXN236.h"                  /* Device specific peripheral access layer header file */
// #include "MCXN236_COMMON.h"

#define RX_BUFFER_SIZE 32U

int uart_poll_main(void);


#endif /* UART_POLL_H */