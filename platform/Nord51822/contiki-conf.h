/*
 * Copyright (c) CoenRoest * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CONTIKI_CONF_H_
#define CONTIKI_CONF_H_


#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "nrf.h"

/** Macros for enabling shortcuts, interrupts and bit-counting */
/*
#define RADIO_SHORTS_ENABLED 1
#define RADIO_BCC_ENABLED 0
#define RADIO_INTERRUPT_ENABLED 0
*/

#ifndef NETSTACK_CONF_RADIO
#define NETSTACK_CONF_RADIO   nrf_radio_driver
#endif /* NETSTACK_CONF_RADIO */
/*---------------------------------------------------------------------------*/
/** Specify the UART baud rate */
#define UART_BAUDRATE UART_BAUDRATE_BAUDRATE_Baud38400

/** Defines for the capture/compare registers in TIMER0*/
#define SCHEDULE_REG 	0
#define TIMESTAMP_REG 	1
#define NOW_REG		2
#define BCC_REG		3

/** \showinitializer */
#define CCIF
/** \showinitializer */
#define CLIF



typedef uint32_t clock_time_t;
typedef uint32_t uip_stats_t;
typedef uint32_t rtimer_clock_t;

/** TRUE if a is less than b, otherwise FALSE.
 * rtimer.h typedefs rtimer_clock_t as unsigned short.
 * We need to define RTIMER_CLOCK_LT here to override this.
 */
#define RTIMER_CLOCK_LT(a,b)    ((int32_t)((a)-(b)) < 0)

/** The Rtimer's TIMER tick freq is HF freq divided by two to power of value defined here*/
#define TIMER_PRESCALER 	0
/** \brief Number of bits used for the Rtimer's TIMER */
#define TIMER_BITSIZE TIMER_BITMODE_BITMODE_32Bit

#if TIMER_BITSIZE == TIMER_BITMODE_BITMODE_08Bit
/** Since the Rtimer is 8 bit the CC interrupt occurs every 2^8 ticks of the TIMER */
#define TIMER_COMPARE_FREQ	256
#endif
#if TIMER_BITSIZE == TIMER_BITMODE_BITMODE_32Bit
/** Since the Rtimer is 8 bit the CC interrupt occurs every 2^8 ticks of the TIMER */
#define TIMER_COMPARE_FREQ	1
#endif

/** HF Clock frequency in Hertz, constant.
 *  When RC is used it is always 16 MHz. When a crystal is
 *  used it is either 16 MHz or 32 MHz based on the crystal.
 */
#define HFCLK_FREQUENCY		  (16000000UL)

/** \brief 16MHz clock based on TIMER0 for the RTIMER
 *  16MHz = 16MHz/((1<<0)x1). To decrease this frequency \ref TIMER_PRESCALER
 *  can be increased till 9 */
#define RTIMER_ARCH_SECOND 		(((HFCLK_FREQUENCY)/(1<<TIMER_PRESCALER))/TIMER_COMPARE_FREQ)


/** \brief Frequency of main clock, for which RTC1 is used
 */
#define CLOCK_CONF_SECOND 64
/* Check if CLOCK_CONF_SECOND is power of 2 and less than or equal to 32.768 kHz */
#if (!(!(CLOCK_CONF_SECOND & (CLOCK_CONF_SECOND-1)) && CLOCK_CONF_SECOND && (CLOCK_CONF_SECOND<=32768)))
#error CLOCK_CONF_SECOND must be a power of 2 with a maximum frequency of 32768 Hz
#endif

/** Specify the source of the Low freq clock for the platform */
#define SRC_LFCLK CLOCK_LFCLKSRC_SRC_Xtal

/** Specify if TICKLESS implementation is required*/
#define TICKLESS true

/*---------------------------------------------------------------------------*/

#endif /* CONTIKI_CONF_H_ */

