/*
 * exti_handler.c
 *
 *  Created on: Mar 5, 2024
 *      Author: chungus237
 */
#include "exti_handler.h"
#include "tim.h"
#include "motor_control.h"

 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
	 if(htim == &htim1)
	 {
		 if(g_bldc_motor.runflag == 1)
		 {
			 g_bldc_motor.step_sta = hall_sensor();
			 if(g_bldc_motor.step_sta >= 1 && g_bldc_motor.step_sta<=6)
			 {
				 switch(g_bldc_motor.step_sta)
				 {
				 case 0x1:
					 m_uhwl();
					 break;
				 case 0x2:
					 m_vhul();
					 break;
				 case 0x3:
					 m_vhwl();
					 break;
				 case 0x4:
					 m_whvl();
					 break;
				 case 0x5:
					 m_uhvl();
					 break;
				 case 0x6:
					 m_whul();
					 break;
				 default:
					 break;
				 }
			 }
		 }
	 }
 }
