/*
 * api_accelerometer.h
 *
 *  Created on: 17 apr 2025
 *      Author: aless
 */

#ifndef INC_API_ACCELEROMETER_H_
#define INC_API_ACCELEROMETER_H_

#include "altera_up_avalon_accelerometer_spi.h"
#include <stdint.h>

//**** use range ******

/*typedef enum{
	ACCELEROMETER_RANGE_2G = 0,
	ACCELEROMETER_RANGE_4G,
	ACCELEROMETER_RANGE_8G,
	ACCELEROMETER_RANGE_16G
} accelerometer_range_t;*/

// **** lecture data *****
typedef struct {
    int x;
    int y;
    int z;
} accelerometer_data_t;


// ***** MACROS *****
#define REG_DATA_FORMAT 0x31



//**** API *****

int accelerometer_init(void);								//initialize value
//int accelerometer_set_range(accelerometer_range_t range);	// set range
int accelerometer_get_data_raw(accelerometer_data_t* data);	// get data in raw value
int accelerometer_get_data_g(accelerometer_data_t* data_g);  // get data in g vale

#endif /* INC_API_ACCELEROMETER_H_ */
