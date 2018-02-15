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

	printf("Start device\n");

	if(i2c_init() == EXIT_FAILURE)
	{
		while(true)
		{
			printf("EROR: I2C bus bad pin state, check and reconnect device\n");
			sleep_wd(WDTO_4S);
		}
	}
	else
	{
		while(true)
		{
			I2C_STATUS status		= i2c_write_byte_to_reg(LM75_DEV_ADDR, LM75_CONF_REG, 0x00);		// wakeup

			sleep_wd(WDTO_250MS);

			uint16_t data			= 0;
			status				= i2c_read_16bit_from_reg(LM75_DEV_ADDR, LM75_TEMP_REG, &data);
			status				= i2c_write_byte_to_reg(LM75_DEV_ADDR, LM75_CONF_REG, LM75_SHUTDOWN);		// sleep

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

			sleep_wd(WDTO_4S);
		}
	}



	return EXIT_SUCCESS;
}


void sleep_wd(uint8_t time)
{
	wdt_reset();
	wdt_enable(time);
	WDTCR |= _BV(WDIE);

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_bod_disable();
	sleep_cpu();
	wdt_disable();
}

