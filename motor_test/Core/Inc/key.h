/*
 * key.h
 *
 *  Created on: Mar 2, 2024
 *      Author:
 */

#ifndef INC_KEY_H_
#define INC_KEY_H_

#include "main.h"

typedef struct{
	uint8_t key1_pressed;
	uint8_t key2_pressed;
}keyFlagStructure;

extern keyFlagStructure keyFlag;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void KEY_Init(void);

#endif /* INC_KEY_H_ */
