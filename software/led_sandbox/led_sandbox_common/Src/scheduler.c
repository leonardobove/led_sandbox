/*
 * scheduler.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include <stddef.h>

#include "../Inc/scheduler.h"

// Structure that defines a periodic task and its period
static struct {
    CallbackType cb;
    int32_t tick_counter;
    int32_t counter_reset;
} periodic_tasks[MAX_PERIODIC_TASKS];

// Number of registered tasks
static uint16_t num_tasks = 0;

// Structure that defines a one-shot event
static struct {
    CallbackType cb;
    int32_t tick_counter;
} oneshot_events[MAX_ONESHOT_EVENTS];

// Flag used to check when one system tick has elapsed
volatile uint32_t tick_flag = 0;

void hal_scheduler_init() {
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

bool hal_scheduler_add_periodic_task(uint16_t ms_period, CallbackType callback) {
    if (num_tasks == MAX_PERIODIC_TASKS) {
        return false;
    }

    periodic_tasks[num_tasks].cb = callback;
    periodic_tasks[num_tasks].counter_reset = ms_period * TICKS_PER_MS;
    periodic_tasks[num_tasks].tick_counter = ms_period * TICKS_PER_MS;

    ++num_tasks;

    return true;
}

bool hal_scheduler_add_oneshot_task(uint16_t ms_delay, CallbackType callback) 	{
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

bool hal_scheduler_tick() {
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
