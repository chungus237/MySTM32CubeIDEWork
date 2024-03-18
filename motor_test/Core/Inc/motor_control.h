/*
 * motor_control.h
 *
 *  Created on: Feb 26, 2024
 *      Author: 86187
 */

#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

#include "main.h"

typedef struct{
	volatile uint8_t	runflag;		/*运行标志*/
	volatile uint8_t	step_sta;		/*本次霍尔状态*/
	volatile uint8_t	step_last;		/*上次霍尔状态*/
	volatile uint8_t	dir;			/*方向*/
	volatile uint16_t	pwm_duty;		/*占空比*/
}bldc_obj;


/*霍尔传感器端口定义*/
#define HALL_SENSOR_U_PORT 		GPIOA
#define HALL_SENSOR_U_PIN		GPIO_PIN_6
#define HALL_SENSOR_V_PORT		GPIOA
#define HALL_SENSOR_V_PIN		GPIO_PIN_7
#define HALL_SENSOR_W_PORT		GPIOB
#define HALL_SENSOR_W_PIN		GPIO_PIN_0

/*UVW相下桥臂定义*/
#define M_LOW_SIDE_U_PORT		GPIOE
#define M_LOW_SIDE_U_PIN		GPIO_PIN_10
#define M_LOW_SIDE_V_PORT		GPIOE
#define M_LOW_SIDE_V_PIN		GPIO_PIN_12
#define M_LOW_SIDE_W_PORT		GPIOE
#define M_LOW_SIDE_W_PIN		GPIO_PIN_14

//最大比较寄存器设置值
#define MAX_CCR_LOAD			800-1

/*shutdown 低电平有效，低电平触发shutdown关闭控制*/
#define M_SD_PORT				GPIOE
#define M_SD_PIN				GPIO_PIN_8

extern bldc_obj g_bldc_motor;

void start_motor(void);
void stop_motor(void);
uint8_t hall_sensor(void);
void m_uhvl(void);
void m_uhwl(void);
void m_vhul(void);
void m_vhwl(void);
void m_whul(void);
void m_whvl(void);

#endif /* INC_MOTOR_CONTROL_H_ */
