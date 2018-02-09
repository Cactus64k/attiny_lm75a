#include "i2c_master/i2c_master.h"
#include "chunks.h"

#define LM75_TEMP_REG		0x00
#define LM75_CONF_REG		0x01
#define LM75_DEV_ADDR		0b10011110

/*
int lm75_sleep()
{
	int status = EXIT_SUCCESS;
	i2c_start();

	if(i2c_send_byte(LM75_DEV_ADDR | I2C_ADDR_WRITE_FLAG) == NASK)		{status = EXIT_FAILURE; goto end;}
	if(i2c_send_byte(LM75_CONF_REG) == NASK)							{status = EXIT_FAILURE; goto end;}
	if(i2c_send_byte(0xFF) == NASK)										{status = EXIT_FAILURE; goto end;}

	end:

	i2c_stop();
	return status;
}

int lm75_wakeup()
{
	int status = EXIT_SUCCESS;
	i2c_start();

	if(i2c_send_byte(LM75_DEV_ADDR | I2C_ADDR_WRITE_FLAG) == NASK)		{status = EXIT_FAILURE; goto end;}
	if(i2c_send_byte(LM75_CONF_REG) == NASK)							{status = EXIT_FAILURE; goto end;}
	if(i2c_send_byte(0x00) == NASK)										{status = EXIT_FAILURE; goto end;}

	end:

	i2c_stop();
	return status;
}*/

LM75_STATUS lm75_get_temp(float* temp)
{
	*temp = NAN;
	LM75_STATUS  status = LM75_OK;

	i2c_start();

	if(i2c_send_byte(LM75_DEV_ADDR | I2C_ADDR_WRITE_FLAG) == NASK)		{status = LM75_DEV_ADDR_FAIL; 	goto end;}
	if(i2c_send_byte(LM75_TEMP_REG) == NASK)							{status = LM75_WRITE_REG_FAIL;	goto end;}

	i2c_start();
	if(i2c_send_byte(LM75_DEV_ADDR | I2C_ADDR_READ_FLAG) == NASK)		{status = LM75_RESTART_FAIL;		goto end;}

	uint16_t data = 0;
	i2c_read_16bit(&data, false);
	if(data & ((uint16_t)1<<15))
	{
		data = ((data>>5)^0x7FF)+1;
		*temp =(data * -0.125);
	}
	else
	{
		data = data >> 5;
		*temp = data * 0.125;
	}


	end:

	i2c_stop();

	return status;
}

