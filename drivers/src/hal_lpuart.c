#include "hal_lpuart.h"

void hal_uart_init(LPUART_Type *base, uint32_t srcClock_Hz)
{
    status_t status;
    lpuart_config_t uart_cfg;

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


void hal_uart_enableTx(LPUART_Type *base, bool enable)
{
    LPUART_EnableTx(base, enable);
}

void hal_uart_enableRx(LPUART_Type *base, bool enable)
{
    LPUART_EnableRx(base, enable);
}

void hal_uart_write_data(LPUART_Type *base, uint8_t data)
{
    LPUART_WriteByte(base, data);
}
