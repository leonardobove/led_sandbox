/*
 * main.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include "../../led_sandbox_common/Inc/led_sandbox.h"
#include "../../led_sandbox_common/Inc/hal.h"
#include "../../led_sandbox_common/Inc/scheduler.h"
#include "../../led_sandbox_common/Inc/pixel_dust_task.h"
#include "altera_up_avalon_video_dma_controller.h"
#include "../Inc/led_matrix.h"

uint8_t pixel_buf[WIDTH * HEIGHT / 2];
uint8_t temp_buf[WIDTH * HEIGHT / 2];
alt_up_video_dma_dev* dev;

int main() {
    led_sandbox_init();

	for (uint32_t i = 0; i < WIDTH * HEIGHT / 2; i++) {
		if (i < (1 * WIDTH)) {
			temp_buf[i] = 0x1;
		}
		 else {
			temp_buf[i] = 0x0;
		}
	}
	swap_lines (temp_buf);
	for (uint32_t i = 0; i < WIDTH * HEIGHT / 2; i++) {
		pixel_buf[i] = temp_buf[i];
	}
    alt_up_video_dma_ctrl_swap_buffers(dev);

    while (1) {
        // If tick has elapsed, call scheduler
        if (tick_flag) {
            scheduler_tick();

            // Reset tick flag
            tick_flag = 0;
        }

        // Call loop subroutine
        led_sandbox_loop();
    }

    return 0;
}

