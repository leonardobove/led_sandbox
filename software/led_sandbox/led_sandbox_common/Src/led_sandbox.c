/*
 * led_sandbox.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include <assert.h>

#include "../Inc/hal.h"
#include "../Inc/led_sandbox.h"

// Task periods
#define STATE_MACHINE_TASK_PERIOD_MS (1u)

// Task subroutine function prototypes

// Static functions declarations



void led_sandbox_init() {
	// Initialize HAL
	hal_init();

	// Register periodic tasks
	assert(hal_scheduler_add_periodic_task(STATE_MACHINE_TASK_PERIOD_MS,
										   state_machine_task));
}

void led_sandbox_loop() {

}
