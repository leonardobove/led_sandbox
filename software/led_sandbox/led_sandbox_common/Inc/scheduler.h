/*
 * scheduler.h
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "../Inc/hal.h"

#define MAX_PERIODIC_TASKS (10u)
#define MAX_ONESHOT_EVENTS (8u)
#define TICKS_PER_MS       (1u)

typedef void (*CallbackType)(void);

// Structure that defines a periodic task and its period
typedef struct {
    CallbackType cb;
    int32_t tick_counter;
    int32_t counter_reset;
} periodic_task_t;

// Structure that defines a one-shot event
typedef struct {
    CallbackType cb;
    int32_t tick_counter;
} oneshot_event_t;

// Flag used to check when one system tick has elapsed
extern volatile uint32_t tick_flag;

// Scheduler API
bool scheduler_add_periodic_task(uint16_t ms_period, CallbackType callback);
bool scheduler_add_oneshot_task(uint16_t ms_delay, CallbackType callback);
void scheduler_init();
// Call scheduler and increment of one tick.
// Call this function when one tick has elapsed (tick_flag set to 1).
bool scheduler_tick();

#ifdef __cplusplus
}
#endif

#endif /* INC_SCHEDULER_H_ */
