/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
	const uint GREEN_PIN = 13;
	const uint YELLOW_PIN = 12;
    gpio_init(LED_PIN);
	gpio_init(GREEN_PIN);
	gpio_init(YELLOW_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_set_dir(GREEN_PIN, GPIO_OUT);
	gpio_set_dir(YELLOW_PIN, GPIO_OUT);
		
	while (true) {
        gpio_put(LED_PIN, 1);
		gpio_put(GREEN_PIN, 1);
		gpio_put(YELLOW_PIN, 0);
		
		
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);
		gpio_put(GREEN_PIN, 0);
		gpio_put(YELLOW_PIN, 1);
        sleep_ms(1000);
    }
#endif
}