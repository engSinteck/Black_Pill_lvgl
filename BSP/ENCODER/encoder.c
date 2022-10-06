/*
 * encoder.c
 *
 *  Created on: 6 de out de 2022
 *      Author: rinal
 */

#include "main.h"
#include "encoder.h"

GPIO_PinState aVal, bVal, cVal;

uint8_t aLast = 0, aCW = 0;
uint8_t bLast = 0, bCW = 0;
uint8_t cLast = 0, cCW = 0;

uint16_t encoderA = 0, encoderB = 0, encoderC = 0;

uint16_t Read_Encoder_A(void)
{
	/* BEGIN – Code for encoder */
	aVal = HAL_GPIO_ReadPin(ENC1_A_GPIO_Port, ENC1_A_Pin);
	if (aVal != aLast)
	{ 	// Means the knob is rotating
		// if the knob is rotating, we need to determine direction
		// We do that by reading pin B.
		if (HAL_GPIO_ReadPin(ENC1_B_GPIO_Port, ENC1_B_Pin) != aVal)
		{ // Means pin A Changed first – We’re Rotating Clockwise
			encoderA++;
			if(encoderA >= 4095) encoderA = 4095;
			aCW = TRUE;
		}
		else {// Otherwise B changed first and we’re moving CCW
			if(encoderA >= 1) encoderA--;
			aCW = FALSE;
		}
		//sprintf(buffer, "Encoder - aVal: %d DT: %d, EncoderPosition: %ld\n", aVal, HAL_GPIO_ReadPin(ENC_C_GPIO_Port, ENC_C_Pin), encoderPosCount);
		//HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	}
	aLast = aVal;

	return encoderA;
}

uint16_t Read_Encoder_B(void)
{
	/* BEGIN – Code for encoder */
	bVal = HAL_GPIO_ReadPin(ENC2_A_GPIO_Port, ENC2_A_Pin);
	if (bVal != bLast)
	{ 	// Means the knob is rotating
		// if the knob is rotating, we need to determine direction
		// We do that by reading pin B.
		if (HAL_GPIO_ReadPin(ENC2_B_GPIO_Port, ENC2_B_Pin) != aVal)
		{ // Means pin A Changed first – We’re Rotating Clockwise
			encoderB++;
			if(encoderB >= 4095) encoderB = 4095;
			bCW = TRUE;
		}
		else {// Otherwise B changed first and we’re moving CCW
			if(encoderB >= 1) encoderB--;
			bCW = FALSE;
		}
		//sprintf(buffer, "Encoder - aVal: %d DT: %d, EncoderPosition: %ld\n", aVal, HAL_GPIO_ReadPin(ENC_C_GPIO_Port, ENC_C_Pin), encoderPosCount);
		//HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	}
	bLast = bVal;

	return encoderB;
}

uint16_t Read_Encoder_C(void)
{
	/* BEGIN – Code for encoder */
	cVal = HAL_GPIO_ReadPin(ENC3_A_GPIO_Port, ENC3_A_Pin);
	if (cVal != cLast)
	{ 	// Means the knob is rotating
		// if the knob is rotating, we need to determine direction
		// We do that by reading pin B.
		if (HAL_GPIO_ReadPin(ENC3_B_GPIO_Port, ENC3_B_Pin) != aVal)
		{ // Means pin A Changed first – We’re Rotating Clockwise
			encoderC++;
			if(encoderC >= 4095) encoderC = 4095;
			cCW = TRUE;
		}
		else {// Otherwise B changed first and we’re moving CCW
			if(encoderC >= 1) encoderC--;
			cCW = FALSE;
		}
		//sprintf(buffer, "Encoder - aVal: %d DT: %d, EncoderPosition: %ld\n", aVal, HAL_GPIO_ReadPin(ENC_C_GPIO_Port, ENC_C_Pin), encoderPosCount);
		//HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	}
	cLast = cVal;

	return encoderC;
}
