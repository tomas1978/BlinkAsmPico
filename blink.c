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
	int sleepTime=10;
	int sleepTimeOut;
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
		//Register R4 is connected to output
		asm
		(
			"mov r4, #55\n"
			"lsl r4, #2\n"
			"lsl r4, #2\n"
			"lsl r4, #2\n"
			"lsl r4, #2\n"
			

			
			: "=r" (sleepTimeOut)
			: "r" (sleepTime)
		);
        gpio_put(LED_PIN, 1);
        sleep_ms(sleepTimeOut);
        gpio_put(LED_PIN, 0);
        sleep_ms(sleepTimeOut);
    }
#endif
}
