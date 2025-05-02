/*
 * pixel_dust_task.h
 *
 *  Created on: 19 Apr 2025
 *      Author: leona
 */

#ifndef INC_PIXEL_DUST_TASK_H_
#define INC_PIXEL_DUST_TASK_H_

#include "../subprojects/Adafruit_PixelDust/Adafruit_PixelDust.h"

#ifdef __cplusplus
extern "C" {
#endif

// Useful RGB LED matrix specification definitions
#define N_GRAINS             (20u) // Number of grains of sand
#define WIDTH                (64u) // Display width in pixels
#define HEIGHT               (32u) // Display height in pixels
#define MATRIX_FPS          (100u) // Maximum redraw rate, frames/second
#define ACCELEROMETER_SCALE (255u) // The accelerometer output values will be scaled by (ACCELEROMETER_SCALE / 256)
#define GRAINS_ELASTICITY   (128u)

// Since we're not using the GFX library, it's necessary to buffer the
// display contents ourselves (8 bits/pixel with the Charlieplex drivers).
extern uint8_t pixel_buf[WIDTH * HEIGHT];
 
// Declare state machine task subroutine
void pixel_dust_task();

#ifdef __cplusplus
}
#endif

#endif /* INC_PIXEL_DUST_TASK_H_ */
 