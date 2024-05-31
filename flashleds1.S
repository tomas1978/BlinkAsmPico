@
@ Assembler program to flash three LEDs connected to the
@ Raspberry Pi GPIO writing to the registers directly.
@
@
	.EQU LED_PIN1, 0
	.EQU LED_PIN2, 1
	.EQU LED_PIN3, 2
	.EQU LED_PIN4, 3
	
	.EQU GPIO_OUT, 1

	.EQU sleep_time,	200

.thumb_func
.global main	        @ Provide program starting address

.align  4			@ necessary alignment

main:
@ Init each of the four pins and set them to output
	MOV	R0, #LED_PIN1	
	bl gpio_init
	MOV	R0, #LED_PIN1	
	MOV R1, #GPIO_OUT	
	BL	link_gpio_set_dir

	MOV	R0, #LED_PIN2	
	bl gpio_init
	MOV	R0, #LED_PIN2
	MOV R1, #GPIO_OUT	
	BL	link_gpio_set_dir

	MOV	R0, #LED_PIN3	
	bl gpio_init
	MOV	R0, #LED_PIN3	
	MOV R1, #GPIO_OUT	
	BL	link_gpio_set_dir

	MOV	R0, #LED_PIN4	
	bl gpio_init
	MOV	R0, #LED_PIN4	
	MOV R1, #GPIO_OUT	
	BL	link_gpio_set_dir
	

loop:
@ Turn each pin on, sleep and then turn the pin off
	mov R5, #0xd0		//Put number 0x000000d0
	lsl r5, #24			//SIO base address 0xd0000000 in r2

	mov r6, #0b1001		//Used to set bits for pins 0 and 4
	str r6,[r5, #0x14]	//Offset address for SIO_OUT_SET is 0x14

	ldr r0, =sleep_time
	bl sleep_ms

	str r6,[r5, #0x18]	//Offset address for SIO_OUT_CLR is 0x18

	mov r6, #0b0110		//Used to set bits for pins 1 and 2
	str r6,[r5, #0x14]	//Offset address for SIO_OUT_SET is 0x14

	ldr r0, =sleep_time
	bl sleep_ms

	str r6,[r5, #0x18]	//Offset address for SIO_OUT_CLR is 0x18

    B       loop	@ loop forever

