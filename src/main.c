#include "chunks.h"
#include "suart/suart.h"
#include "i2c_master/i2c_master.h"


ISR(WDT_vect)
{
	WDTCR |= _BV(WDIE);
}

#define LM75_TEMP_REG		0x00
#define LM75_CONF_REG		0x01
#define LM75_DEV_ADDR		0x9E

int main()
{
	SUART_tx_init();
	SUART_init_tx_stdio();


	power_adc_disable();
	power_timer1_disable();
	power_usi_disable();

	wdt_disable();

	sei();

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
			uint16_t data			= 0;
			I2C_STATUS status		= i2c_read_16bit_from_reg(LM75_DEV_ADDR, LM75_TEMP_REG, &data);

			switch(status)
			{
				case I2C_TRANSFER_OK:
				{
					int16_t int_temp		= 0;
					int16_t fract_temp		= 0;

					if(data & ((uint16_t)1<<15))
					{
						data			= ((data>>5)^0x7FF)+1;

						int_temp		= (int16_t)(data >> 3) * -1;
						fract_temp	= (data & 0x7) * 125;		// 0x7 == 0b111
						//temp =(data * -0.125);
					}
					else
					{
						data			= data >> 5;

						int_temp		= data >> 3;
						fract_temp	= (data & 0x7) * 125;
						//temp = data * 0.125;
					}

					printf("%d.%d\n", int_temp, fract_temp); break;
				}
				case  I2C_NO_DEVICE:
					printf("EROR: No device\n"); break;
				case  I2C_REG_WRITE_FAIL:
					printf("EROR: Register selection failed\n"); break;
				case  I2C_RESTART_FAIL:
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

