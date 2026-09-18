#ifndef HAL_LPUART_H
#define HAL_LPUART_H

#include "fsl_lpuart.h"



#define LPUART_STAT_TDRE_MASK (1UL << 23U)
#define LPUART_STAT_RDRF_MASK (1UL << 21U)


void HAL_uart_init(LPUART_Type *base, uint32_t srcClock_Hz);
void HAL_uart_enableTx(LPUART_Type *base, bool enable);
void HAL_uart_enableRx(LPUART_Type *base, bool enable);
void HAL_uart_write_data(LPUART_Type *base, uint8_t data);
uint8_t HAL_uart_read_data(LPUART_Type *base);
status_t HAL_uart_writeBlocking(LPUART_Type *base, uint8_t *data, size_t length);
status_t HAL_uart_readBlocking(LPUART_Type *base, uint8_t *data, size_t length);
void HAL_uart_write_string(LPUART_Type *base, const char *string, size_t length);
void HAL_uart_EnableInterrupts(LPUART_Type *base, uint32_t mask);
void HAL_uart_DisableInterrupts(LPUART_Type *base, uint32_t mask);
void HAL_uart_TransferStartRingBuffer(LPUART_Type *base,
                                    lpuart_handle_t *handle,
                                    uint8_t *ringBuffer,
                                    size_t ringBufferSize);

status_t HAL_uart_TransferReceiveNonBlocking(LPUART_Type *base,
                                           lpuart_handle_t *handle,
                                           uint8_t *data,
                                           size_t length,
                                           size_t *receivedBytes);

void HAL_uart_TransferCreateHandle(LPUART_Type *base,
                                 lpuart_handle_t *handle,
                                 lpuart_transfer_callback_t callback,
                                 void *userData);

size_t HAL_uart_TransferGetRxRingBufferLength(LPUART_Type *base, lpuart_handle_t *handle);
#endif /* HAL_LPUART_H */