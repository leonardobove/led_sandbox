/*
 * led_sandbox_hal_impl_nios2.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include "../../led_sandbox_common/Inc/hal.h"
#include "../Inc/nios2_config.h"
#include "../Inc/system_tick.h"


void hal_init() {
	// Initialize system tick
	system_tick_init(1/TICKS_PER_MS,
					(volatile uint32_t*)(&tick_flag));

	// Initialize scheduler
	scheduler_init();
}

