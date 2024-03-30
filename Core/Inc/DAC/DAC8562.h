/*
 * DAC8562.h
 *
 * Library for Texas Instruments DAC8562 2-Channel 16-bit SPI DAC
 *
 * Wiring:
 *
 * Din = MOSI
 * SCLK = CLK
 * /SYNC/ = NSS pin
 * /LDAC/ = GND
 * /CLR/ = VDD
 *
 *
 */

#ifndef __DAC8562_H__
#define __DAC8562_H__


#include <stdbool.h>
#include <stdint.h>
/*
 * Commands for the DAC8562
 * Pg.37 of ds
 *
 * https://www.ti.com/lit/ds/symlink/dac8562.pdf?ts=1710058927457&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FDAC8562#page=38&zoom=100,0,182
 */
#define CMD_WRITE_INPUT_REG 0x00	//Write to input register n (Table 12)
#define CMD_SOFTWARE_LDAC 0x08	//Software LDAC, update DAC register n (Table 12)
#define CMD_WRITE_INPUT_REG_UPDATE 0x10	//Write to input register n and update all DAC registers
#define CMD_WRITE_INPUT_REG_UPDATE_N 0x18	//Write to input register n and update DAC register n
#define CMD_PWR_UP_DOWN_DAC 0x20	//Power up or power down DAC
#define CMD_SOFTWARE_RST 0x28	//Software reset
#define CMD_SET_LDAC_REG 0x30	//Set LDAC registers
#define CMD_EN_DIS_INTERNAL_REFERENCE 0x38	//Enable or disable the internal refernce

/*
 * Commands for use, includes addr.
 */

#define CMD_DAC_GAIN_SET 0x02

#define CMD_WRITE_DAC_A_REG 0x00
#define CMD_WRITE_DAC_B_REG 0x01
#define CMD_WRITE_DAC_A_B_REG 0x07

#define CMD_UPDATE_DAC_A 0x08
#define CMD_UPDATE_DAC_B 0x09
#define CMD_UPDATE_DAC_A_B 0x0F

#define CMD_WRITE_UPDATE_DAC_A 0x18
#define CMD_WRITE_UPDATE_DAC_B 0x19

/*
 * Address select for the DAC8562
 */

#define ADRR_DAC_A 0x00	//Select DAC_A
#define ADRR_DAC_B 0x01	//Select DAC_B
#define ADRR_GAIN 0x02	//Only use with command 0x00
#define ADRR_DAC_A_B 0x07	//Select DAC_A and DAC_B
#define ADRR_DC_BITS 0x00	//Dont care bits

/*
 * Data for DAC8562
 */
#define DATA_DC 0x0000

#define DATA_PWR_UP_DAC_A_B 0x0003
#define DATA_PWR_DWN_DAC_A_B 0x0023
#define DATA_RST_DAC_A_B_UPDATE 0x0001

#define DATA_EN_INT_REF 0x0001
#define LDAC_INACTIVE 0x0003

#define GAIN_SET_2 0x0000
#define GAIN_SET_1 0x0003

uint8_t DAC_BEGIN();
void DAC_INIT();

uint8_t DAC_GAIN_SET(uint16_t data);

uint16_t DIN_CALC(float voltageOut,uint8_t gain,float vref); //Calculate Din for wanted voltage

uint8_t DAC_WR_REG(uint8_t cmd, uint16_t data);	//Generic write register

uint8_t DAC_A_WR(uint16_t data);	//Write data to DAC_A input register
uint8_t DAC_B_WR(uint16_t data);	//Write data to DAC_B input register

uint8_t DAC_A_UPDATE();	//Update DAC_A
uint8_t DAC_B_UPDATE();	// Update DAC_B

uint8_t DAC_A_WR_UPDATE(uint16_t data);	//Write and update DAC_A
uint8_t DAC_B_WR_UPDATE(uint16_t data);	//Write and update DAC_B

uint8_t DAC_A_B_PWR_UP();	//Power up DAC_A and DAC_B
uint8_t DAC_A_B_PWR_DWN();	//Power down DAC_A and DAC_B

uint8_t DAC_A_B_RESET_UPDATE();
#endif
