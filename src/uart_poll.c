#include "uart_poll.h"

int uart_poll_main(void)
{
    uint8_t receive_data_buffer[RX_BUFFER_SIZE] = {0};
    uint8_t received_data;
    static const char message[] = "MCX-N236 polling UART started\r\n";

    SYSCON->FCCLKSEL[4U] = 2U;
    SYSCON->FLEXCOMMCLKDIV[4U] = 0U;
    HAL_CLOCK_Init(kCLOCK_LPUart4);

    /*
     * P1_8 = FC4_P0 = LPUART4 RX
     * Select ALT2.
     */
    HAL_PINMUX_Init(PORT1, 8U, kPORT_MuxAlt2);

    /*
     * P1_9 = FC4_P1 = LPUART4 TX
     * Select ALT2.
     */
    HAL_PINMUX_Init(PORT1, 9U, kPORT_MuxAlt2);

    uint32_t lpuart_source_clock_hz = CLOCK_GetLPFlexCommClkFreq(4U);
    HAL_uart_init(LPUART4, lpuart_source_clock_hz);

    (void)HAL_uart_write_string(LPUART4, message, sizeof(message) - 1U);

    while (1)
    {
        if (HAL_uart_readBlocking(LPUART4, &received_data, sizeof(received_data)) == kStatus_Success)
        {
            HAL_uart_writeBlocking(LPUART4, &received_data, sizeof(received_data));
        }
    }
}