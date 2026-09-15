#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#include "hal_clock.h"
#include "hal_pinmux.h"
#include "hal_gpio.h"
#include "MCXN236.h"                  /* Device specific peripheral access layer header file */
// #include "MCXN236_COMMON.h"



/* LED configuration - update these after confirming your board LED */
#define LED_GPIO         GPIO4       /* PLACEHOLDER */
#define LED_PIN          18U          /* PLACEHOLDER */
#define LED_PIN_R 17U 
#define LED_PIN_G 18U 
#define LED_PIN_B 19U
/* Replace these after confirming the actual LED pin */
#define LED_PORT    PORT4

static void delay(void);
int main(void);


#endif /* MAIN_H */