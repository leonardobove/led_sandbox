/*
 * state_machine_task.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include <stdio.h>

#include "../Inc/state_machine_task.h"
#include "../Inc/hal.h"

// Initialize current/next state
fsm_state_t current_state = RESET;
fsm_state_t next_state = RESET;

// Initialize inputs
fsm_inputs_t inputs = {
    .switch_inputs = 0,
    .slider_inputs = 0,
};

void state_machine_task() {
    // Read inputs
    inputs.switch_inputs = hal_read_switches();
    inputs.slider_inputs = hal_read_sliders();

    // Evaluate next state based on current state and inputs
    switch (current_state) {
        case RESET:
            if (inputs.switch_inputs & (1 << START_KEY)) {
                next_state = IDLE;
            } else {
                next_state = RESET;
            }
            break;

        case IDLE:
            if (inputs.switch_inputs & (1 << START_KEY)) {
                if (inputs.slider_inputs & (1 << GSENSOR_MODE_SLIDER)) {
                    next_state = GSENSOR_SANDBOX;
                }
            } else {
                next_state = IDLE;
            }
            break;

        case GSENSOR_SANDBOX:

            break;

        default:
            break;

    }

    // Global reset: from any state, go back to RESET state
    if ((inputs.switch_inputs & (1 << RESET_KEY))) {
        next_state = RESET;
    }

    // Update FSM state
    current_state = next_state;

    // Update FSM outputs
    switch (current_state) {
        case RESET:
            break;
        case IDLE:
            break;
        case GSENSOR_SANDBOX:
            break;
    }
}



