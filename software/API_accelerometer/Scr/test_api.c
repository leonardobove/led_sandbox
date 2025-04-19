/*
 * test_API.c
 *
 *  Created on: 16 apr 2025
 *      Author: aless
 */

#include <stdint.h>
#include <stdio.h>
#include "system.h"
#include "stdlib.h"
#include "unistd.h" // per usleep()
#include "../Inc/api_accelerometer.h"

int main() {
    alt_up_accelerometer_spi_dev* check = accelerometer_init();
    if(check== NULL){
    	printf("apertura accelerometro fallita\n");
    	return 1;
    }

    accelerometer_data_t axis_value;

    while (1) {
        if (accelerometer_get_data_raw(&axis_value) == 0) {
            printf("X: %d, Y: %d, Z: %d\n",
                   axis_value.x, axis_value.y, axis_value.z);
            // Attendi 100 millisecondi
                  usleep(100000);
        }
    }
}



