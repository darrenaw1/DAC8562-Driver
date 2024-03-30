/*
 * 	DAC8562.c
 *
 * 	Library for DAC8562
 */

#include <DAC/DAC8562.h>
#include "main.h"

/*
 *
 * Vout = (Din / 2^16) x Vref x gain
 *
 */

/*
 * @brief Initialise the dac
 *
 */

uint8_t DAC_BEGIN()
{
	uint8_t status;
	status = DAC_A_B_RESET_UPDATE();
	status = DAC_A_B_PWR_UP();
	status = DAC_WR_REG(CMD_EN_DIS_INTERNAL_REFERENCE, DATA_EN_INT_REF);
	status = DAC_GAIN_SET(GAIN_SET_1);
	status = DAC_WR_REG(CMD_SET_LDAC_REG, LDAC_INACTIVE);

	return status;
}
void DAC_INIT();

uint16_t DIN_CALC(float voltageOut,uint8_t gain,float vref){
	/*
	 * Vout = (Din / 2^16) x Vref x gain
	 *
	 * Gain is set by user, set to 1.
	 *
	 * Vref is set by user, internal ref 2.5V.
	 */

	uint16_t dIn = (voltageOut * 65536) / (vref * gain);
	uint16_t rounded_din = round(dIn);
	return rounded_din;
}


/*
 * @brief Generic write register
 */
uint8_t DAC_WR_REG(uint8_t cmd, uint16_t data)
{
    uint8_t status;
    uint8_t txData[3];

	txData[0] = cmd;
	txData[1] = ((data >> 8) & 0xFF);
	txData[2] = (data & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}

/*
 *  Write data to DAC_A input register
 */
uint8_t DAC_A_WR(uint16_t data)
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_WRITE_DAC_A_REG;
	txData[1] = ((data >> 8) & 0xFF);
	txData[2] = (data & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}

/*
 *  Write data to DAC_B input register
 */
uint8_t DAC_B_WR(uint16_t data)
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_WRITE_DAC_B_REG;
	txData[1] = ((data >> 8) & 0xFF);
	txData[2] = (data & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}

/*
 * Update DAC_A
 */
uint8_t DAC_A_UPDATE()
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_UPDATE_DAC_A;
	txData[1] = ((DATA_DC >> 8) & 0xFF);
	txData[2] = (DATA_DC & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}

/*
 * Update DAC_B
 */
uint8_t DAC_B_UPDATE()
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_UPDATE_DAC_B;
	txData[1] = ((DATA_DC >> 8) & 0xFF);
	txData[2] = (DATA_DC & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}

/*
 *  Write and update DAC_A
 */
uint8_t DAC_A_WR_UPDATE(uint16_t data)
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_WRITE_UPDATE_DAC_A;
	txData[1] = ((data >> 8) & 0xFF);
	txData[2] = (data & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;

}

/*
 *  Write and update DAC_B
 */
uint8_t DAC_B_WR_UPDATE(uint16_t data)
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_WRITE_UPDATE_DAC_B;
	txData[1] = ((data >> 8) & 0xFF);
	txData[2] = (data & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;

}

/*
 *  Power up DAC_A and DAC_B
 */
uint8_t DAC_A_B_PWR_UP()
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_PWR_UP_DOWN_DAC;
	txData[1] = ((DATA_PWR_UP_DAC_A_B >> 8) & 0xFF);
	txData[2] = (DATA_PWR_UP_DAC_A_B & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}

/*
 *  Power down DAC_A and DAC_B
 */
uint8_t DAC_A_B_PWR_DWN()
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_PWR_UP_DOWN_DAC;
	txData[1] = ((DATA_PWR_DWN_DAC_A_B >> 8) & 0xFF);
	txData[2] = (DATA_PWR_DWN_DAC_A_B & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}

/*
 * Reset all registers, and update all DACs
 */
uint8_t DAC_A_B_RESET_UPDATE()
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_SOFTWARE_RST;
	txData[1] = ((DATA_RST_DAC_A_B_UPDATE >> 8) & 0xFF);
	txData[2] = (DATA_RST_DAC_A_B_UPDATE & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}


uint8_t DAC_GAIN_SET(uint16_t data)
{
	uint8_t status;
	uint8_t txData[3];

	txData[0] = CMD_DAC_GAIN_SET;
	txData[1] = ((data >> 8) & 0xFF);
	txData[2] = (data & 0xFF);

	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_RESET);
	status = (HAL_SPI_Transmit(&hspi1, txData, sizeof(txData), HAL_MAX_DELAY)==HAL_OK);
	HAL_GPIO_WritePin(GPIOB, DAC_NSS_Pin, GPIO_PIN_SET);

	return status;
}
