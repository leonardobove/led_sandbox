/*
 * system_tick.c
 *
 *  Created on: 14 Apr 2025
 *      Author: leona
 */

#include "../Inc/system_tick.h"

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
// Interval Timer ISR with enhanced API
void system_tick_ISR(void* context)

#else
// Interval Timer ISR with legacy API
void system_tick_ISR(void* context, alt_u32 id)
#endif
{
	uint32_t *tick_ptr = (uint32_t*) context;

	*tick_ptr = 1;

	// Acknowledgment IRQ
	IOWR_ALTERA_AVALON_TIMER_STATUS(SYSTEM_TICK_TIMER_BASE, ALTERA_AVALON_TIMER_STATUS_TO_MSK);

}

void system_tick_init(uint32_t period_ms, volatile uint32_t* tick_ptr)
{

	uint32_t period_reg = period_ms*(SYSTEM_TICK_TIMER_FREQ/1000) - 1;

	IOWR_ALTERA_AVALON_TIMER_PERIODL(SYSTEM_TICK_TIMER_BASE, period_reg & 0xFFFF);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(SYSTEM_TICK_TIMER_BASE, period_reg >> 16);

	IOWR_ALTERA_AVALON_TIMER_CONTROL(SYSTEM_TICK_TIMER_BASE,
			                         ALTERA_AVALON_TIMER_CONTROL_ITO_MSK |
			                         ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
			                         ALTERA_AVALON_TIMER_CONTROL_START_MSK);

	#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
	// register Interval Timer ISR with enhanced API
	alt_ic_isr_register(0, SYSTEM_TICK_TIMER_IRQ, system_tick_ISR, (void *) tick_ptr, NULL);
	#else
	// register Interval Timer with legacy API
	alt_irq_register(INTERVAL_TIMER_IRQ, (void *) tick_ptr, system_tick_ISR);
	#endif

}
