/*
 * scheduler.cpp
 *
 *  Created on: 26 apr 2025
 *      Author: aless
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "../Inc/scheduler.h"

// Static array of periodic tasks
static periodic_task_t periodic_tasks[MAX_PERIODIC_TASKS];

// Number of registered tasks
static uint16_t num_tasks = 0;

// Static array of one-shot events
static oneshot_event_t oneshot_events[MAX_ONESHOT_EVENTS];

// Flag used to check when one system tick has elapsed
volatile uint32_t tick_flag = 0;

void scheduler_init() {
    for (size_t i = 0u; i < MAX_PERIODIC_TASKS; ++i)
    {
        periodic_tasks[i].cb = NULL;
        periodic_tasks[i].counter_reset = 0u;
        periodic_tasks[i].tick_counter = 0u;
    }

    for (size_t i = 0u; i < MAX_ONESHOT_EVENTS; ++i)
    {
        oneshot_events[i].cb = NULL;
        oneshot_events[i].tick_counter = 0u;
    }
}

bool scheduler_add_periodic_task(uint16_t ms_period, CallbackType callback) {
    if (num_tasks == MAX_PERIODIC_TASKS) {
        return false;
    }

    periodic_tasks[num_tasks].cb = callback;
    periodic_tasks[num_tasks].counter_reset = ms_period * TICKS_PER_MS;
    periodic_tasks[num_tasks].tick_counter = ms_period * TICKS_PER_MS;

    ++num_tasks;

    return true;
}

bool scheduler_add_oneshot_task(uint16_t ms_delay, CallbackType callback)     {
    bool ret = false;

    for (size_t i = 0u; i < MAX_ONESHOT_EVENTS; ++i)
    {
        if (oneshot_events[i].cb == NULL)
        {
            oneshot_events[i].cb = callback;
            oneshot_events[i].tick_counter = ms_delay * TICKS_PER_MS;

            ret = true;
            break;
        }
    }

    return ret;
}

bool scheduler_tick() {
    for (uint16_t i = 0; i < num_tasks; i++) {
        periodic_tasks[i].tick_counter -= 1;

        if (periodic_tasks[i].tick_counter <= 0) {
            periodic_tasks[i].cb();
            periodic_tasks[i].tick_counter += periodic_tasks[i].counter_reset;
        }
    }

    for (size_t i = 0u; i < MAX_ONESHOT_EVENTS; ++i)
    {
        if (oneshot_events[i].cb != NULL)
        {
            oneshot_events[i].tick_counter -= 1;

            if (oneshot_events[i].tick_counter <= 0)
            {
                oneshot_events[i].cb();

                oneshot_events[i].cb = NULL;
                oneshot_events[i].tick_counter = 0;
            }
        }
    }

    return true;
}

#ifdef __cplusplus
}
#endif





