/*
 * hal.h
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#ifndef INC_HAL_H_
#define INC_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// Initialize tasks scheduler and peripherals
void hal_init();

// Start and stop timers
void hal_start_timers();
void hal_stop_timers();

// UI peripherals HAL interface
uint32_t hal_read_switches();
uint32_t hal_read_sliders();

// Accelerometer sensor HAL interface
typedef struct {
    int32_t a_x;
    int32_t a_y;
    int32_t a_z;
} accelerometer_output_t;

//Initialization and read functions
bool hal_accelerometer_init();
accelerometer_output_t hal_read_accelerometer();

// LED matrix utility functions
void hal_shift_rows(uint8_t *temp_buf);
void hal_write8_bypass_cache(uint8_t* base, uint32_t offset, uint8_t data);

// Error return function
void hal_error(uint32_t error_code);

#ifdef __cplusplus
}
#endif


#endif /* INC_HAL_H_ */
