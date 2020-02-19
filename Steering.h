/*
 * Steering.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Zayed & Saad
 */

#ifndef STEERING_H_
#define STEERING_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"


/*
 *  INCLUDE MOTOR.H HERE
 */

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/

/*Command Macros to call the steering api*/
#define		CAR_STOP		0
#define		CAR_FORWARD		1
#define		CAR_BACKWARD	2
#define		CAR_RIGHT		3
#define		CAR_LEFT		4

/************************************************************************/
/*		      STEERING FUNCTIONS' PROTOTYPES		        */
/************************************************************************/


/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

u8_ERROR_STATUS_t Steering_Init(void);

/**
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This funtion controls the command and the speed of the car.
 * 							
 */
u8_ERROR_STATUS_t Steering_SteerCar(uint8_t u8_Steering_CarCmd, uint8_t u8_speed);





#endif /* STEERING_H_ */