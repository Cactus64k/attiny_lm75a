ATTiny85 UART thermometer
=====================================================

Details:
* 1x ATTiny85 (fuses E:FF, H:DF, L:FF)
* 1x 3686400MHz quartz
* 1x LM75a
* 2x 12-20pf capacitors
* 2x 10-4.7k resistors for i2c pull-up
* 1x 10k resistors
* 2x 0.5-1mf ceramic capacitors for power supply filthering
* 1x schottky diode
* 1x optional 0ohm resistor

This code provide UART thermometer with 4s period. UART and I2C is software.
Features:
* low power device(12µA in sleep mode)
* polarity reversal protection
* easy connect to PC(using uart->usb converter)
* stable UART freq and no errors on 7 methers of twisted pair
* lowcost components
* code size is 3.5 Kbytes (can be less without printf and stdout)

<img src="/img/cheme.png" width="350"/>
<img src="/img/photo.png" width="350"/>
