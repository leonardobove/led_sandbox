/*
 * led_sandbox.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include <assert.h>

#include "../Inc/hal.h"
#include "../Inc/scheduler.h"
#include "../Inc/led_sandbox.h"
#include "../Inc/pixel_dust_task.h"

// Task periods
#define STATE_MACHINE_TASK_PERIOD_MS (1u)
#define PIXEL_DUST_TASK_PERIOD_MS    (TICKS_PER_MS * 1000u / MATRIX_FPS)

// Task subroutine function prototypes

// Static functions declarations



void led_sandbox_init() {
    // Initialize HAL
    hal_init();

    // Register periodic tasks
    assert(scheduler_add_periodic_task(STATE_MACHINE_TASK_PERIOD_MS,
                                        state_machine_task));
	assert(scheduler_add_periodic_task(PIXEL_DUST_TASK_PERIOD_MS,
										pixel_dust_task));
}

void led_sandbox_loop() {

}
