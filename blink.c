/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

int blink_led(const uint LED_PIN, int sleepTime) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
	gpio_put(LED_PIN, 1);
	sleep_ms(sleepTime);
	gpio_put(LED_PIN, 0);
	sleep_ms(sleepTime);
}
	

int main() {
	#ifndef PICO_DEFAULT_LED_PIN
	#warning blink example requires a board with a regular LED
	#else
	const uint LED_PIN = PICO_DEFAULT_LED_PIN;

	int sleepTime=200;
	int numberOfBlinks;
	
	//Register r7 connected to output variable numberOfBlinks
	//Calculating the value of expression 3*(2+4)-5*(9+7)/8, store in r7 and numberOfBlinks
	asm(
			"mov r1, #2\n"
			"mov r2, #4\n"
			"add r3, r1, r2\n"
			"mov r1, #3\n"
			"mul r1, r3, r1\n" //Partial result 2*(2+4)=12 now in r1. INCORRECT!!! Seems to be value 18 instead of 12!
			
			"mov r2, #9\n"
			"mov r3, #7\n"
			"add r4, r2, r3\n"
			"mov r5, #8\n"
			"lsl r4, #3\n" //Result of (9+7)/8 now in r4
			"mov r2, #5\n"
			"mul r2, r2, r4\n" //Partial result 5*(9+7)/8=10 now in r2. INCORRECT!!! Seems to be more than 100 instead of 10!
			"mov r7, r2"
			"sub r7, r1, r2\n"
			
			: "=r" (numberOfBlinks)
			
		);

	for(int i=0; i<numberOfBlinks; i++) {
		blink_led(LED_PIN, sleepTime);
	}
	
	
 #endif
}
