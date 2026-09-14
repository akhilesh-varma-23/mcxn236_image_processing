#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "fsl_gpio.h"



#define LED_ACTIVE_HIGH  0U

void HAL_GPIO_Init(GPIO_Type *port, uint32_t pin);
void HAL_GPIO_On(GPIO_Type *port, uint32_t pin);
void HAL_GPIO_Off(GPIO_Type *port, uint32_t pin);
void HAL_GPIO_Toggle(GPIO_Type *port, uint32_t pin);

#endif /* HAL_GPIO_H */