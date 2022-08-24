/*
 * ads1115.h
 *
 *  Created on: 22 de ago de 2022
 *      Author: rinal
 */

#ifndef ADS1115_ADS1115_H_
#define ADS1115_ADS1115_H_

#include "main.h"

/**
  ******************************************************************************
  * @file    ads1115.h
  * @author  zhiLiangMa
  * @version V0.1.0
  * @date    2019/06/30
  * @brief ads1115.c.h contains the basic drive functions of ads1115, over-range trigger edge, and load cell unit conversion
  ******************************************************************************
  * @attention
  *
	 * 1. Pay attention before using this driver. The iic timing of ads1115 is different from the standard iic protocol of at24c02 and mpu6050
	 *, the difference is mainly reflected in the reading. For details, please refer to page 24 of the manual, writing data is consistent with the standard iic
	 * For normal iic reading, first send the device iic ID, then send the register address to be read, and then send the device iic ID+1
	 *. And ads introduced the device pointer register, no need to carry the register address in the iic frame of each frame
	 * 2. The correct reading method of ads is to write data to iic and point the pointer register to the register address that you want to read
	 *, and then use the last bit of the iic device ID as the read/write control bit, read 1 and write 0, and omit the register address in the standard iic frame. Read data directly.
	 * 3. In short, before the standard iic reads the data that the user wants, it needs to send three bytes: device ID, device register address required by the user, device ID+1
	 *. And ads, before getting the data that the user wants, only one byte needs to be sent: the device ID including the read and write control bits. . . But before that, you must write the pointer controller to write the required address
	 * 4. Also note that when writing a 16-bit register, you must write all 16 bits at a time. 16 bits only write 8 bits, the last 8 bits cannot be addressed
  ******************************************************************************
  */

 /* When the ADDR pin is connected to different levels, the device shows different I2C addresses */
#define ads1115_GND_iic_addr	0x48
#define ads1115_VDD_iic_addr	0x49
#define ads1115_SDA_iic_addr	0x4A
#define ads1115_SCL_iic_addr	0x4B

 /* ADS1115 register address */
#define ConversionRegister		0x00
#define ConfigRegister			0x01
#define LoThreshRegister		0x03
#define HiThreshRegister		0x04

 /* Read the level of the Alert pin to determine whether it exceeds the range of the digital comparator */
#define GetADS1115Alert GPIO_ReadInputDataBit(ADC_ALERT_GPIO_Port, ADC_ALERT_Pin)

 /* Use union & bit field to configure register */
 //Combination and bit field combination http://www.stmcu.org.cn/module/forum/forum.php?mod=viewthread&tid=610197
 //Because the memory accumulation of the bit field starts from the low bit, put the high register in the manual at the end of the bit field definition
union xADS1115ConfigRegisterH
{
	uint8_t  value;
	struct{
		uint8_t MODE:1;
		uint8_t PGA:3;
		uint8_t MUX:3;
		uint8_t OS:1;
	}RegisterH;
};

union xADS1115ConfigRegisterL
{
	uint8_t  value;
	struct{
		uint8_t COMP_QUE:2;
		uint8_t COMP_LAT:1;
		uint8_t COMP_POL:1;
		uint8_t COMP_MODE:1;
		uint8_t DR:3;
	}RegisterL;
};

/************************************************
 Ads1115 internal register function definition
************************************************/
 //Run status or single conversion bit
 //Run status or single conversion start This bit determines the running status of the device. OS can only be written in the power-down state, and is invalid when the conversion is in progress.
enum OS
{
	 No_effect=0, //Invalid
	 Start_single_conversion //Start a single conversion
};

 //Enter the multiplexer configuration
 //These bits configure the input multiplexer
enum MUX
{
	AIN0_AIN1=0, //MUX strobed pins connected to PGA are AIN0 and AIN1
	AIN0_AIN3,
	AIN1_AIN3,
	AIN2_AIN3,
	AIN0_GND,
	AIN1_GND,
	AIN2_GND,
	AIN3_GND
};

 //Programmable gain amplifier configuration
 //These bits set the FSR of the programmable gain amplifier
 //This parameter represents the full scale range of ADC scaling. Do not apply a voltage exceeding VDD + 0.3 V to the analog input of the device
