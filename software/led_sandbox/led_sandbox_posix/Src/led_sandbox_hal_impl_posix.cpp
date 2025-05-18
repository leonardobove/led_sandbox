#include "../../led_sandbox_common/Inc/hal.h"
#include "../../led_sandbox_common/Inc/scheduler.h"
#include "../../led_sandbox_common/Inc/pixel_dust_task.h"

#include <string.h>
#include <stdlib.h>
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

// Output matrix bitmap file specifications
#define OUTPUT_FILE "./matrix_pixels.txt"
#define REFRESH_INTERVAL_US (10000u)  // 10 ms = 10,000 microseconds


// Equivalent to hardware readout registers of peripherals
static uint32_t switches = 0;
static uint32_t sliders = 0;

// Equivalent of output acceleration measurement returned by the accelerometer
static int32_t x_acceleration = 0;
static int32_t y_acceleration = 0;
static int32_t z_acceleration = 0;

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
            // Push-buttons
            case 'a': {
                switches ^= (uint32_t)(1 << 0);
                printf("Switches: %d\n", switches);
                break;
            }
            case 's': {
                switches ^= (uint32_t)(1 << 1);
                printf("Switches: %d\n", switches);
                break;
            }
            case 'd': {
                switches ^= (uint32_t)(1 << 2);
                printf("Switches: %d\n", switches);
                break;
            }
            case 'w': {
                switches ^= (uint32_t)(1 << 3);
                printf("Switches: %d\n", switches);
                break;
            }
            // Increase/decrease accelerations
            case 'x': {
                x_acceleration--;
                printf("Accelerations: x: %d, y: %d, z: %d\n", x_acceleration, y_acceleration, z_acceleration);
                break;
            }
            case 'X': {
                x_acceleration++;
                printf("Accelerations: x: %d, y: %d, z: %d\n", x_acceleration, y_acceleration, z_acceleration);
                break;
            }
            case 'y': {
                y_acceleration--;
                printf("Accelerations: x: %d, y: %d, z: %d\n", x_acceleration, y_acceleration, z_acceleration);
                break;
            }
            case 'Y': {
                y_acceleration++;
                printf("Accelerations: x: %d, y: %d, z: %d\n", x_acceleration, y_acceleration, z_acceleration);
                break;
            }
            case 'z': {
                z_acceleration--;
                printf("Accelerations: x: %d, y: %d, z: %d\n", x_acceleration, y_acceleration, z_acceleration);
                break;
            }
            case 'Z': {
                z_acceleration++;
                printf("Accelerations: x: %d, y: %d, z: %d\n", x_acceleration, y_acceleration, z_acceleration);
                break;
            }
            
            // Sliders
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                uint8_t num_pressed = c - '0';
                // Toggle the bit corresponding to the pressed number
                sliders ^= (uint32_t)(1 << num_pressed);
                printf("Sliders: %d\n", sliders);
                break;
            }
            default: {
                break;
            }
        }
        

    }

    return NULL;
}

// Converts a 6-bit value to a 6-character binary string.
// The 6-bit value corresponds to the lower and upper
// pixels 3-bit RGB values.
void get_binary_string(uint8_t value, char *str) {
    str[0] = (value & 0b100000) ? '1' : '0';
    str[1] = (value & 0b010000) ? '1' : '0';
    str[2] = (value & 0b001000) ? '1' : '0';
    str[3] = (value & 0b000100) ? '1' : '0';
    str[4] = (value & 0b000010) ? '1' : '0';
    str[5] = (value & 0b000001) ? '1' : '0';
    str[6] = '\0';
}

void* pixel_buf_to_file(void*) {
    FILE *fp;
    char bin_str[7];

    while (true) {
        fp = fopen(OUTPUT_FILE, "w");
        if (!fp) {
            perror("Error opening file");
            return NULL;
        }

        for (uint32_t i = 0; i < (WIDTH * HEIGHT / 2); ++i) {
            get_binary_string(pixel_back_buf[i] & 0x3F, bin_str);  // mask to 6 bits
            fprintf(fp, "%s\n", bin_str);
        }

        fclose(fp);

        usleep(REFRESH_INTERVAL_US);  // sleep for 1 ms
    }
    
    return NULL;
}

void create_keyboard_logger_thread() {
    pthread_t tid;
    pthread_create(&tid, NULL, keyboard_logger_task, NULL);
}

void create_pixel_buf_to_file_thread() {
    pthread_t tid;
    pthread_create(&tid, NULL, pixel_buf_to_file, NULL);
}


/*** HAL functions implementations ***/

void hal_init() {
    scheduler_init();
    create_keyboard_logger_thread();
    create_pixel_buf_to_file_thread();
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

// UI peripherals HAL interface
uint32_t hal_read_switches() {
    return switches;
}

uint32_t hal_read_sliders() {
    return sliders;
}

// Accelerometer sensor HAL interface
bool hal_accelerometer_init() {
    return true;
}

accelerometer_output_t hal_read_accelerometer() {
    accelerometer_output_t acc_read = {
        .a_x = x_acceleration,
        .a_y = y_acceleration,
        .a_z = z_acceleration,
    };
    return acc_read;
}

void hal_error(uint32_t error_code) {
    printf("The program terminated with an error (error code: %d).\n", error_code);
    while (true) {;}
}

void hal_shift_rows(uint8_t *temp_buf) {
    return;
}