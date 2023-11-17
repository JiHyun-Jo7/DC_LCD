/*
 * Button.h
 *
 *  Created on: Sep 6, 2023
 *      Author: user
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include "stm32f4xx_hal.h"

enum {PUSHED, RELEASED};
enum {NO_ACT, ACT_PUSH, ACT_RELEASE};

typedef struct _button
{
  GPIO_TypeDef *GPIOx;  // GPIO ABCD..
  uint16_t GPIO_PIN;    // PIN num
  uint8_t prevState;
}Button;

void Button_Init(Button *btn, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t Button_getState(Button *btn);



#endif /* SRC_BUTTON_H_ */
