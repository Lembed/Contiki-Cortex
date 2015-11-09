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

#include "contiki.h"
#include "board.h"
#include "simple-uart.h"
#include "dev/leds.h"

#include "nrf-radio.h"
#include "nrf-init.h"

/*---------------------------------------------------------------------------*/
int main(void)
{
/*
 * Initialize the basic peripherals required for Contiki
 */
  clock_init();
  rtimer_init();
  leds_init();

  process_init();
  simple_uart_init();

  /* Testing of the basic peripherals */
  leds_blink();
  printf("Testing\n\r");

  process_start(&etimer_process, NULL);
  ctimer_init();

  /* Configure the nRF51 inits */
  nrf_init();

  /* Configure the nRF51 radio */
  nrf_radio_init();

  autostart_start(autostart_processes);

  while(true) {
    uint32_t process_count;
    do {
    	process_count = process_run();
    } while(process_count > 0);

    /* We have serviced all pending events. Enter a Low-Power mode. */
    __WFE();
  }
}
/*---------------------------------------------------------------------------*/
