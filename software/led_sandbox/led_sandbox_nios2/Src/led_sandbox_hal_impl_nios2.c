/*
 * led_sandbox_hal_impl_nios2.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../led_sandbox_common/Inc/hal.h"
#include "../../led_sandbox_common/Inc/scheduler.h"
#include "../Inc/nios2_config.h"
#include "../Inc/system_tick.h"


void hal_init() {
    // Initialize system tick
    system_tick_init(1/TICKS_PER_MS,
                    (volatile uint32_t*)(&tick_flag));

    // Initialize scheduler
    scheduler_init();
}

uint32_t hal_read_sliders() {

}

uint32_t hal_read_switches() {

}

bool hal_accelerometer_init() {

}

accelerometer_output_t hal_read_accelerometer() {

}


void hal_error(uint32_t error_code) {
	printf("Error %d", error_code);
}

