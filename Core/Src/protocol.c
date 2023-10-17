#include "protocol.h"
#include "BMP280.h"

uint32_t Pressure_value;
uint32_t Temperature_value;

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart2;

h_BMP280_t h_BMP280;



void protocol(char RX_Pi_buffer[RX_BUFFER_SIZE], uint8_t Size)
{
	if (strncmp(RX_Pi_buffer,"GET_T",strlen("GET_T"))==0)
	{
		Temperature_value= BMP280_read_temp(&h_BMP280);
		printf("T=%d_C\r\n",Temperature_value);

	}
	else if (strncmp(RX_Pi_buffer,"GET_P",strlen("GET_P"))==0)
	{
		Pressure_value=BMP280_read_press(&h_BMP280);
		printf("P=%dPa\r\n",Pressure_value);
	}
	else if (strncmp(RX_Pi_buffer,"SET_K",strlen("SET_K"))==0)
	{

	}
	else if (strncmp(RX_Pi_buffer,"GET_K",strlen("GET_K"))==0)
	{

	}
	else if (strncmp(RX_Pi_buffer,"GET_A",strlen("GET_A"))==0)
	{

	}
	else
	{
		printf("Command not found\r\n"
				"Try one of these commands:\r\n"
				"GET_T: to get the temperature value \r\n"
				"GET_P: to get the pressure value \r\n"
				"SET_K=xxxx: to set the K coefficient on xxxx value (in 1/100e)\r\n"
				"GET_K: to get the K coefficient\r\n"
				"GET_A: to get the angle\r\n");
	}
	memset(RX_Pi_buffer,NULL,Size*sizeof(char));
}
