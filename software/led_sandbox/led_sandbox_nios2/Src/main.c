/*
 * main.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include "led_sandbox.h"
#include "hal.h"
#include "scheduler.h"

int main() {
    led_sandbox_init();

    while (1) {
        // If tick has elapsed, call scheduler
        if (tick_flag) {
            scheduler_tick();

            // Reset tick flag
            tick_flag = 0;
        }

        // Call loop subroutine
        led_sandbox_loop();
    }

    return 0;
}

