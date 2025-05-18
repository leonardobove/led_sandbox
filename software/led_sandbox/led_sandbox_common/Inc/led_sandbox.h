/*
 * led_sandbox.h
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#ifndef INC_LED_SANDBOX_H_
#define INC_LED_SANDBOX_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "state_machine_task.h"

// Declaration funxtion for init
void led_sandbox_init();
void led_sandbox_loop();

#ifdef __cplusplus
}
#endif

#endif /* INC_LED_SANDBOX_H_ */
