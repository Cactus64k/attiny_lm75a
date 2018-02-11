#ifndef UART_ATTINY_SRC_CHUNKS_H_
	#define UART_ATTINY_SRC_CHUNKS_H_

	#ifndef F_CPU
		#define F_CPU 3686400UL
	#endif

	#ifndef DEVICE
		#define DEVICE attiny85
	#endif

	#ifndef __AVR_ATtiny85__
		#define __AVR_ATtiny85__
	#endif

	#include <avr/io.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <stdio.h>
	#include <float.h>
	#include <util/delay.h>
	#include <math.h>
	#include <avr/interrupt.h>
	#include <avr/power.h>
	#include <avr/wdt.h>
	#include <avr/sleep.h>

	#define LM75_TEMP_REG		0x00
	#define LM75_CONF_REG		0x01
	#define LM75_DEV_ADDR		0x9E
	#define LM75_SHUTDOWN		0x01

	void sleep_wd(uint8_t time);

#endif /* UART_ATTINY_SRC_CHUNKS_H_ */