enum PGA
{
	 Gain_2_3_6144V=0, //Gain is 2/3, the maximum input voltage of the pin is ±6.144 +0.3V
	 Gain_1_4096V, //The gain is 1, the maximum input voltage of the pin is ±4.096 +0.3V
	 Gain_2_2048V, //The gain is 2, the maximum input voltage of the pin is ±2.048 +0.3V
	 Gain_4_1024V, //The gain is 4, the maximum input voltage of the pin is ±1.024 +0.3V
	 Gain_8_0512V, //The gain is 8, the maximum input voltage of the pin is ±0.512 +0.3V
	 Gain_16_0256V, //The gain is 16, the maximum input voltage of the pin is ±0.256 +0.3V
	 Gain_16_0256V1, //The gain is 16, the maximum input voltage of the pin is ±0.256 +0.3V
	 Gain_16_0256V2 //The gain is 16, the maximum input voltage of the pin is ±0.256 +0.3V
};

 //Device operating mode
 //This bit controls the operation mode.
enum MODE
{
	 Continuous_conversion_mode=0, //Continuous conversion mode
	 Single_shot_mode //Single shot mode or power down state
};

 //Data rate
 //These bits control the data rate setting.
enum DR
{
	Rate_8=0,			//8 SPS
	Rate_16,			//16 SPS
	Rate_32,			//32 SPS
	Rate_64,			//64 SPS
	Rate_128,			//128 SPS
	Rate_250,			//250 SPS
	Rate_475,			//475 SPS
	Rate_860			//860 SPS
};

 //Comparator mode
 //This bit configures the working mode of the comparator
enum COMP_MODE
{
	 Traditional_comparator=0, //Traditional comparator
	 Window_comparator //Window comparator
};

 //Comparator polarity
 //This bit controls the polarity of the ALERT/RDY pin
enum COMP_POL
{
	 Active_low=0, //active low
	 Active_high //active high
};

 //Comparator latch
 //This bit controls whether the ALERT/RDY pin is latched after being set or cleared within the upper and lower threshold range after conversion
enum COMP_LAT
{
	 Nonlatching=0, //Non-latching comparator
	 Latching //Latching comparator
};

 //Comparator queue and disabling
//These bits perform two functions. When set to 11, the comparator is disabled and the ALERT/RDY pin is set to a high impedance state. When set to any other value, the ALERT/RDY pin and the comparator function are enabled, and the set value determines the number of consecutive conversions that exceed the required upper or lower limit before asserting the ALERT/RDY pin
enum COMP_QUE
{
	 One=0, //Assertion after one conversion
	 Two, //Assertion after two conversions
	 Four, //Assertion after four conversions
	 Disable //Disable the comparator and set the ALERT/RDY pin to high impedance
};



/*====================================================================================================*/
/*====================================================================================================*
 ** Function name: ADS1115_ReadConversionRegister(uint8_t ads_addr)
 ** Function description: Read 16-bit ADC conversion data of ADS1115, pay attention to the type, is int16, signed
 ** Input: IIC device address of ads1115 selected by ads_addr
 ** Output: 16-bit ADC conversion data, pay attention to the type, is int16, signed
 ** Explanation: Pay attention to the type, it is int16, signed
**====================================================================================================*/
/*====================================================================================================*/
int16_t ADS1115_ReadConversionRegister(uint8_t ads_addr);

/*====================================================================================================*/
/*====================================================================================================*
 ** Function name: ADS1115_GetAinVoltage(uint8_t ads_addr)
 ** Function description: Get the input port voltage of ADS1115, and get the actual voltage value according to the configuration of the register
 ** Input: IIC device address of ads1115 selected by ads_addr
 ** Output: float type voltage data
 ** Explanation: The voltage unit is V
 ** Table 3. Full-Scale Range and Corresponding LSB Size ti official website 53 pages manual page 17
**					 FSR 			LSB SIZE
**					 ±6.144 V(1) 	187.5 μV
**					 ±4.096 V(1) 	125 μV
**					 ±2.048 V 		62.5 μV
**					 ±1.024 V 		31.25 μV
**					 ±0.512 V 		15.625 μV
**					 ±0.256 V 		7.8125 μV
**====================================================================================================*/
/*====================================================================================================*/
float ADS1115_GetAinVoltage(uint8_t ads_addr, uint8_t PGA_mode);

