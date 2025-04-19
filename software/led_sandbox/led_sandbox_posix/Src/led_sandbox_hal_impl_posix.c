#ifdef __cplusplus
extern "C" {
#endif

#include "../../led_sandbox_common/Inc/hal.h"
#include "../../led_sandbox_common/Inc/scheduler.h"

#ifdef __cplusplus
}
#else
static const void *nullptr = 0u;
#endif

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <net/if.h>

#include <pthread.h>
#include <assert.h>


/*** HAL functions implementations ***/

void hal_init() {
    scheduler_init();
    hal_start_timers();
}

void timer_handler(int signum) {
    tick_flag = 1;
}


void hal_start_timers() {
    struct sigaction sa;
    struct itimerval timer;

    /* Install timer_handler as the signal handler for SIGVTALRM. */
    memset(&sa, 0, sizeof (sa));
    sa.sa_handler = &timer_handler;
    sigaction(SIGALRM, &sa, NULL);

    /* Configure the timer to expire after TICKS_PER_MS ms... */
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = TICKS_PER_MS * 1000;
    /* ... and every TICKS_PER_MS ms after that. */
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = TICKS_PER_MS * 1000;
    /* Start a virtual timer. It counts down whenever this process is
    executing. */
    setitimer(ITIMER_REAL, &timer, NULL);
}