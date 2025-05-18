#include <stdbool.h>
#include <stdio.h>

#include "../Inc/pixel_dust_task.h"
#include "../Inc/state_machine_task.h"
#include "../Inc/accelerometer_average_task.h"
#include "../Inc/hal.h"

#include "../subprojects/Adafruit_PixelDust/Adafruit_PixelDust.h"
#include "altera_up_avalon_video_dma_controller.h"
#include "../../led_sandbox_nios2/Inc/led_matrix.h"



// Flag that is true every time the GSENSOR_SANDBOX state is entered
static uint32_t has_reset = true;

// Sand object, last 2 args are accelerometer scaling and grain elasticity
Adafruit_PixelDust sand(WIDTH, HEIGHT, N_GRAINS, ACCELEROMETER_SCALE, GRAINS_ELASTICITY);

// Frame buffers
uint8_t pixel_buf[WIDTH * HEIGHT / 2];
uint8_t pixel_back_buf[WIDTH * HEIGHT / 2];
uint8_t temp_buf[WIDTH * HEIGHT / 2];

void pixel_dust_task() {
    if (current_state == GSENSOR_SANDBOX) {
        if (has_reset) {    // First time entering in the task
            // Initialize pixel dust grains and obstacles
            if (!sand.begin()) {
                hal_error(1);   // Malloc error
            }
            
            // Initialize RGB LED Matrix driver
            memset(pixel_buf, 0, sizeof(pixel_buf));   // Clear pixel front buffer
            memset(pixel_back_buf, 0, sizeof(pixel_back_buf));   // Clear pixel back buffer
            memset(temp_buf, 0, sizeof(temp_buf));	// Clear temporary buffer

            sand.randomize(); // Initialize random sand positions

            // Turn initialization flag off
            has_reset = false;
        }

        // Erase old grain positions in pixel_buf[]
        dimension_t x, y;
        for(uint32_t i = 0; i < N_GRAINS; i++) {
            sand.getPosition(i, &x, &y);
            if (y >= (HEIGHT / 2)) {	// If the grain is in the upper half, erase the upper pixel
            	pixel_back_buf[(y % (HEIGHT / 2)) * WIDTH + x] &= CLEAR_UPPER_PIXEL;
            } else {	// Otherwise erase the lower pixel
            	pixel_back_buf[(y % (HEIGHT / 2)) * WIDTH + x] &= CLEAR_LOWER_PIXEL;
            }
        }

        // Run one frame of the simulation
        // X & Y axes are flipped around here to match physical mounting
        sand.iterate(acceleration_average.a_x, acceleration_average.a_y, acceleration_average.a_z);
        printf("Iteration\n");

        // Draw new grain positions in pixel_buf[]
        grain_color_t color = BLACK;
        for(uint32_t i = 0; i < N_GRAINS; i++) {
            sand.getPosition(i, &x, &y);
            sand.getColor(i, &color);
            if (y >= (HEIGHT / 2)) { // If the grain is in the upper half, set the upper pixel
            	pixel_back_buf[(y % (HEIGHT / 2)) * WIDTH + x] |= SET_UPPER_PIXEL((uint8_t)color);
            } else { // Otherwise set the lower pixel
            	pixel_back_buf[(y % (HEIGHT / 2)) * WIDTH + x] |= SET_LOWER_PIXEL((uint8_t)color);
            }
        }

        for (uint32_t i = 0; i < WIDTH * HEIGHT / 2; i++) {
    		temp_buf[i] = pixel_back_buf[i];
    	}

    	hal_shift_rows(temp_buf);

    	//hal_update_frame();

    	for (uint32_t i = 0; i < WIDTH * HEIGHT / 2; i++) {
    		pixel_buf[i] = temp_buf[i];
    	}
        
    } else {
        has_reset = true;
    }
}
