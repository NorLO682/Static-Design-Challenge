/*
 * Steering.c
 *
 * Created: 19/02/2020 03:40:30 م
 *  Author: TOSHIBA
 */ 

#include "motor.h"
#include "Steering.h"
u8_ERROR_STATUS_t Steering_Init(void){
	Motor_Init(MOTOR_1);
	Motor_Init(MOTOR_2);
	return E_OK;
}
u8_ERROR_STATUS_t Steering_SteerCar(uint8_t u8_Steering_CarCmd, uint8_t u8_speed){
	uint8_t u8_MotorErrorStatus;
	switch(u8_Steering_CarCmd){
		
		case CAR_STOP :
	   Motor_Stop(MOTOR_1);
	   Motor_Stop(MOTOR_2);
	   u8_MotorErrorStatus=E_OK;
		break;
		
		case  CAR_FORWARD:
			Motor_Direction(MOTOR_1,MOTOR_FORWARD);
			Motor_Direction(MOTOR_2,MOTOR_FORWARD);
			Motor_Start(MOTOR_1,u8_speed);
			Motor_Start(MOTOR_2,u8_speed);
			u8_MotorErrorStatus=E_OK;
		break;
		
		case  CAR_BACKWARD :
		Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		Motor_Start(MOTOR_1,u8_speed);
		Motor_Start(MOTOR_2,u8_speed);
		u8_MotorErrorStatus=E_OK;
		break;
		
		case CAR_RIGHT :
		Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		Motor_Start(MOTOR_1,u8_speed);
		Motor_Start(MOTOR_2,u8_speed);
		u8_MotorErrorStatus=E_OK;
		break;
		
		case CAR_LEFT:
		Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2,MOTOR_FORWARD);
		Motor_Start(MOTOR_1,u8_speed);
		Motor_Start(MOTOR_2,u8_speed);
		u8_MotorErrorStatus=E_OK;
		break;
		
		default:
		u8_MotorErrorStatus=E_NOK;
		break;	
		
	}
	return u8_MotorErrorStatus;
}