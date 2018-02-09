ATTiny85 UART thermomether
=====================================================

Details:
* 1x ATTiny85
* 1x 3686400MHz quartz
* 1x LM75a<br>
* 2x 20pf capacitors<br>
* 3x 10k resistors<br>
* 2x 1mf ceramic capacitors for power supply filthering<br>
* 1x schottky diode<br>
* 1x optional 0ohm resistor<br>

This code provide UART thermomether with 4s period. UART and I2C is software.<br>
Features:<br>
* low power device<br>
* easy connect to PC(using uart->usb converter)<br>
* stable UART freq and no errors on 7 methers of twisted pair<br>
* lowcost components<br>
* code size is 3376 bytes (can be less without printf and stdout)<br>

<img src="/img/cheme.png" width="350"/>
<img src="/img/photo.png" width="350"/>
