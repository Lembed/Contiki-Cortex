/*
 * Copyright (c) prithvi * All rights reserved.
 * Created on: 03-Feb-2014
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


/**
 *  nrf51-clock Clock implementation for nrf51822 SoC
 * 			This module include the initialization of the 16 MHz high
 * 			frequency clock, 32.768 kHz LF clock and RTC1. Also all the
 * 			implementations of functions required by \ref nrf51-contiki-clock
 * 			module are defined here.
 *
 */

#ifndef CLOCK_NRF_H_
#define CLOCK_NRF_H_

#include "nrf.h"
#include "clock.h"
#include "contiki-conf.h"
#include "nrf-delay.h"
#include "nrf-gpio.h"
#include "simple-uart.h"

/** LF Clock frequency in Hertz, constant. */
#define LFCLK_FREQUENCY           (32768UL)
#define RTC1_IRQ_PRI				3

/** \brief Prescalar value required for RTC initialization.
 *  Based on the formula f = LFCLK/(prescaler + 1)
 */
#define COUNTER_PRESCALER         ((LFCLK_FREQUENCY/CLOCK_SECOND) - 1)

/** Unsigned int to store the number of seconds passed, required by Contiki */
static volatile uint32_t current_seconds = 0;

/** Unsigned int to store the number of times the RTC has overflowed to calculate \ref current_seconds.
 * 	Used with TICKLESS implementation */
static volatile uint32_t seconds_ovr = 0;
/** Variable to store the seconds offset if \ref clock_set_seconds is called.
 * 	Used with TICKLESS implementation */
static volatile int32_t seconds_offset = 0;
/** Variable to store the number of TICK of the clock.
 * 	Used without TICKLESS implementation */
static volatile clock_time_t current_clock = 0;
/** Variable to store the number of ticks remaining to increment \ref current_seconds.
 * 	Used without TICKLESS implementation */
static volatile unsigned int second_countdown = CLOCK_SECOND;

void rtc_init(void);
void lfclk_init(void);
void lfclk_deinit(void);
void hfclk_xtal_init(void);
void hfclk_xtal_deinit(void);
clock_time_t nrf_clock_time(void);
unsigned long nrf_clock_seconds(void);
void nrf_clock_set_seconds(uint32_t sec);
void nrf_clock_update_expiration_time(clock_time_t expiration_time);

#endif /* CLOCK_NRF_H_ */
