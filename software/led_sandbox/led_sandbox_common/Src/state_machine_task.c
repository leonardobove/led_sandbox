/*
 * state_machine_task.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include <stdio.h>

#include "../Inc/state_machine_task.h"

// Initialize current/next state
fsm_state_t current_state = RESET;
fsm_state_t next_state = RESET;

void state_machine_task() {
	// Evaluate next state based on current state and inputs
	switch (current_state) {
		case RESET:
			printf("Hello");
			break;

		case IDLE:
			break;

		case GSENSOR_SANDBOX:
			break;

		case GESTURE_RECOGNITION:
			break;

		default:
			printf("default");
			break;

	}

	// Update FSM state
	current_state = next_state;

	// Update FSM outputs
}



