
#include "timer_interrupt.h"

static volatile uint32_t timer_ticks = 0U;

uint32_t HAL_ctimer_getTicks(void)
{
    return timer_ticks;
}

void HAL_ctimer_IncrementTick(void)
{
    timer_ticks++;
}

static void CTIMER0_Callback(uint32_t flags)
{
    (void)flags;

    HAL_ctimer_IncrementTick();
}

int main(void)
{
    volatile uint32_t previous_tick = 0U;

    SYSCON->FCCLKSEL[4U] = 2U;
    SYSCON->FLEXCOMMCLKDIV[4U] = 0U;
    HAL_CLOCK_Init(kCLOCK_Timer0);

    HAL_CLOCK_Init(kCLOCK_Port4);
    HAL_CLOCK_Init(kCLOCK_Gpio4);

    HAL_PINMUX_Init(PORT4, 18U, kPORT_MuxAsGpio);
    HAL_GPIO_Init(GPIO4, 18U);

    
    HAL_ctimer_Init(CTIMER0, 47U);

    HAL_ctimer_SetupMatch(CTIMER0, kCTIMER_Match_0, 1000000U);

    /* Register callback */
    HAL_ctimer_RegisterCallBack(CTIMER0, CTIMER0_Callback, kCTIMER_SingleCallback);

    NVIC_SetPriority(CTIMER0_IRQn, 3U);
    NVIC_EnableIRQ(CTIMER0_IRQn);

    HAL_ctimer_StartTimer(CTIMER0);

    while(1)
    {
        volatile uint32_t current_tick = HAL_ctimer_getTicks();
        if ((current_tick - previous_tick) >= 1U)
        {
            previous_tick = current_tick;
            HAL_GPIO_Toggle(GPIO4, 18U);
        }

    }

}