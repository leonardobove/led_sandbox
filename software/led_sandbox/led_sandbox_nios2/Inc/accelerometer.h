/*
 * api_accelerometer.h
 *
 *  Created on: 17 apr 2025
 *      Author: aless
 *
 * Accelerometer sensor used: ADXL345.
 * Scope of a measure: default +-2g. POssibility to edit up to +-16g.
 * Sensitivity measure: (256*2)/Scope [LSB/g], default case: (256*2)/2 [LSB/g].
 */

#ifndef INC_API_ACCELEROMETER_H_
#define INC_API_ACCELEROMETER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "system.h"
#include "stdlib.h"
#include "altera_up_avalon_accelerometer_spi.h"


//**** use range ******

/*typedef enum{
	ACCELEROMETER_RANGE_2G = 0,
	ACCELEROMETER_RANGE_4G,
	ACCELEROMETER_RANGE_8G,
	ACCELEROMETER_RANGE_16G
} accelerometer_range_t;*/

// **** lecture data *****
typedef struct {
    int32_t x;
    int32_t y;
    int32_t z;
} accelerometer_data_t;


// ***** MACROS *****
#define REG_DATA_FORMAT (0x31)



//**** API *****

alt_up_accelerometer_spi_dev* accelerometer_init(void);		    // initialize value
//int accelerometer_set_range(accelerometer_range_t range);	    // set range
int32_t accelerometer_get_data_raw(accelerometer_data_t* data);	    // get data in raw value
int32_t accelerometer_get_data_g(accelerometer_data_t* data_g);     // get data in g vale

#ifdef __cplusplus
}
#endif

#endif /* INC_API_ACCELEROMETER_H_ */
