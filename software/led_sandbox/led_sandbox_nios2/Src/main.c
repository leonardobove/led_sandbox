/*
 * main.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include "../../led_sandbox_common/Inc/led_sandbox.h"
#include "../../led_sandbox_common/Inc/hal.h"
#include "../../led_sandbox_common/Inc/scheduler.h"

int main() {
    // System initialization
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

