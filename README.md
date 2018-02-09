UART thermomether
=====================================================

Details:
1x ATTiny85
1x 3686400MHz quartz
1x LM75a
2x 20pf capacitors
3x 10k resistors
2x 1mf ceramic capacitors for power supply filthering
1x schottky diode

This code provide UART thermomether with 4s period. UART and I2C is software.
Features:
	low power device
	easy connect to PC(using uart->usb converter)
	stable UART freq and no errors on 7 methers of twisted pair
	lowcost components
	code size is 3376 bytes (can be less without printf and stdout)

<img src="external_thermomether_lm75/cheme.png " width="350"/>
