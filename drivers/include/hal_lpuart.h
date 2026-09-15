#ifndef HAL_LPUART_H
#define HAL_LPUART_H

#include "fsl_lpuart.h"



#define LED_ACTIVE_HIGH  0U


void hal_uart_init(LPUART_Type *base, uint32_t srcClock_Hz);
void hal_uart_enableTx(LPUART_Type *base, bool enable);
void hal_uart_enableRx(LPUART_Type *base, bool enable);
void hal_uart_write_data(LPUART_Type *base, uint8_t data);

#endif /* HAL_LPUART_H */