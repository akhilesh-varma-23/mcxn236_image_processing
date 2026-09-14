#include "hal_gpio.h"

void HAL_GPIO_Init(GPIO_Type *port, uint32_t pin)
{
    gpio_pin_config_t led_config;

    led_config.pinDirection = kGPIO_DigitalOutput;

#if (LED_ACTIVE_HIGH == 1U)
    led_config.outputLogic = 0U;
#else
    led_config.outputLogic = 1U;
#endif

    GPIO_PinInit(port, pin, &led_config);
}

void HAL_GPIO_On(GPIO_Type *port, uint32_t pin)
{
#if (LED_ACTIVE_HIGH == 1U)
    GPIO_PinWrite(port, pin, 1U);
#else
    GPIO_PinWrite(port, pin, 0U);
#endif
}

void HAL_GPIO_Off(GPIO_Type *port, uint32_t pin)
{
#if (LED_ACTIVE_HIGH == 1U)
    GPIO_PinWrite(port, pin, 0U);
#else
    GPIO_PinWrite(port, pin, 1U);
#endif
}

void HAL_GPIO_Toggle(GPIO_Type *port, uint32_t pin)
{
    GPIO_PortToggle(port, (1UL << pin));
}