
#ifndef HAL_PINMUX_H
#define HAL_PINMUX_H

#include "fsl_port.h"



void HAL_PINMUX_Init(PORT_Type *port, uint32_t pin, port_mux_t mux);

#endif /* HAL_PINMUX_H */

