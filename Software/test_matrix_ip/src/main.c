/*
 * main.c
 *
 *  Created on: 30 Apr 2025
 *      Author: leona
 */

#include <stdint.h>

#include "altera_up_avalon_video_dma_controller.h"
#include "io.h"
#include "system.h"

#define WIDTH 	(64u)
#define HEIGHT 	(16u)

int main() {
	uint16_t frame_buffer[WIDTH*HEIGHT];

	for (int i = 0; i < WIDTH*HEIGHT; i++) {
		frame_buffer[i] = (uint32_t)0b100001;
	}

	IOWR(VIDEO_DMA_CONTROLLER_0_BASE, 0, (unsigned int)(&frame_buffer[0]));
	IOWR(VIDEO_DMA_CONTROLLER_0_BASE, 3, 1 << 2);
	while (1) {

	}
}
