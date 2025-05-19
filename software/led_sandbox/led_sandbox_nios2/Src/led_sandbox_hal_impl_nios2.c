/*
 * led_sandbox_hal_impl_nios2.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../../led_sandbox_common/Inc/hal.h"
#include "../../led_sandbox_common/Inc/scheduler.h"
#include "../../led_sandbox_common/Inc/pixel_dust_task.h"
#include "../Inc/nios2_config.h"
#include "../Inc/system_tick.h"
#include "../Inc/accelerometer.h"
#include "../Inc/gpio.h"
#include "../Inc/led_matrix.h"
#include "altera_up_avalon_video_dma_controller.h"

alt_up_video_dma_dev* dev;

void hal_init() {
    // Initialize system tick
    system_tick_init(1/TICKS_PER_MS,
                    (volatile uint32_t*)(&tick_flag));

    // Initialize scheduler
    scheduler_init();

    // Initialize DMA
    dev = alt_up_video_dma_open_dev("/dev/video_dma_controller_0");

    // Clear pixel buffer for first use
    memset(pixel_back_buf, 0, sizeof(pixel_back_buf));
	for (uint32_t i = 0; i < WIDTH * HEIGHT / 2; i++) {
		IOWR_8DIRECT(&pixel_buf[0], i, 0);
	}

    // Set front and back DMA buffer addresses.
    // The front buffer contains the frame that will be effectively displayed
    // The front buffer address cannot be directly set, because it is a read-only register
    hal_set_back_buf_addr((unsigned int)(&pixel_buf[0])); // Load the front buffer address onto the back buffer address register
    hal_swap_buffers();	// Swap the front and back buffer addresses, so to set the front buffer address to "pixel_buf"
    while (hal_check_swap_status() != 0) {;} // Wait for the swap to effectively occur
    //hal_set_back_buf_addr((unsigned int)(&temp_buf[0])); // Load the back buffer address onto the back buffer address register
}

// GPIO
uint32_t hal_read_sliders() {
	uint32_t val = SLIDERS_DATA_REG;
	LED_DATA_REG = val;
	return SLIDERS_DATA_REG;
}

uint32_t hal_read_switches() {
	uint32_t val = KEY_EDGE_REG;
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

// Hal for errors
void hal_error(uint32_t error_code) {
	printf("Error %d", (int)error_code);
}

// This function is used to fix via software the 1 row offset in the LED matrix.
// Each row is shifted back by one.
void hal_shift_rows(uint8_t *temp_buf) {
	uint8_t temp_line[WIDTH];

	for (int i = 0; i < (WIDTH * (HEIGHT / 2)); i++) {
		if(i < (WIDTH)) {
			temp_line[i] = temp_buf[i];
		}
		if(i >= (((HEIGHT / 2) - 1) * WIDTH)) {
	        temp_buf[i] = temp_line[i -(WIDTH * ((HEIGHT / 2) - 1))];
		}
		if(i < (((HEIGHT / 2) - 1) * WIDTH)) {
			temp_buf[i] = temp_buf[i + WIDTH];
		}
	}
}

void hal_set_back_buf_addr(unsigned int addr) {
	alt_up_video_dma_ctrl_set_bb_addr(dev, addr);
}

void hal_swap_buffers(void) {
	alt_up_video_dma_ctrl_swap_buffers(dev);
	return;
}

int hal_check_swap_status(void) {
	return alt_up_video_dma_ctrl_check_swap_status(dev);
}

void hal_update_frame(void) {
	hal_swap_buffers();
	while (hal_check_swap_status() != 0) {;}
	hal_swap_buffers();
	while (hal_check_swap_status() != 0) {;}
}
