#include "uart_interrupt.h"

#define UART_RX_RING_BUFFER_SIZE (128U)

static volatile bool uart_rx_complete = false;
static volatile status_t uart_rx_error = kStatus_Success;
static lpuart_handle_t uart_handle;
static uint8_t uart_ring_buffer[UART_RX_RING_BUFFER_SIZE] = {0};
static uint8_t received_data;

static void uart_callback(
    LPUART_Type *base,
    lpuart_handle_t *handle,
    status_t status,
    void *userData)
{
    (void)base;
    (void)handle;
    (void)userData;

    switch (status)
    {
    case kStatus_LPUART_RxIdle:
        /*
         * The requested number of bytes was received.
         */
        uart_rx_complete = true;
        break;

    case kStatus_LPUART_RxRingBufferOverrun:
    case kStatus_LPUART_RxHardwareOverrun:
    case kStatus_LPUART_NoiseError:
    case kStatus_LPUART_FramingError:
    case kStatus_LPUART_ParityError:
        /*
         * Record the error and handle it in main().
         */
        uart_rx_error = status;
        break;

    default:
        break;
    }
}

int uart_interrupt_main(void)
{
    size_t ring_buffer_length;
    static const char message[] = "MCX-N236 interrupt UART started\r\n";

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

    /*
     * Then create the SDK transactional handle.
     */
    HAL_uart_TransferCreateHandle(LPUART4, &uart_handle, uart_callback, NULL);

    /*
     * Install the background ring buffer.
     */
    HAL_uart_TransferStartRingBuffer(LPUART4, &uart_handle, uart_ring_buffer, sizeof(uart_ring_buffer));

    size_t receivedBytes = 0U;
    uart_rx_complete = false;
    status_t status;

    while (1)
    {
        ring_buffer_length = HAL_uart_TransferGetRxRingBufferLength(LPUART4, &uart_handle);
        if (ring_buffer_length > 0U)
        {

            /*
             * Submit the next one-byte interrupt receive.
             */
            receivedBytes = 0U;

            status = HAL_uart_TransferReceiveNonBlocking(
                LPUART4,
                &uart_handle,
                &received_data,
                sizeof(received_data),
                &receivedBytes);

            if (status != kStatus_Success)
            {
                while (1)
                {
                }
            }
            if (receivedBytes == sizeof(received_data))
            {
                /*
                 * Echo using polling/blocking TX.
                 */
                status = HAL_uart_writeBlocking(LPUART4, &received_data, sizeof(received_data));

                if (status != kStatus_Success)
                {

                    while (1)
                        ;
                }
            }
        }

        if (uart_rx_error != kStatus_Success)
        {
            /*
             * Record or handle the error before clearing it.
             */
            uart_rx_error = kStatus_Success;
        }

        /*
         * Other application code can execute here.
         */
    }
}