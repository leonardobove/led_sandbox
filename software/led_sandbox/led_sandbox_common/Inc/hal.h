/*
 * hal.h
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#ifndef INC_HAL_H_
#define INC_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "scheduler.h"

// Initialize tasks scheduler and peripherals
void hal_init();

// Start and stop timers
void hal_start_timers();
void hal_stop_timers();

// Return the number of milliseconds elapsed since the start of the execution
uint32_t hal_get_millis(); // TODO: add time-stamp timer

#ifdef __cplusplus
}
#endif


#endif /* INC_HAL_H_ */
