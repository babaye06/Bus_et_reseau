/*
 * BMP280.c
 *
 *  Created on: 10 oct. 2023
 *      Author: GILLES Baptiste
 */

#include "BMP280.h"

int BMP280_init(h_BMP280_t * h_BMP280)
{
    h_BMP280->data_available = 0;
	h_BMP280->skipped_data = 0;
    //Récupération de l'ID du composant
    uint8_t chip_id = BMP280_CHIP_ID_t;
    h_BMP280->I2C_drv.transmit(BMP280_I2CADDR, &chip_id, 2);
    h_BMP280->I2C_drv.receive(BMP280_I2CADDR, &chip_id, 2);
    if(chip_id != 0x58)
    {
        return -1;
    }
    h_BMP280->chip = chip_id;
    
    //Reset du composant
    uint8_t reset = BMP280_RESET;
    h_BMP280->I2C_drv.transmit(BMP280_I2CADDR, &reset, 1);


    //Configuration du composant
    uint8_t power_mode = BMP280_SAMPLE_2|BMP280_SAMPLE_16|BMP280_NORMAL_MODE ;
    uint8_t buffer[2];
    buffer[0] = BMP280_CONTROL;
    buffer[1] = power_mode;
    h_BMP280->I2C_drv.transmit(BMP280_I2CADDR, buffer, 2);
    h_BMP280->I2C_drv.receive(BMP280_I2CADDR, buffer, 1);
    h_BMP280->power =  buffer[0];
    h_BMP280->sample = buffer[1];
    return 0;
}

int BMP280_read_temp(h_BMP280_t * h_BMP280)
{
	
	int32_t temp;
	uint8_t temp_msb = BMP280_TEMP_MSB;
	uint8_t buffer[3];
	h_BMP280->I2C_drv.transmit(BMP280_I2CADDR, &temp_msb, 1);
	h_BMP280->I2C_drv.receive(BMP280_I2CADDR, buffer, 3);

	temp = (buffer[0] << 12 | buffer[1] << 4 | buffer[2]>>4);

	printf("Temperature = %d \n\r",temp);

	return temp;
}

int BMP280_read_press(h_BMP280_t * h_BMP280)
{

	int32_t press;
	uint8_t press_msb = BMP280_PRESSURE_MSB;
	uint8_t buffer[3];
	h_BMP280->I2C_drv.transmit(BMP280_I2CADDR, &press_msb, 1);
	h_BMP280->I2C_drv.receive(BMP280_I2CADDR, buffer, 3);

	press = (buffer[0] << 12 | buffer[1] << 4 | buffer[2]>>4);

	printf("Pression = %d \n\r",press);

	return press;
}
