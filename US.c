/*
 * US.c
 *
 * Created: 19/02/2020 11:34:54 ص
 *  Author: TOSHIBA
 */ 
#include "US.h"
#include "softwareDelay.h"

#define GPIO_TRIGGER_PORT GPIOB

#define GPIO_TRIGGER_PIN  BIT0

gstr_DIO_Cfg_t  str_US_pinConf={GPIO_TRIGGER_PORT, GPIO_TRIGGER_PIN ,OUTPUT};


gstr_Icu_cfg_t str_ICU_Cfg ={ICU_CH2,ICU_TIMER_CH0};
	

u8_ERROR_STATUS_t Us_Init(void){
	
	//DIO_init (&str_US_pinConf);
	//DIO_Write (GPIO_TRIGGER_PORT, GPIO_TRIGGER_PIN ,LOW);
	PORTB_DIR |= 0x01;
	Icu_Init(&str_ICU_Cfg);
	return E_OK;
}
u8_ERROR_STATUS_t Us_Trigger(void){
	DIO_Write (GPIO_TRIGGER_PORT, GPIO_TRIGGER_PIN ,HIGH);
	
	softwareDelayMs(15);
	
	DIO_Write (GPIO_TRIGGER_PORT, GPIO_TRIGGER_PIN ,LOW);
	return E_OK;
}

u8_ERROR_STATUS_t Us_GetDistance(uint16_t *pu16_Distance){
	uint32_t  pu16_Temp;
	Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL, &pu16_Temp);

	*pu16_Distance = pu16_Temp ;
	
	
	//softwareDelayMs(60);
	return E_OK;
}