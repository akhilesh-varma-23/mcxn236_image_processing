
// #include "main.h"

// static void delay(void)
// {
//     volatile uint32_t count;

//     for (count = 0U; count < 1000000U; count++)
//     {
//         __asm volatile ("nop");
//     }
// }

// int main(void)
// {
//     /* Initialize clocks required by PORT4 and GPIO4 */
//     HAL_CLOCK_Init();

//     /* Configure P4_17, P4_18 and P4_19 as GPIO */
//     HAL_PINMUX_Init(LED_PORT, LED_PIN_R);
//     HAL_PINMUX_Init(LED_PORT, LED_PIN_G);
//     HAL_PINMUX_Init(LED_PORT, LED_PIN_B);

//     /* Configure P4_17, P4_18 and P4_19 as outputs */
//     HAL_GPIO_Init(LED_GPIO, LED_PIN_R);
//     HAL_GPIO_Init(LED_GPIO, LED_PIN_G);
//     HAL_GPIO_Init(LED_GPIO, LED_PIN_B);

//     while (1)
//     {
//         /* Toggle all three LEDs together */
//         HAL_GPIO_Toggle(LED_GPIO, LED_PIN_R);
//         HAL_GPIO_Toggle(LED_GPIO, LED_PIN_G);
//         HAL_GPIO_Toggle(LED_GPIO, LED_PIN_B);

//         delay();
//     }
// }

// #include "main.h"

// static void delay(void)
// {
//     volatile uint32_t count;

//     for (count = 0U; count < 1000000U; count++)
//     {
//         __asm volatile ("nop");
//     }
// }

// int main(void)
// {
//     HAL_CLOCK_Init();

//     HAL_PINMUX_Init(PORT4, 18U);
//     HAL_GPIO_Init(GPIO4, 18U);

//     while (1)
//     {
//         HAL_GPIO_On(GPIO4, 18U);
//         delay();

//         HAL_GPIO_Off(GPIO4, 18U);
//         delay();
//     }
// }

#include "main.h"

int main(void)
{
    HAL_CLOCK_Init();

    HAL_PINMUX_Init(PORT4, 18U);
    HAL_GPIO_Init(GPIO4, 18U);

    /* Force P4_18 ON */
    HAL_GPIO_On(GPIO4, 18U);

    while (1)
    {
    }
}