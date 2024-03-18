/*
 * key.c
 *
 *  Created on: Mar 2, 2024
 *      Author: 86187
 */

#include "key.h"

keyFlagStructure keyFlag;

void KEY_Init(void)
{
	keyFlag.key1_pressed = 0;
	keyFlag.key2_pressed = 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case GPIO_PIN_0:
		keyFlag.key1_pressed = 1;
		break;
	case GPIO_PIN_13:
		keyFlag.key2_pressed = 1;
		break;
	}
}
