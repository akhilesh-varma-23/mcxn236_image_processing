#ifndef HAL_CTIMER_H
#define HAL_CTIMER_H

#include "fsl_ctimer.h"

void HAL_ctimer_Init(CTIMER_Type *base, uint32_t prescale_val);
void HAL_ctimer_Deinit(CTIMER_Type *base);
void HAL_ctimer_GetDefaultConfig(ctimer_config_t *config);
uint32_t HAL_ctimer_GetTimerCountValue(CTIMER_Type *base);
void HAL_ctimer_SetupMatch(CTIMER_Type *base, ctimer_match_t matchChannel, uint32_t match_val);
void HAL_ctimer_StartTimer(CTIMER_Type *base);
void HAL_ctimer_StopTimer(CTIMER_Type *base);
void HAL_ctimer_Reset(CTIMER_Type *base);
void HAL_ctimer_SetPrescale(CTIMER_Type *base, uint32_t prescale);
uint32_t HAL_ctimer_GetStatusFlags(CTIMER_Type *base);
void HAL_ctimer_ClearStatusFlags(CTIMER_Type *base, uint32_t mask);
uint32_t HAL_ctimer_GetCaptureValue(CTIMER_Type *base, ctimer_capture_channel_t capture);
void HAL_ctimer_EnableInterrupts(CTIMER_Type *base, uint32_t mask);
void HAL_ctimer_DisableInterrupts(CTIMER_Type *base, uint32_t mask);
// uint32_t HAL_ctimer_getTicks(void);
// void HAL_ctimer_IncrementTick(void);
void HAL_ctimer_RegisterCallBack(CTIMER_Type *base, ctimer_callback_t cb_func, ctimer_callback_type_t cb_type);

#endif /* HAL_CTIMER_H */