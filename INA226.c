/*
 * INA226.c
 *
 *  Created on: Apr 21, 2024
 *      Author: Hasan
 */


#include "INA226.h"

//extern olarak tx uart bıffer eklenmelidir.

extern const uint8_t INA226I2CAddresses[8];

INA226_t INA226Channels[8];

HAL_StatusTypeDef checkAllINA226(void){
	HAL_StatusTypeDef status;

	for(uint8_t i=0;i<INA226CHANNELCOUNT; i++){
		status = HAL_I2C_IsDeviceReady(&INA226I2CHANDLER, INA226I2CAddresses[i], 5, INA226TIMEOUT);
		if(status != HAL_OK){
			//bu alana sendrs485 fonksiyonu eklenmelidir.
		}
	}
	return status;
}

HAL_StatusTypeDef configAllINA226(void){
	HAL_StatusTypeDef status;
	uint8_t configBuffer = 0;
	for(uint8_t i=0;i<INA226CHANNELCOUNT; i++){

		status = HAL_I2C_Mem_Write(&INA226I2CHANDLER, INA226I2CAddresses[i], INA226_CONFIG_REGISTER, 1, &configBuffer, 1, (uint32_t)INA226TIMEOUT);

		return status;


	}

	return HAL_OK;
}
