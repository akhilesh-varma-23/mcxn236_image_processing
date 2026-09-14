
#include "hal_pinmux.h"
#include "fsl_port.h"

void HAL_PINMUX_Init(PORT_Type *port, uint32_t pin)
{
    /*
     * Configure the LED pin as GPIO.
     *
     * Replace PORTx and LED_PIN with the
     * actual LED port/pin for your MCXN236 board.
     */
    PORT_SetPinMux(port, pin, kPORT_MuxAsGpio);
}

