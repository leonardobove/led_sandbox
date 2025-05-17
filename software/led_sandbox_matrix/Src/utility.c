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

	for (int i = 0; i < (WIDTH * (HEIGHT / 2)); i++) {
		if(i < (WIDTH)) {
			temp_line[i] = frame_buffer[i];
		}
		if(i >= (((HEIGHT / 2) - 1) * WIDTH)) {
	        frame_buffer[i] = temp_line[i -(WIDTH * ((HEIGHT / 2) - 1))];
		}
		if(i < (((HEIGHT / 2) - 1) * WIDTH)) {
			frame_buffer[i] = frame_buffer[i + WIDTH];
		}
	}
}

#define CYCLES_PER_MS 574

void wait_ms(unsigned int time_ms)
{
    int i, j;
    for(j=0; j<time_ms; j++)
    {
        for(i=0; i<CYCLES_PER_MS; i++) {;}
    }
}
