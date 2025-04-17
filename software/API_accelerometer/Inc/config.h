/*
 * config.h
 *
 *  Created on: 09 mar 2025
 *      Author: aless
 */

#ifndef CONFIG_H_
#define CONFIG_H_


#include "system.h"
#include "stdint.h"
#include "stdlib.h"
#include <stdint.h>
#include <stdio.h>
#include "unistd.h" // per usleep()



#define MSK_NIBBLE		0xF
#define SHIFT_NIBBLE	4
#define SHIFT_BYTE_1	8
#define ALL_LED_ON		0x3FF
#define DISPLAY_h		0x74	// 01110100

#endif /* CONFIG_H_ */
