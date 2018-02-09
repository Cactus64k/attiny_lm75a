#include "chunks.h"
#include "suart/suart.h"
#include "i2c_master/i2c_master.h"


ISR(WDT_vect)
{
	WDTCR |= _BV(WDIE);
}

int main()
{
	SUART_tx_init();
	SUART_init_tx_stdio();


	power_adc_disable();
	power_timer1_disable();
	power_usi_disable();

	wdt_disable();

	sei();

	float temp = 0;

	if(i2c_init() == EXIT_FAILURE)
	{
		while(true)
		{
			printf("EROR: I2C bus bad pin state, check and reconnect device\n");

			wdt_reset();
			wdt_enable(WDTO_4S);
			WDTCR |= _BV(WDIE);

			set_sleep_mode(SLEEP_MODE_PWR_DOWN);
			sleep_enable();
			sleep_bod_disable();
			sleep_cpu();
			wdt_disable();
		}
	}
	else
	{
		while(true)
		{
			LM75_STATUS status = lm75_get_temp(&temp);
			switch(status)
			{
				case LM75_OK:
					printf("%f\n", temp); break;
				case LM75_DEV_ADDR_FAIL:
					printf("EROR: No device\n"); break;
				case LM75_WRITE_REG_FAIL:
					printf("EROR: Register selection failed\n"); break;
				case LM75_RESTART_FAIL:
					printf("EROR: Device restart failed\n"); break;
				default:
					break;
			}

			wdt_reset();
			wdt_enable(WDTO_4S);
			WDTCR |= _BV(WDIE);

			set_sleep_mode(SLEEP_MODE_PWR_DOWN);
			sleep_enable();
			sleep_bod_disable();
			sleep_cpu();
			wdt_disable();
		}
	}



	return EXIT_SUCCESS;
}

