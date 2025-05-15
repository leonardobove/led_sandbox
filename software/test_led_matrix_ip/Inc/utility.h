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
#define HEIGHT 	(16u)

#define RED     (0x01)
#define GREEN   (0x02)
#define BLUE    (0x04)
#define PURPLE  (0x05)
#define YELLOW  (0x06)
#define CIAN    (0x03)
#define BLACK   (0x00)
#define WHITE   (0x07)

void swap_lines (uint8_t *frame_buffer);


#endif /* UTILITY_H_ */
