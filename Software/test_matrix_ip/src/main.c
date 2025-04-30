/*
 * main.c
 *
 *  Created on: 30 Apr 2025
 *      Author: leona
 */

#include <stdint.h>

#include "altera_up_avalon_video_dma_controller.h"
#include "system.h"

#define WIDTH 	(64u)
#define HEIGHT 	(16u)

int main() {
	uint16_t frame_buffer[WIDTH*HEIGHT];

	for (int i = 0; i < WIDTH*HEIGHT; i++) {
		frame_buffer[i] = 0xFFFF;
	}

	alt_up_video_dma_dev* dma_dev_handler = alt_up_video_dma_open_dev("/dev/video_dma_controller_0");
	if (alt_up_video_dma_ctrl_set_bb_addr(dma_dev_handler, frame_buffer) != 0) {
		while (1) {

		}
	}
	//alt_up_video_dma_screen_fill(dma_dev_handler, 0xFFFF, 0);
	volatile uint32_t res = 0;
	while (1) {
		if (alt_up_video_dma_ctrl_check_swap_status(dma_dev_handler)) {
			res = alt_up_video_dma_ctrl_swap_buffers(dma_dev_handler);
		}
	}
}
