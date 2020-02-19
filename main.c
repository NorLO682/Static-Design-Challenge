/*
 * car_steering.c
 *
 * Created: 16/02/2020 09:11:31 م
 * Author : TOSHIBA
 */ 

// #include "DIO.h"
// #include "Timer.h"
// #include "PWM.h"
 #include "motor.h"
 #include "softwareDelay.h"
// #include "ICU.h"
 #include "US.h"
#include "car_sm.h"



int main(){
	 Car_SM_Init();
	 while (1){
		  Car_SM_Update();
	 }
	return 0;
}

/*int main(){
 	
 	PORTB_DIR |= 0xf0;
	 
 	 
 	 uint16_t data = 0;
 	 
	  Us_Init();
	  
	 while(1){
		 Us_Trigger();
		  Us_GetDistance(& data); 
		 PORTB_DATA=( PORTB_DATA&0x0f)|(data<<4);
		  softwareDelayMs(250);
		  
	 }
	return 0;
 }*/






/*int main (){
	uint32_t data=0;
	gstr_Icu_cfg_t  icu={ICU_CH2,ICU_TIMER_CH0};
	gstr_DIO_Cfg_t gpio={GPIOA,FULL_PORT,OUTPUT};
	DIO_init (&gpio);
	Icu_Init(& icu);
	while (1){
		Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL,&data);
		//DIO_Write (GPIOA,FULL_PORT,data);
		PORTA_DATA=data;
		softwareDelayMs(100);
	}
	return 0;
}*/
/*int main(){
	
 	Motor_Init(MOTOR_1);
 	Motor_Direction(MOTOR_1,MOTOR_FORWARD);
	
	Motor_Init(MOTOR_2);
	Motor_Direction(MOTOR_2,MOTOR_FORWARD);
	
	Motor_Start(MOTOR_1,80);
	Motor_Start(MOTOR_2,80);
	while (1);
	
	
	return 0;
	
}*/




 /*int main (){
	 gstr_Pwm_Cfg_t srt_Pwm_Cfg={
		 PWM_CH1B,
		 PWM_PRESCALER_1024 };
	
	Pwm_Init(&srt_Pwm_Cfg);
	 Pwm_Start( PWM_CH1B,80,FREQ_100_);
	 
	 while (1){
		 
	 }
	 
	 return 0;
 }*/





















/*
int main(void)
{uint8_t status =0,counter=0;
	
	gstr_DIO_Cfg_t gpio={GPIOA,FULL_PORT,OUTPUT};
		
	gstrTimerConfig_t timer0={	TIMER_CH_2 ,
		                        TIMER_MODE,
								TIMER2_PRESCALER_256,
								TIMER_MODE_POOLING
								};
	 
	 DIO_init(&gpio);
	 Timer_Init(&timer0);
	 DIO_Write(GPIOA,UPPER_NIBBLE,HIGH);
	
  
    while (1) 
    {
		
		for (counter=0;counter<=244;counter++){
			//status=0;
		Timer_Start (TIMER_CH_2,255);
        Timer_GetStatus(TIMER_CH_2,&status);
		 
		while (!status){
		Timer_GetStatus(TIMER_CH_2,&status);
		}
		
		//SET_BIT(TIFR,0x40);
		}
	   
		DIO_Toggle(GPIOA,FULL_PORT);
    }
	return 0;
}*/

