/*
 * max6675.h
 *
 *  Created on: 18 de ago de 2022
 *      Author: rinal
 */

#ifndef MAX6675_MAX6675_H_
#define MAX6675_MAX6675_H_

#include "main.h"
#include "stdbool.h"
#include "stdlib.h"
#include "spi.h"

#define MAX6675_SPI hspi1
#define BUFFER_SIZE 2
#define MAX_TEMP 1024
#define MAX6675_RESOLUTION 4095

typedef struct MAX6675_Typedef MAX6675_Typedef;

struct MAX6675_Typedef{

	uint16_t Value;
	float Temp_C;
	bool State;

	uint16_t (*MAX6675_getValue)(MAX6675_Typedef* const sensor);
	float (*MAX6675_getTemp)(MAX6675_Typedef* const sensor);
	bool (*MAX6675_getState)(MAX6675_Typedef* const sensor);
};

uint16_t MAX6675_getValue(MAX6675_Typedef* const sensor);
float MAX6675_getTemp(MAX6675_Typedef* const sensor);
bool MAX6675_getState(MAX6675_Typedef* const sensor);

void MAX6675_Init(MAX6675_Typedef* const sensor, uint16_t (*getValue_f)(MAX6675_Typedef* const sensor),
				  float (*getTemp_f)(MAX6675_Typedef* const sensor),bool (*getState_f)(MAX6675_Typedef* const sensor));
MAX6675_Typedef* MAX6675_Create(void);
void MAX6675_Cleanup(MAX6675_Typedef* const sensor);
void MAX6675_Destroy(MAX6675_Typedef* const sensor);

#endif /* MAX6675_MAX6675_H_ */
