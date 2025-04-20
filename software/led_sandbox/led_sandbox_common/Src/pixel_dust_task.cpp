#include <stdbool.h>
#include <stdio.h>

#include "../Inc/pixel_dust_task.h"
#include "../Inc/state_machine_task.h"
#include "../Inc/hal.h"

// Flag that is true every time the GSENSOR_SANDBOX state is entered
static uint32_t has_reset = true;

// Sand object, last 2 args are accelerometer scaling and grain elasticity
Adafruit_PixelDust sand(WIDTH, HEIGHT, N_GRAINS, ACCELEROMETER_SCALE, GRAINS_ELASTICITY);

uint8_t pixel_buf[WIDTH * HEIGHT];

// Variable to hold the return values from the accelerometer
static accelerometer_output_t acceleration = {
    .a_x = 0,
    .a_y = 0,
    .a_z = 0
};

void pixel_dust_task() {
    if (current_state == GSENSOR_SANDBOX) {
        if (has_reset) {    // First time entering in the task
            // Initialize pixel dust grains and obstacles
            if (!sand.begin()) {
                hal_error(1);   // Malloc error
            } //TODO: define error codes in a better way
            
            if (!hal_accelerometer_init()) {
                hal_error(2);   // Accelerometer initialization error
            }
            
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

        // Read accelerometer
        acceleration = hal_read_accelerometer();

        // Run one frame of the simulation
        // X & Y axes are flipped around here to match physical mounting
        sand.iterate(acceleration.a_x, acceleration.a_y, acceleration.a_z);

        // Draw new grain positions in pixel_buf[]
        for(uint32_t i = 0; i < N_GRAINS; i++) {
            sand.getPosition(i, &x, &y);
            pixel_buf[y * WIDTH + x] = RED;
        }
    } else {
        has_reset = true;
    }
}