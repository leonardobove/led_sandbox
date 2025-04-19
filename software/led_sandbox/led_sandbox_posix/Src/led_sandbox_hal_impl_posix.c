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
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>

#include <pthread.h>
#include <assert.h>


// Equivalent to hardware readout registers of peripherals
static uint32_t switches = 0;
static uint32_t sliders = 0;

// Save original terminal settings
struct termios orig_termios;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void enable_raw_mode() {
    struct termios raw;

    // Get current terminal attributes
    tcgetattr(STDIN_FILENO, &orig_termios);
    // Register a function to reset terminal when the program exits
    atexit(disable_raw_mode);

    raw = orig_termios;

    // Disable canonical mode (line buffering) and echo
    raw.c_lflag &= ~(ICANON | ECHO);
    // Set minimum number of input bytes and timeout
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void* keyboard_logger_task(void*) {
    while (true) {
        enable_raw_mode();

        char c;
        ssize_t n = read(STDIN_FILENO, &c, 1);

        // Map keyboard inputs to DE10-Lite hardware inputs
        switch (c) {
            case 'a':
                switches ^= (uint32_t)(1 << 0);
                break;
            case 's':
                switches ^= (uint32_t)(1 << 1);
                break;
            case 'd':
                switches ^= (uint32_t)(1 << 2);
                break;
            case 'w':
                switches ^= (uint32_t)(1 << 3);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                uint8_t num_pressed = c - '0';
                // Toggle the bit corresponding to the pressed number
                sliders ^= (uint32_t)(1 << num_pressed);
                break;
            default:
                break;
        }
        

    }

    return NULL;
}

void create_keyboard_logger_thread() {
    pthread_t tid;
    pthread_create(&tid, NULL, keyboard_logger_task, NULL);
}


/*** HAL functions implementations ***/

void hal_init() {
    scheduler_init();
    create_keyboard_logger_thread();
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

uint32_t hal_read_switches() {
    return switches;
}

uint32_t hal_read_sliders() {
    return sliders;
}