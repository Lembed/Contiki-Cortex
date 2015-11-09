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

#include "leds.h"
#include "nrf-gpio.h"
#include "board.h"

/*---------------------------------------------------------------------------*/
/**@brief Function to initialize the LEDS in the PCA10000 board,
 * 		  also switch off all of them
 */
void
leds_arch_init(void){
	  nrf_gpio_cfg_output(LEDS_CONF_RED);
	  nrf_gpio_pin_set(LEDS_CONF_RED);
	  nrf_gpio_cfg_output(LEDS_CONF_GREEN);
	  nrf_gpio_pin_set(LEDS_CONF_GREEN);
	  nrf_gpio_cfg_output(LEDS_CONF_BLUE);
	  nrf_gpio_pin_set(LEDS_CONF_BLUE);
	  nrf_gpio_cfg_output(LEDS_CONF_YELLOW);
	  nrf_gpio_pin_set(LEDS_CONF_YELLOW);
	  nrf_gpio_cfg_output(LEDS_CONF_CYAN);
	  nrf_gpio_pin_set(LEDS_CONF_CYAN);
}
/*---------------------------------------------------------------------------*/
/** \brief Get the current status of the LEDs in the last three bits
 * \return 2nd bit: Red; 1st bit: Blue; 0th bit: Green; Other bits: Zero
 * 		   1 if LED is on, 0 if off
 */
uint8_t
leds_arch_get(void){
	uint8_t temp = 	(nrf_gpio_pin_read(LEDS_CONF_RED)*LEDS_RED)|
			(nrf_gpio_pin_read(LEDS_CONF_BLUE)*LEDS_BLUE)|
			(nrf_gpio_pin_read(LEDS_CONF_GREEN)*LEDS_GREEN);
	return ((~temp)&(LEDS_RED|LEDS_BLUE|LEDS_GREEN));
}
/*---------------------------------------------------------------------------*/
/**
 * \brief 		Set the LEDs of the RGB LED unit with last three bits
 * \param leds	2nd bit: Red; 1st bit: Blue; 0th bit: Green; Other bits: No effect
 * 				LED will light up if the bit is 1, switch off if bit is 0.
 */
void
leds_arch_set(uint8_t leds){
	/* Invert the input since the LEDs are active low */
	leds = ~leds;
	nrf_gpio_pin_write(LEDS_CONF_GREEN,(leds & LEDS_GREEN));
	nrf_gpio_pin_write(LEDS_CONF_BLUE,(leds & LEDS_BLUE));
	nrf_gpio_pin_write(LEDS_CONF_RED,(leds & LEDS_RED));
	nrf_gpio_pin_write(LEDS_CONF_YELLOW,(leds & LEDS_BLUE));
	nrf_gpio_pin_write(LEDS_CONF_CYAN,(leds & LEDS_RED));
}
