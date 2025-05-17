/*
 * main.c
 *
 *  Created on: 3 May 2025
 *      Author: leona
 */

#include <stdint.h>

#include "..\test_led_matrix_ip_bsp\drivers\inc\altera_up_avalon_video_dma_controller.h"
#include "system.h"
#include "../Inc/utility.h"



int main() {
	uint8_t frame_buffer[WIDTH * HEIGHT / 2];
	uint8_t temp_buffer[WIDTH * HEIGHT / 2];
	uint8_t p = 0;

	alt_up_video_dma_dev* dev = alt_up_video_dma_open_dev("/dev/video_dma_controller_0");
	alt_up_video_dma_ctrl_set_bb_addr(dev, (unsigned int)(&temp_buffer[0]));


	while (1) {
		for (int i = 0; i < WIDTH*(HEIGHT / 2); i++) {
			if (i < (p % WIDTH)) {
				frame_buffer[i] = (RED_L | RED_H);
			}
			else {
				if((i >= (WIDTH * ((HEIGHT / 2) - 1))) && (i < ((((HEIGHT / 2) - 1) * WIDTH) + (p % WIDTH)))){
					frame_buffer[i] = (BLUE_L | BLUE_H);
				}
			    else {
				    frame_buffer[i] = (BLACK_L | BLACK_H);
			    }
			}
		}
		swap_lines (frame_buffer);
		for(uint32_t j = 0; j < WIDTH*(HEIGHT / 2); j++) {
			temp_buffer[j] = frame_buffer[j];
		}
//		alt_up_video_dma_ctrl_swap_buffers(dev);
		if(p == 255) p = 0;
		else p++;
		wait_ms(100);
	}
}
