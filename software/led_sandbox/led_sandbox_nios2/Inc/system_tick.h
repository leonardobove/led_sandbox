/*
 * system_tick.h
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#ifndef INC_SYSTEM_TICK_H_
#define INC_SYSTEM_TICK_H_

#define ALT_ENHANCED_INTERRUPT_API_PRESENT

#include "altera_avalon_timer_regs.h"
#include "system.h"
#include "sys/alt_irq.h"
#include <stdint.h>

// These macros need to match those related to the used INTERVAL TIMER CORE
// The used INTERVAL TIMER CORE has to be disconnected from HAL services
#define SYSTEM_TICK_TIMER_BASE		SYSTICK_TIMER_BASE
#define SYSTEM_TICK_TIMER_FREQ		SYSTICK_TIMER_FREQ
#define SYSTEM_TICK_TIMER_IRQ		SYSTICK_TIMER_IRQ

void system_tick_init(uint32_t, volatile uint32_t*);

#endif /* INC_SYSTEM_TICK_H_ */
