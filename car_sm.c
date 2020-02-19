/*
 * car_sm.c
 *
 * Created: 19/02/2020 04:02:58 م
 *  Author: TOSHIBA
 */ 
#include "car_sm.h"
#include "softwareDelay.h"
#include "US.h"
#include "Steering.h"
u8_ERROR_STATUS_t Car_SM_Init(void){
	
Us_Init();
Steering_Init();
Steering_SteerCar(CAR_FORWARD,30);
return E_OK;
}
u8_ERROR_STATUS_t Car_SM_Update(void){
	uint16_t u16_distance;
	Us_Trigger();
	Us_GetDistance(&u16_distance);
	if(u16_distance>45){
		Steering_SteerCar(CAR_FORWARD,30);
		softwareDelayMs(150);
	}
	else if  (u16_distance>30){
		/*Steering_SteerCar(CAR_STOP	,0);*/
		//softwareDelayMs(50);
		Steering_SteerCar(CAR_RIGHT	,30);
		softwareDelayMs(200);	
	}
	else {
// 			Steering_SteerCar(CAR_STOP	,0);
// 			softwareDelayMs(50);
			Steering_SteerCar(CAR_BACKWARD,30);
			softwareDelayMs(150);
			
	}
	return E_OK;
}