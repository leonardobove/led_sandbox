/*
 * pixel_dust_task.h
 *
 *  Created on: 19 Apr 2025
 *      Author: leona
 */

#ifndef INC_PIXEL_DUST_TASK_H_
#define INC_PIXEL_DUST_TASK_H_

//#include "../subprojects/Adafruit_PixelDust/Adafruit_PixelDust.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Useful RGB LED matrix specification definitions
#define N_GRAINS             (20u) // Number of grains of sand
#define WIDTH                (64u) // Display width in pixels
#define HEIGHT               (32u) // Display height in pixels
#define MATRIX_FPS          (100u) // Maximum redraw rate, frames/second
#define ACCELEROMETER_SCALE (255u) // The accelerometer output values will be scaled by (ACCELEROMETER_SCALE / 256)
#define GRAINS_ELASTICITY   (128u)

// Since we're not using the GFX library, it's necessary to buffer the
// display contents ourselves.
// 3 bit per pixel. Each uint8_t element contains the pixel value of the i-th row
// (first LSB bits) and of the (i+16)-th row (from bit 3 to bit 5).
extern uint8_t pixel_buf[WIDTH * HEIGHT / 2];
extern uint8_t temp_buf[WIDTH * HEIGHT / 2];
 
// Declare state machine task subroutine
void pixel_dust_task();

// Useful Macros
#define LOWER_PIXEL_MASK          (0b00000111)
#define UPPER_PIXEL_MASK          (0b00111000)
#define SET_LOWER_PIXEL(x)        ((x) << 0)
#define SET_UPPER_PIXEL(x)        ((x) << 3)
#define CLEAR_LOWER_PIXEL		  (0b11111000)
#define CLEAR_UPPER_PIXEL         (0b11000111)

#ifdef __cplusplus
}
#endif

#endif /* INC_PIXEL_DUST_TASK_H_ */
 
