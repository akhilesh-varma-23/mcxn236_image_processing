#include "hal_lpuart.h"

void HAL_uart_init(LPUART_Type *base, uint32_t srcClock_Hz)
{
    status_t status;
    lpuart_config_t uart_cfg;

    LPUART_GetDefaultConfig(&uart_cfg);
    uart_cfg.baudRate_Bps = 115200U;
    uart_cfg.parityMode = kLPUART_ParityDisabled;
    uart_cfg.dataBitsCount = kLPUART_EightDataBits;
    uart_cfg.isMsb = false;
#if defined(FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT
    uart_cfg.stopBitCount = kLPUART_OneStopBit;
#endif
#if defined(FSL_FEATURE_LPUART_HAS_FIFO) && FSL_FEATURE_LPUART_HAS_FIFO
    uart_cfg.txFifoWatermark = 0U;
    uart_cfg.rxFifoWatermark = 0U;
#endif
#if defined(FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT) && FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT
    uart_cfg.enableRxRTS = false;
    uart_cfg.enableTxCTS = false;
    uart_cfg.txCtsSource = kLPUART_CtsSourcePin;
    uart_cfg.txCtsConfig = kLPUART_CtsSampleAtStart;
#endif
    uart_cfg.rxIdleType = kLPUART_IdleTypeStartBit;
    uart_cfg.rxIdleConfig = kLPUART_IdleCharacter1;
    uart_cfg.timeoutConfig.rxExtendedTimeoutValue = 0U;
    uart_cfg.timeoutConfig.txExtendedTimeoutValue = 0U;
    uart_cfg.timeoutConfig.rxCounter0.enableCounter = false;
    uart_cfg.timeoutConfig.rxCounter0.timeoutCondition = kLPUART_TimeoutAfterCharacters;
    uart_cfg.timeoutConfig.rxCounter0.timeoutValue = 0U;

    uart_cfg.timeoutConfig.rxCounter1.enableCounter = false;
    uart_cfg.timeoutConfig.rxCounter1.timeoutCondition = kLPUART_TimeoutAfterCharacters;
    uart_cfg.timeoutConfig.rxCounter1.timeoutValue = 0U;

    uart_cfg.timeoutConfig.txCounter0.enableCounter = false;
    uart_cfg.timeoutConfig.txCounter0.timeoutCondition = kLPUART_TimeoutAfterCharacters;
    uart_cfg.timeoutConfig.txCounter0.timeoutValue = 0U;

    uart_cfg.timeoutConfig.txCounter1.enableCounter = false;
    uart_cfg.timeoutConfig.txCounter1.timeoutCondition = kLPUART_TimeoutAfterCharacters;
    uart_cfg.timeoutConfig.txCounter1.timeoutValue = 0U;

    uart_cfg.enableSingleWire = false;

    uart_cfg.rtsDelay = 0U;
    uart_cfg.enableTx = true;
    uart_cfg.enableRx = true;

    status = LPUART_Init(base, &uart_cfg, srcClock_Hz);
    if(status != kStatus_Success){
        while(1);
    }
}


void HAL_uart_enableTx(LPUART_Type *base, bool enable)
{
    LPUART_EnableTx(base, enable);
}

void HAL_uart_enableRx(LPUART_Type *base, bool enable)
{
    LPUART_EnableRx(base, enable);
}

void HAL_uart_write_data(LPUART_Type *base, uint8_t data)
{
    while ((base->STAT & LPUART_STAT_TDRE_MASK) == 0U)
    {

    }
    LPUART_WriteByte(base, data);
}

uint8_t HAL_uart_read_data(LPUART_Type *base)
{
    while ((base->STAT & LPUART_STAT_RDRF_MASK) == 0U)
    {

    }
    return LPUART_ReadByte(base);
}

status_t HAL_uart_writeBlocking(LPUART_Type *base, uint8_t *data, size_t length)
{
    return LPUART_WriteBlocking(base, data, length);
}

status_t HAL_uart_readBlocking(LPUART_Type *base, uint8_t *data, size_t length)
{
    return LPUART_ReadBlocking(base, data, length);
}

void HAL_uart_write_string(LPUART_Type *base, const char *string, size_t length)
{
    if (string == NULL)
    {
        return;
    }

    while (*string != '\0')
    {
        HAL_uart_writeBlocking(base, (const uint8_t *)string, length);
        string++;
    }
}

void HAL_uart_EnableInterrupts(LPUART_Type *base, uint32_t mask)
{
    LPUART_EnableInterrupts(base, mask);
}

void HAL_uart_DisableInterrupts(LPUART_Type *base, uint32_t mask)
{
    LPUART_DisableInterrupts(base, mask);
}

void HAL_uart_TransferStartRingBuffer(LPUART_Type *base,
                                    lpuart_handle_t *handle,
                                    uint8_t *ringBuffer,
                                    size_t ringBufferSize)
{
    LPUART_TransferStartRingBuffer(base, handle, ringBuffer,ringBufferSize);

}

status_t HAL_uart_TransferReceiveNonBlocking(LPUART_Type *base,
                                           lpuart_handle_t *handle,
                                           uint8_t *data,
                                           size_t length,
                                           size_t *receivedBytes)
{
    lpuart_transfer_t received_data;
    received_data.rxData = data;
    received_data.dataSize = length;

    return LPUART_TransferReceiveNonBlocking(base, handle, &received_data, receivedBytes);

}

void HAL_uart_TransferCreateHandle(LPUART_Type *base,
                                 lpuart_handle_t *handle,
                                 lpuart_transfer_callback_t callback,
                                 void *userData)
{
    LPUART_TransferCreateHandle(base, handle, callback, userData);
}

size_t HAL_uart_TransferGetRxRingBufferLength(LPUART_Type *base, lpuart_handle_t *handle)
{
    return  LPUART_TransferGetRxRingBufferLength(base,handle);
}

