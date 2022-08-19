/*
 * xpt2046.h
 *
 *  Created on: 26 de ago de 2020
 *      Author: Rinaldo Dos Santos
 *      Sinteck Next
 */

#ifndef XPT2046_H_
#define XPT2046_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"


#define TP_CS(x)	  HAL_GPIO_WritePin(MAX6675_GPIO_Port, MAX6675_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)

//#define TP_INT_IN()   HAL_GPIO_ReadPin(TOUCH_PRESS_GPIO_Port, TOUCH_PRESS_Pin)

/* Private typedef -----------------------------------------------------------*/
typedef	struct POINT
{
   uint16_t x;
   uint16_t y;
}Point;


typedef struct Matrix
{
long double An,
            Bn,
            Cn,
            Dn,
            En,
            Fn,
            Divider ;
} Matrix ;

/* Private variables ---------------------------------------------------------*/
extern Point ScreenSample[3];
extern Point DisplaySample[3];
extern Matrix matrix ;
extern Point  display ;

/* Private define ------------------------------------------------------------*/

#define	CHX 	0x90
#define	CHY 	0xd0

/* Private function prototypes -----------------------------------------------*/
void TP_Init(void);
Point *Read_XPT_2046(void);
void TouchPanel_Calibrate(void);
void TP_GetXY(uint16_t *x, uint16_t *y);
int GetTouchStatus(Point * pos);

#endif /* XPT2046_H_ */
