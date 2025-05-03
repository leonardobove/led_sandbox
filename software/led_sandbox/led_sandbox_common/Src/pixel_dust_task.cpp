#include <stdbool.h>
#include <stdio.h>

#include "../Inc/pixel_dust_task.h"
#include "../Inc/state_machine_task.h"
#include "../Inc/accelerometer_average_task.h"
#include "../Inc/hal.h"

#include "../subprojects/Adafruit_PixelDust/Adafruit_PixelDust.h"

// Flag that is true every time the GSENSOR_SANDBOX state is entered
static uint32_t has_reset = true;

// Sand object, last 2 args are accelerometer scaling and grain elasticity
Adafruit_PixelDust sand(WIDTH, HEIGHT, N_GRAINS, ACCELEROMETER_SCALE, GRAINS_ELASTICITY);

uint8_t pixel_buf[WIDTH * HEIGHT]; //TODO: maybe it's not really necessary and I can use the class internal bitmap?


void pixel_dust_task() {
    if (current_state == GSENSOR_SANDBOX) {
        if (has_reset) {    // First time entering in the task
            // Initialize pixel dust grains and obstacles
            if (!sand.begin()) {
                hal_error(1);   // Malloc error
            } //TODO: define error codes in a better way
            
            
            // Initialize RGB LED Matrix driver
            //TODO

            memset(pixel_buf, 0, sizeof(pixel_buf));   // Clear pixel buffer

            sand.randomize(); // Initialize random sand positions

            // Turn initialization flag off
            has_reset = false;
        }

        // Erase old grain positions in pixel_buf[]
        uint8_t     i;
        dimension_t x, y;
        for(i = 0; i < N_GRAINS; i++) {
            sand.getPosition(i, &x, &y);
            pixel_buf[y * WIDTH + x] = 0;
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
            pixel_buf[y * WIDTH + x] = color;
        }
    } else {
        has_reset = true;
    }
}
