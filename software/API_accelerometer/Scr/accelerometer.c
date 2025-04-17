/*
 * accelerometer.c
 *
 *  Created on: 16 apr 2025
 *      Author: aless
 */

#include "../Inc/api_accelerometer.h"
#include "../Inc/config.h"

//static accelerometer_range_t current_range = ACCELEROMETER_RANGE_2G; //Default init has 2G

//**** type accelerometer ****
static alt_up_accelerometer_spi_dev *accel_dev;

int accelerometer_init(void){
	accel_dev = alt_up_accelerometer_spi_open_dev("/dev/accelerometer_spi_0");
	if (accel_dev == NULL) {
	        return -1;
	    }
	else{
		return 0;
	}
}



/*int accelerometer_set_range(accelerometer_range_t range){
	current_range = range;
	return alt_up_accelerometer_spi_write(accel_dev, REG_DATA_FORMAT, range);
}*/



int accelerometer_get_data_raw(accelerometer_data_t* data){
	alt_up_accelerometer_spi_read_x_axis(accel_dev, &(data->x));
	alt_up_accelerometer_spi_read_y_axis(accel_dev, &(data->y));
	alt_up_accelerometer_spi_read_z_axis(accel_dev, &(data->z));
	return 0;
}



int accelerometer_get_data_g (accelerometer_data_t* data_g){
	float	scale= 0.039;	//for rage of 2g


	accelerometer_data_t data_raw;
	accelerometer_get_data_raw(&data_raw);

	data_g->x = data_raw.x * scale;
	data_g->y = data_raw.y * scale;
	data_g->z = data_raw.z * scale;
	return 0;
}
