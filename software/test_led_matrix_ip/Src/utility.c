/*
 * utility.c
 *
 *  Created on: 15 mag 2025
 *      Author: termi
 */


#include "../Inc/utility.h"
#include <stdint.h>

void swap_lines (uint8_t *frame_buffer) {
	uint8_t temp_line[WIDTH];

	for (int i = 0; i < (WIDTH * HEIGHT); i++) {
		if(i < (WIDTH)) {
			temp_line[i] = frame_buffer[i];
		}
		else {
		    if(i >= ((HEIGHT - 1) * WIDTH)) {
			frame_buffer[i] = temp_line[i -(WIDTH * (HEIGHT - 1))];
		}
		    else {
			    frame_buffer[i - (WIDTH)] = frame_buffer[i];
		    }
		}
	}
}
