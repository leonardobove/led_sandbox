#include "../../led_sandbox_common/Inc/scheduler.h"
#include "../../led_sandbox_common/Inc/hal.h"
#include "../../led_sandbox_common/Inc/led_sandbox.h"


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
