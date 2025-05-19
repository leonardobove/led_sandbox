/*
 * gpio.h
 *
 *  Created on: 2 May 2025
 *      Author: leona
 */

#ifndef LED_SANDBOX_NIOS2_INC_GPIO_H_
#define LED_SANDBOX_NIOS2_INC_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "system.h"

#define SKIP_CACHE (1 << 31)

// LEDS
#define LED_DATA_REG (*(volatile uint32_t *) (LEDS_BASE | SKIP_CACHE))

// SLIDERS
#define SLIDERS_DATA_REG      (*(volatile uint32_t *) (SLIDERS_BASE  | SKIP_CACHE))

// KEYS with edge capture
#define KEY_EDGE_REG          (*(volatile uint32_t *) ((KEYS_BASE | SKIP_CACHE) + 12))


#ifdef __cplusplus
}
#endif

#endif /* LED_SANDBOX_NIOS2_INC_GPIO_H_ */
