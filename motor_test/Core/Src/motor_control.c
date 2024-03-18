/*
 * motor_control.c
 *
 *  Created on: Feb 26, 2024
 *      Author: 86187
 */

#include "motor_control.h"
#include "tim.h"

bldc_obj g_bldc_motor;

/*获取霍尔传感器状态*/
uint8_t hall_sensor(void)
{
	uint8_t state = 0;
	if(HAL_GPIO_ReadPin(HALL_SENSOR_U_PORT,HALL_SENSOR_U_PIN) != GPIO_PIN_RESET)
	{
		state |= 0x1;
	}
//	else
//	{
//		state &= ~((uint8_t)0x1);
//	}
	if(HAL_GPIO_ReadPin(HALL_SENSOR_V_PORT,HALL_SENSOR_V_PIN) != GPIO_PIN_RESET)
	{
		state |= 0x1<<1;
	}
//	else
//	{
//		state &= ~((uint8_t)0x1<<1);
//	}
	if(HAL_GPIO_ReadPin(HALL_SENSOR_W_PORT,HALL_SENSOR_W_PIN) != GPIO_PIN_RESET)
	{
		state |= 0x1<<2;
	}
//	else
//	{
//		state &= ~((uint8_t)0x1<<2);
//	}
	return state;
}

/*U相上桥臂导通V相下桥臂导通*/
void m_uhvl()
{
	/*上桥臂控制，通道x比较寄存器赋值*/
	htim1.Instance -> CCR1 = g_bldc_motor.pwm_duty;
	htim1.Instance -> CCR2 = 0;
	htim1.Instance -> CCR3 = 0;

	/*下桥臂控制*/
	HAL_GPIO_WritePin(M_LOW_SIDE_U_PORT, M_LOW_SIDE_U_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_V_PORT, M_LOW_SIDE_V_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(M_LOW_SIDE_W_PORT, M_LOW_SIDE_W_PIN, GPIO_PIN_RESET);
}

/*U相上桥臂导通W相下桥臂导通*/
void m_uhwl()
{
	/*上桥臂控制，通道x比较寄存器赋值*/
	htim1.Instance -> CCR1 = g_bldc_motor.pwm_duty;
	htim1.Instance -> CCR2 = 0;
	htim1.Instance -> CCR3 = 0;

	/*下桥臂控制*/
	HAL_GPIO_WritePin(M_LOW_SIDE_U_PORT, M_LOW_SIDE_U_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_V_PORT, M_LOW_SIDE_V_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_W_PORT, M_LOW_SIDE_W_PIN, GPIO_PIN_SET);
}

/*V相上桥臂导通U相下桥臂导通*/
void m_vhul()
{
	/*上桥臂控制，通道x比较寄存器赋值*/
	htim1.Instance -> CCR1 = 0;
	htim1.Instance -> CCR2 = g_bldc_motor.pwm_duty;
	htim1.Instance -> CCR3 = 0;

	/*下桥臂控制*/
	HAL_GPIO_WritePin(M_LOW_SIDE_U_PORT, M_LOW_SIDE_U_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(M_LOW_SIDE_V_PORT, M_LOW_SIDE_V_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_W_PORT, M_LOW_SIDE_W_PIN, GPIO_PIN_RESET);
}

/*V相上桥臂导通W相下桥臂导通*/
void m_vhwl()
{
	/*上桥臂控制，通道x比较寄存器赋值*/
	htim1.Instance -> CCR1 = 0;
	htim1.Instance -> CCR2 = g_bldc_motor.pwm_duty;
	htim1.Instance -> CCR3 = 0;

	/*下桥臂控制*/
	HAL_GPIO_WritePin(M_LOW_SIDE_U_PORT, M_LOW_SIDE_U_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_V_PORT, M_LOW_SIDE_V_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_W_PORT, M_LOW_SIDE_W_PIN, GPIO_PIN_SET);
}

/*W相上桥臂导通U相下桥臂导通*/
void m_whul()
{
	/*上桥臂控制，通道x比较寄存器赋值*/
	htim1.Instance -> CCR1 = 0;
	htim1.Instance -> CCR2 = 0;
//	htim1.Instance -> CCR3 = g_bldc_motor.pwm_duty;
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,g_bldc_motor.pwm_duty);

	/*下桥臂控制*/
	HAL_GPIO_WritePin(M_LOW_SIDE_U_PORT, M_LOW_SIDE_U_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(M_LOW_SIDE_V_PORT, M_LOW_SIDE_V_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_W_PORT, M_LOW_SIDE_W_PIN, GPIO_PIN_RESET);
}

/*W相上桥臂导通V相下桥臂导通*/
void m_whvl()
{
	/*上桥臂控制，通道x比较寄存器赋值*/
	htim1.Instance -> CCR1 = 0;
	htim1.Instance -> CCR2 = 0;
	htim1.Instance -> CCR3 = g_bldc_motor.pwm_duty;
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,g_bldc_motor.pwm_duty);

	/*下桥臂控制*/
	HAL_GPIO_WritePin(M_LOW_SIDE_U_PORT, M_LOW_SIDE_U_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_V_PORT, M_LOW_SIDE_V_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(M_LOW_SIDE_W_PORT, M_LOW_SIDE_W_PIN, GPIO_PIN_RESET);
}

/*关闭电机旋转*/
void stop_motor(void)
{
	HAL_GPIO_WritePin(M_SD_PORT, M_SD_PIN, GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
	htim1.Instance -> CCR1 = 0;
	htim1.Instance -> CCR2 = 0;
	htim1.Instance -> CCR3 = 0;
	HAL_GPIO_WritePin(M_LOW_SIDE_U_PORT, M_LOW_SIDE_U_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_V_PORT, M_LOW_SIDE_V_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_LOW_SIDE_W_PORT, M_LOW_SIDE_W_PIN, GPIO_PIN_RESET);
}

/*开启电机旋转*/
void start_motor(void)
{
	HAL_GPIO_WritePin(M_SD_PORT, M_SD_PIN, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}
