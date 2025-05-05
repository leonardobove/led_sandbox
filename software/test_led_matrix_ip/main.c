/*
 * main.c
 *
 *  Created on: 3 May 2025
 *      Author: leona
 */

#include <stdint.h>

#include "altera_up_avalon_video_dma_controller.h"
#include "io.h"
#include "system.h"

#define WIDTH 	(64u)
#define HEIGHT 	(16u)

int main() {
	uint32_t frame_buffer[WIDTH*HEIGHT];

	for (int i = 0; i < WIDTH*HEIGHT; i++) {
		//if (i < WIDTH) {
			//frame_buffer[i] = (uint32_t)0b001001;
		//} else {
			//frame_buffer[i] = (uint32_t)0b000000;
		//}
		frame_buffer[i] = (uint16_t)0b000001;
	}

	alt_up_video_dma_dev* dev = alt_up_video_dma_open_dev("/dev/video_dma_controller_0");
	if (0 != alt_up_video_dma_ctrl_set_bb_addr(dev, (unsigned int)(&frame_buffer[0]))) {
		while (1) {

		}
	}

	alt_up_video_dma_ctrl_swap_buffers(dev);
	//IOWR(VIDEO_DMA_CONTROLLER_0_BASE, 0, (unsigned int)(&frame_buffer[0]));
	//IOWR(VIDEO_DMA_CONTROLLER_0_BASE, 3, 1 << 2);
	while (1) {

	}
}