/*====================================================================================================*/
/*====================================================================================================*
 ** Function name: ADS1115_PointRegister(uint8_t ads_addr,uint8_t point)
 ** Function description: Set the pointing address of the internal pointer register, pointing to the ADS1115 pointer register to prepare to read data
 ** Input: IIC device address of ads1115 selected by ads_addr
						  point The pointed address of the internal pointer register
 ** Output: void
 ** Explanation: If you want to read the ADC conversion value, you must call this function to point the pointer to the ADC conversion data register, and then IIC will read it.
 ** So there is no need to carry ADC conversion data register address in IIC read
**====================================================================================================*/
/*====================================================================================================*/
void ADS1115_PointRegister(uint8_t ads_addr,uint8_t point);

/*====================================================================================================*/
/*====================================================================================================*
 ** Function name: ADS1115_ConfigRegister(uint8_t ads_addr)
 ** Function description: Configure ADS1115 internal registers to complete information configuration such as channel selection, capture rate, PGA gain multiple, etc.
 ** Input: IIC device address of ads1115 selected by ads_addr
 ** Output: void
 ** Note: If you need to change the settings, please change the structure of the following union
**====================================================================================================*/
/*====================================================================================================*/
//void ADS1115_ConfigRegister(uint8_t ads_addr);
void ADS1115_ConfigRegister(uint8_t ads_addr, uint8_t mux, uint8_t pga);

/*====================================================================================================*/
/*====================================================================================================*
 ** Function name: ADS1115_Comparator_Threshold(uint8_t ads_addr, int16_t LowerThreshold, int16_t UpperThreshold)
 ** Function description: Set the upper and lower thresholds of the digital voltage comparator
 ** Input: IIC device address of ads1115 selected by ads_addr
 ** LowerThreshold lower threshold
 ** UpperThreshold upper threshold
 ** Output: void
 ** Explanation: If the ALERT output of the digital voltage comparator turned on exceeds the lower or upper threshold of the threshold, a level transition will occur on the ALERT pin
**====================================================================================================*/
/*====================================================================================================*/
void ADS1115_Comparator_Threshold(uint8_t ads_addr, int16_t LowerThreshold, int16_t UpperThreshold);

/*====================================================================================================*/
/*====================================================================================================*
 ** Function name: ADS1115_AlertGPIOInit(void)
 ** Function description: STM32 GPIO configuration of Alert pin. You can select interrupt trigger or scan level mode.
 ** Input: void
 ** Output: void
 ** Explanation: Because the sampling frequency of ads1115 is relatively low, selecting the scan level method will miss many moments that exceed the threshold
 ** It is strongly established to use GPIO interrupt input to do it. High-level or low-level trigger interrupt, see the configuration method of the function above for details
**====================================================================================================*/
/*====================================================================================================*/
// void ADS1115_AlertGPIOInit(void);

/*====================================================================================================*/
/*====================================================================================================*
 ** Function name: void ADS1115_Init(void)
 **Function description: Initialization of ADS1115, including IIC pin setting, digital voltage comparator setting, Alert interrupt pin setting, A/D conversion rate setting, PGA gain setting, input pin channel setting
 ** Input: void
 ** Output: void
 ** Description: Integrate all the above configurations, add 100ms delay between each configuration, to prevent the crosstalk after analog IIC continuous transmission
**====================================================================================================*/
/*====================================================================================================*/
void ADS1115_Init(void);

void ADS1115_WriteOneByte(uint8_t ads_addr, uint8_t WriteAddr, uint8_t DataToWrite);
void ADS1115_WriteMulByte(uint8_t ads_addr, uint8_t WriteAddr,uint8_t xnum,uint8_t* xData);
void IIC_Stop(uint8_t ads_addr);

#endif /* ADS1115_ADS1115_H_ */
