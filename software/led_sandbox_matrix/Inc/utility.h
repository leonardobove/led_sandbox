/*
 * utility.h
 *
 *  Created on: 15 mag 2025
 *      Author: termi
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdint.h>

#define WIDTH 	(64u)
#define HEIGHT 	(32u)

#define RED_L     (0x01)
#define GREEN_L   (0x02)
#define BLUE_L    (0x04)
#define PURPLE_L  (0x05)
#define YELLOW_L  (0x03)
#define CIAN_L    (0x06)
#define BLACK_L   (0x00)
#define WHITE_L   (0x07)

#define RED_H     (0x08)
#define GREEN_H   (0x10)
#define BLUE_H    (0x20)
#define PURPLE_H  (0x28)
#define YELLOW_H  (0x18)
#define CIAN_H    (0x30)
#define BLACK_H   (0x00)
#define WHITE_H   (0x38)

void swap_lines (uint8_t *frame_buffer);
void wait_ms(unsigned int time_ms);


#endif /* UTILITY_H_ */
