/*
 * ads1115.c
 *
 *  Created on: 22 de ago de 2022
 *      Author: rinal
 */

#include "ads1115.h"
#include "i2c.h"
#include <stdio.h>
#include <math.h>

unsigned char ADSwrite[10];

int16_t ADS1115_ReadConversionRegister(uint8_t ads_addr)
{
	uint8_t adcTemp[2];
    int16_t reading;

	HAL_I2C_Master_Receive(&hi2c1, ads_addr <<1, adcTemp, 2, 100);
	reading=((int16_t)adcTemp[0] << 8) | adcTemp[1] ;

	return reading ;
}

float ADS1115_GetAinVoltage(uint8_t ads_addr, uint8_t PGA_mode)
{
  int16_t adcValue;
  float AinVoltage; //Ain input port voltage
  adcValue = ADS1115_ReadConversionRegister(ads_addr);

  if(PGA_mode==0)       AinVoltage=(float)adcValue * 0.0001875;
  else if(PGA_mode==1)  AinVoltage=(float)adcValue * 0.000125;
  else if(PGA_mode==2)  AinVoltage=(float)adcValue * 0.0000625;
  else if(PGA_mode==3)  AinVoltage=(float)adcValue * 0.00003125;
  else if(PGA_mode==4)  AinVoltage=(float)adcValue * 0.000015625;
  else                  AinVoltage=(float)adcValue * 0.0000078125;

  return AinVoltage;
}

void ADS1115_PointRegister(uint8_t ads_addr,uint8_t point)
{
  ADSwrite[0]=point;
  HAL_I2C_Master_Transmit(&hi2c1, ads_addr << 1, ADSwrite, 1, 100);
  IIC_Stop(ads_addr);
}

void ADS1115_ConfigRegister(uint8_t ads_addr, uint8_t mux, uint8_t pga)
{
  union xADS1115ConfigRegisterH ADS1115ConfigRegisterH;
  union xADS1115ConfigRegisterL ADS1115ConfigRegisterL;

  uint8_t xsend[2];

  ADS1115ConfigRegisterH.RegisterH.OS = Start_single_conversion; 		//Open a single conversion
  ADS1115ConfigRegisterH.RegisterH.MUX = mux; 							//The pins of MUX strobe connected to PGA are AIN0 and AIN1
  ADS1115ConfigRegisterH.RegisterH.PGA = pga; 							//The gain is 16, the maximum input voltage of the pin is ±0.256 +0.3V
  ADS1115ConfigRegisterH.RegisterH.MODE = Continuous_conversion_mode;	//Continuous conversion mode

  ADS1115ConfigRegisterL.RegisterL.DR = Rate_128;						//128 SPS
  ADS1115ConfigRegisterL.RegisterL.COMP_MODE = Traditional_comparator; //Window comparator
  ADS1115ConfigRegisterL.RegisterL.COMP_POL = Active_low; 				//Aler pin, active low
  ADS1115ConfigRegisterL.RegisterL.COMP_LAT = Nonlatching; 				//Non-latching comparator
  ADS1115ConfigRegisterL.RegisterL.COMP_QUE = Disable; 					//Assert after one conversion


  //Write the configured register content into the ADS1115 device through the IIC bus
  xsend[0] = ADS1115ConfigRegisterH.value;
  //xsend[0] = 0xC1;
  xsend[1] = ADS1115ConfigRegisterL.value;
  ADS1115_WriteMulByte(ads_addr, ConfigRegister, 2, xsend);
}

void ADS1115_Comparator_Threshold(uint8_t ads_addr, int16_t LowerThreshold, int16_t UpperThreshold)
{
  uint8_t xsend[2];

  xsend[0] = (LowerThreshold>>8) & 0x00FF;
  xsend[1] = LowerThreshold & 0x00FF;
   //Digital voltage comparator voltage lower limit threshold setting
  ADS1115_WriteMulByte(ads_addr, LoThreshRegister, 2, xsend);

  HAL_Delay(2);

  xsend[0] = (UpperThreshold>>8) & 0x00FF;
  xsend[1] = UpperThreshold & 0x00FF;
   //Digital voltage comparator voltage upper limit threshold setting
  ADS1115_WriteMulByte(ads_addr, HiThreshRegister, 2, xsend);
}

//////////////init
void ADS1115_Init(void)
{
    ADS1115_ConfigRegister(ads1115_GND_iic_addr, AIN0_GND, Gain_2_2048V);
}


/////////////I2C W/R

void ADS1115_WriteOneByte(uint8_t ads_addr, uint8_t WriteAddr, uint8_t DataToWrite)
{
  ADSwrite[0]=WriteAddr;
  ADSwrite[1]=DataToWrite;

  HAL_I2C_Master_Transmit(&hi2c1, ads_addr << 1, ADSwrite, 2, 100);
  IIC_Stop(ads_addr);
}

void ADS1115_WriteMulByte(uint8_t ads_addr, uint8_t WriteAddr,uint8_t xnum,uint8_t* xData)
{
  ADSwrite[0]=WriteAddr;
  for(int i=0;i<xnum;i++){
    ADSwrite[(1+i)]=xData[i];
  }

  HAL_I2C_Master_Transmit(&hi2c1, ads_addr << 1, ADSwrite, (xnum+1), 100);
  IIC_Stop(ads_addr);
}

void IIC_Stop(uint8_t ads_addr)
{
    ADSwrite[0] = 0x00;
    HAL_I2C_Master_Transmit(&hi2c1, ads_addr << 1, ADSwrite, 1, 100);
    HAL_Delay(20);
}
