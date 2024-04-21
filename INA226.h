/*
 * INA226.h
 *
 *  Created on: Apr 21, 2024
 *      Author: Hasan KIZILOVA
 */

#ifndef INC_INA226_H_
#define INC_INA226_H_

//USER CODE include
#include "main.h"
#include "stdbool.h"
#include "math.h"

extern I2C_HandleTypeDef hi2c1;

#define INA226_CONFIG_REGISTER 0x00
#define INA226_SHUNT_VOLTAGE_REGISTER 0x01
#define INA226_BUS_VOLTAGE_REGISTER 0x02
#define INA226_POWER_REGISTER 0x03
#define INA226_CURRENT REGISTER 0x04
#define INA226_CALIBRATION_REGISTER 0x05
#define INA226_MASK_REGISTER 0x06
#define INA226_ALERT_LIMIT_REGISTER 0x07
#define INA226_MANIFACTURER_ID_REGISTER 0xFE
#define INA226_DIE_ID_REGISTER 0xFF
#define INA226I2CHANDLER hi2c1
#define INA226CHANNELCOUNT 8
#define INA226TIMEOUT 100
#define MAXCURRENT 6
#define SHUNTRESISTOR 0.010
#define CALIBRATIONFIXEDCOEF 0.00512

#define CURRENTLSB(x) ((x) / 32768) //32768 2^15 in decimal değeri

double_t calibrationValue = CALIBRATIONFIXEDCOEF /(SHUNTRESISTOR*CURRENTLSB(MAXCURRENT));

enum numberOfAvarages_e{
	AVARAGE_1 = 0,
	AVARAGE_4,
	AVARAGE_16,
	AVARAGE_64,
	AVARAGE_128,
	AVARAGE_256,
	AVARAGE_512,
	AVARAGE_1024,
	AVARAGE_INDEX = 9
};

enum conversionTime_e{
	_140_uS = 0,
	_204_uS,
	_332_uS,
	_588_uS,
	_1_1_mS,
	_2_116_mS,
	_4_156_mS,
	_8_244_mS,
	BUSVOLTAGEINDEX = 6,
	SHUNTVOLTAGEINDEX = 3
};
enum operatingModes_e{
	POWERDOWN_1 = 0,
	SHUNTVOLTAGE_TRIGGERED,
	BUSVOLTAGE_TRIGGERED,
	SHUNT_BUS_TRIGGERED,
	POWERDOWN_2,
	SHUNTVOLTAGE_CONTINUOUS,
	BUSVOLTAGE_CONTINUOUS,
	SHUNT_BUS_CONTINUOUS,
	MODES_INDEX = 0
};


const uint8_t INA226I2CAddresses[8] = {0b1000000, 0b1000001, 0b1000010, 0b1000011, 0b1000100, 0b1000101, 0b1000110, 0b1000111};

struct INA226ConfigRegisters {
	uint16_t configuration; // R/W
	uint16_t maskEnable; // R/W
	uint16_t alertLimit; // R/W
};

typedef struct {
	struct INA226ConfigRegisters INA226CONFIG;
	bool isInitialized;
	uint8_t slaveI2CAddress; //DEVICE ADDRESS
	uint8_t registerAddress;
	uint16_t shuntVoltage; //READ ONLY
	uint16_t busVoltage; //READ ONLY
	uint16_t power; //READ ONLY
	uint16_t current; //READ ONLY
} INA226_t;



#endif /* INC_INA226_H_ */
