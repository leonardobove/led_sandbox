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
#include "../../led_sandbox_common/Inc/pixel_dust_task.h"
#include "../Inc/nios2_config.h"
#include "../Inc/system_tick.h"
#include "../Inc/accelerometer.h"
#include "../Inc/gpio.h"
#include "../Inc/led_matrix.h"


void hal_init() {
    // Initialize system tick
    system_tick_init(1/TICKS_PER_MS,
                    (volatile uint32_t*)(&tick_flag));

    // Initialize scheduler
    scheduler_init();

    // Initialize DMA
    DMA_ENABLE((unsigned int)(&pixel_buf));
    DMA_START;
}

// GPIO
uint32_t hal_read_sliders() {
	uint32_t val = SLIDERS_DATA_REG;
	LED_DATA_REG = val;
	return SLIDERS_DATA_REG;
}

uint32_t hal_read_switches() {
	uint32_t val = KEY_EDGE_REG; //TODO: make another function to clean edge detection
	KEY_EDGE_REG = 0xFFFFFFFF;
	return val;
}

// Accelerometer

// Static structure to hold the current read value from the sensor
bool hal_accelerometer_init() {
	accelerometer_init();
	return true;
}

accelerometer_output_t hal_read_accelerometer() {
	accelerometer_data_t data;
	accelerometer_get_data_raw(&data);

	accelerometer_output_t output_data = {
			.a_x = data.x,
			.a_y = data.y,
			.a_z = data.z
	};
	return output_data;
}

// Miscellaneous
void hal_error(uint32_t error_code) {
	printf("Error %d", (int)error_code);
}

