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


	typedef enum LM75_STATUS
	{
		LM75_OK = 0,
		LM75_DEV_ADDR_FAIL,
		LM75_WRITE_REG_FAIL,
		LM75_RESTART_FAIL,
		LM75_WRITE_FAIL
	} LM75_STATUS;


	LM75_STATUS lm75_get_temp(float* temp);
	int lm75_sleep();
	int lm75_wakeup();

#endif /* UART_ATTINY_SRC_CHUNKS_H_ */
