/*
 * accelerometer_average_task.h
 *
 *  Created on: 25 Apr 2025
 *      Author: ale_ball
 */

#ifndef INC_ACCELEROMETER_AVERAGE_TASK_H_
#define INC_ACCELEROMETER_AVERAGE_TASK_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdint.h>
#include "../Inc/hal.h"

//Define MACROs

#define NUM_AVERAGES 	(10u)
//chosen 10 because it's a good trade-off between precision and reactivity

//Define average acceleration struct
extern accelerometer_output_t acceleration_average;
  
// Declare average acceleration task subroutine
void accelerometer_average_task();

#ifdef __cplusplus
}
#endif
 
#endif /* INC_ACCELEROMETER_AVERAGE_TASK_H_ */
 
