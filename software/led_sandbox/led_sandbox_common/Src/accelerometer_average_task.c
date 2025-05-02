

#include "../Inc/accelerometer_average_task.h"
#include "../Inc/hal.h"


//Define average counter;
static uint32_t counter = 0;

//Define array vector
static accelerometer_output_t acceleration_array[NUM_AVERAGES] = {{0}};


//Assign initialization value
accelerometer_output_t acceleration_average = {
    .a_x = 0,
    .a_y = 0,
    .a_z = 0
};


//Define sum for average
static accelerometer_output_t sum = {
    .a_x = 0,
    .a_y = 0,
    .a_z = 0
};

void accelerometer_average_task(){

	if (!hal_accelerometer_init()) {
	                hal_error(2);   // Accelerometer initialization error
	    }

    if(counter >= NUM_AVERAGES){      //in case of full array, average is calculated
        for (int i = 0; i < NUM_AVERAGES; i++){
            sum.a_x += acceleration_array[i].a_x;
            sum.a_y += acceleration_array[i].a_y;
            sum.a_z += acceleration_array[i].a_z;
        }
        acceleration_average.a_x= sum.a_x/NUM_AVERAGES;
        acceleration_average.a_y= sum.a_y/NUM_AVERAGES;
        acceleration_average.a_z= sum.a_z/NUM_AVERAGES;

        //counter reset
        counter = 0;
        //sum reset
        sum.a_x = 0;
        sum.a_y = 0;
        sum.a_z = 0;
    }
    else{
        acceleration_array[counter]= hal_read_accelerometer();
        counter++;
    }
}


