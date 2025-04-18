/*
 * state_machine_task.h
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#ifndef INC_STATE_MACHINE_TASK_H_
#define INC_STATE_MACHINE_TASK_H_

#include <stdint.h>

// Define FSM states and declare current/next state variables
typedef enum {
	RESET               = 0,
	IDLE                = 1,
	GSENSOR_SANDBOX     = 2,
	GESTURE_RECOGNITION = 3,
} fsm_state_t;

extern fsm_state_t current_state, next_state;

// Define FSM inputs
typedef struct {
	uint32_t switch_inputs;
	uint32_t key_inputs;
} fsm_inputs_t;

// Define FSM outputs
typedef struct {
	uint32_t out_test;
} fsm_outputs_t;

// Declare state machine task subroutine
void state_machine_task();

#endif /* INC_STATE_MACHINE_TASK_H_ */
