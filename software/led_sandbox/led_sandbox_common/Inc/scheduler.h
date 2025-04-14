/*
 * scheduler.h
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include <stdbool.h>

#include "../Inc/hal.h"

#define MAX_PERIODIC_TASKS 10u
#define MAX_ONESHOT_EVENTS 8u
#define TICKS_PER_MS 1

typedef void (*CallbackType)(void);

// Flag used to check when one system tick has elapsed
extern volatile uint32_t tick_flag;

// Scheduler API
bool hal_scheduler_add_periodic_task(uint16_t ms_period, CallbackType callback);
bool hal_scheduler_add_oneshot_task(uint16_t ms_delay, CallbackType callback);
void hal_scheduler_init();
// Call scheduler and increment of one tick.
// Call this function when one tick has elapsed (tick_flag set to 1).
bool hal_scheduler_tick();

#endif /* INC_SCHEDULER_H_ */
