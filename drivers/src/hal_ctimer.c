#include "hal_ctimer.h"

void HAL_ctimer_Init(CTIMER_Type *base, uint32_t prescale_val)
{
    ctimer_config_t ctimer_cfg;
    CTIMER_GetDefaultConfig(&ctimer_cfg);
    // uint32_t timer_clk;
    // timer_clk = CLOCK_GetCTimerClkFreq(0U);
    // ctimer_cfg.prescale = (timer_clk / 1000000U) - 1U;
    ctimer_cfg.prescale = prescale_val;
    const ctimer_config_t *ctimer_cfg_ptr = &ctimer_cfg;

    CTIMER_Init(base, ctimer_cfg_ptr);
}

void HAL_ctimer_Deinit(CTIMER_Type *base)
{
    CTIMER_Deinit(base);
}

void HAL_ctimer_GetDefaultConfig(ctimer_config_t *config)
{
    /*
 * The default values are:
 *   config->mode = kCTIMER_TimerMode;
 *   config->input = kCTIMER_Capture_0;
 *   config->prescale = 0;
 */
    CTIMER_GetDefaultConfig(config);
}

uint32_t HAL_ctimer_GetTimerCountValue(CTIMER_Type *base)
{
    return CTIMER_GetTimerCountValue(base);
}

void HAL_ctimer_SetupMatch(CTIMER_Type *base, ctimer_match_t matchChannel, uint32_t match_val)
{
    ctimer_match_config_t matchCfg;
    matchCfg.matchValue = match_val;
matchCfg.enableInterrupt = true;
matchCfg.enableCounterReset = true;
matchCfg.enableCounterStop = false;
matchCfg.outControl = false;
matchCfg.outPinInitState = false;
    CTIMER_SetupMatch(base, matchChannel, &matchCfg);
}

void HAL_ctimer_StartTimer(CTIMER_Type *base)
{
    CTIMER_StartTimer(base);
}

void HAL_ctimer_StopTimer(CTIMER_Type *base)
{
    CTIMER_StopTimer(base);
}

void HAL_ctimer_Reset(CTIMER_Type *base)
{
    CTIMER_Reset(base);
}

void HAL_ctimer_SetPrescale(CTIMER_Type *base, uint32_t prescale)
{
    CTIMER_SetPrescale(base, prescale);
}

uint32_t HAL_ctimer_GetStatusFlags(CTIMER_Type *base)
{
    return CTIMER_GetStatusFlags(base);
}

void HAL_ctimer_ClearStatusFlags(CTIMER_Type *base, uint32_t mask)
{
    CTIMER_ClearStatusFlags(base, mask);
}

uint32_t HAL_ctimer_GetCaptureValue(CTIMER_Type *base, ctimer_capture_channel_t capture)
{
    return CTIMER_GetCaptureValue(base, capture);
}

void HAL_ctimer_EnableInterrupts(CTIMER_Type *base, uint32_t mask)
{
    CTIMER_EnableInterrupts(base, mask);
}

void HAL_ctimer_DisableInterrupts(CTIMER_Type *base, uint32_t mask)
{
    CTIMER_DisableInterrupts(base, mask);
}

// static volatile uint32_t irq_timer_ticks_count = 0U;
// uint32_t HAL_ctimer_getTicks(void)
// {
//     return irq_timer_ticks_count;
// }

// void HAL_ctimer_IncrementTick(void)
// {
//     irq_timer_ticks_count++;
// }

static ctimer_callback_t timer_callback;
void HAL_ctimer_RegisterCallBack(CTIMER_Type *base, ctimer_callback_t cb_func, ctimer_callback_type_t cb_type)
{
    timer_callback = cb_func;
    CTIMER_RegisterCallBack(base, &timer_callback, cb_type);
}