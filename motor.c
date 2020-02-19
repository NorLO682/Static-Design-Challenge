/*
 * motor.c
 *
 * Created: 18/02/2020 05:24:12 م
 *  Author: TOSHIBA
 */ 


#include  "motor.h"

#define MOTOR_EN_1_GPIO		(GPIOD)
#define MOTOR_OUT_1A_GPIO	(GPIOD)
#define MOTOR_OUT_1B_GPIO	(GPIOD)

#define MOTOR_EN_2_GPIO		(GPIOD)
#define MOTOR_OUT_2A_GPIO	(GPIOD)
#define MOTOR_OUT_2B_GPIO	(GPIOD)

#define MOTOR_EN_1_BIT		(BIT4)
#define MOTOR_OUT_1A_BIT	(BIT2)
#define MOTOR_OUT_1B_BIT	(BIT3)

#define MOTOR_EN_2_BIT		(BIT5)
#define MOTOR_OUT_2A_BIT	(BIT6)
#define MOTOR_OUT_2B_BIT	(BIT7)

#define MOTOR_EN_1_PWM_CH   (PWM_CH1B)
#define MOTOR_EN_2_PWM_CH   (PWM_CH1A)


#define MOTOE_UNINTI (0)
#define MOTOE_INTI (1)

static gstr_DIO_Cfg_t str_Motor1Info={
	                      GPIOD,
						  MOTOR_EN_1_BIT|MOTOR_OUT_1A_BIT
						  |MOTOR_OUT_1B_BIT,
						  OUTPUT};
						  
static gstr_DIO_Cfg_t str_Motor2Info={
		GPIOD,
		MOTOR_EN_2_BIT|MOTOR_OUT_2A_BIT
		|MOTOR_OUT_2B_BIT,
	      OUTPUT};
	
static gstr_Pwm_Cfg_t str_Motor1_EN={
	                  	MOTOR_EN_1_PWM_CH ,
						PWM_PRESCALER_1024};

static gstr_Pwm_Cfg_t str_Motor2_EN={
		MOTOR_EN_2_PWM_CH ,
	     PWM_PRESCALER_1024};							
						
						
static uint8_t Motor1_InitFlag=MOTOE_UNINTI;				 
static uint8_t Motor2_InitFlag=MOTOE_UNINTI;	
					  
	

u8_ERROR_STATUS_t Motor_Init(uint8_t u8_Motor_Number){
	uint8_t u8_MotorErrorStatus;
	switch( u8_Motor_Number){
		case MOTOR_1	:
		DIO_init(&str_Motor1Info);
		 Motor1_InitFlag=MOTOE_INTI;
		u8_MotorErrorStatus= E_OK;
		break;
		case MOTOR_2 :
		DIO_init(&str_Motor2Info);
		Motor2_InitFlag=MOTOE_INTI;
		u8_MotorErrorStatus= E_OK;
		break;
	default:
	u8_MotorErrorStatus= E_NOK;
	break;
	}
	return u8_MotorErrorStatus;
}

u8_ERROR_STATUS_t Motor_Direction(uint8_t u8_Motor_Number, uint8_t u8_Motor_Direction){
	uint8_t u8_MotorErrorStatus;
	switch (u8_Motor_Number){
		case MOTOR_1 :
		switch (u8_Motor_Direction){
			
			case MOTOR_STOP :
			DIO_Write (MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
			DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
			u8_MotorErrorStatus=E_OK;
			break;
			
			case MOTOR_FORWARD:
			DIO_Write (MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
			DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
			
			u8_MotorErrorStatus=E_OK;
			break;
			
			case  MOTOR_BACKWARD:
			 DIO_Write (MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
			 DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,HIGH);
			
			u8_MotorErrorStatus=E_OK;
			break;
			
			default:
			u8_MotorErrorStatus=E_NOK;
			break;
		}
		break;
		case MOTOR_2 :
		switch (u8_Motor_Direction){
			
			case MOTOR_STOP :
			DIO_Write (MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
			DIO_Write (MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
			u8_MotorErrorStatus=E_OK;
			break;
			
			case MOTOR_FORWARD:
			DIO_Write (MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
			DIO_Write (MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
			
			u8_MotorErrorStatus=E_OK;
			break;
			
			case  MOTOR_BACKWARD:
			DIO_Write (MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
			DIO_Write (MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,HIGH);
			
			u8_MotorErrorStatus=E_OK;
			break;
			
			default:
			u8_MotorErrorStatus=E_NOK;
			break;
		}
		break;
		default:
		u8_MotorErrorStatus=E_NOK;
		break;
	}
	return u8_MotorErrorStatus;
}

u8_ERROR_STATUS_t Motor_Start(uint8_t u8_Motor_Number, uint8_t u8_Mot_Speed){
	uint8_t u8_MotorErrorStatus;
	switch (u8_Motor_Number){
		case MOTOR_1 :
		
		Pwm_Init(&str_Motor1_EN);
		Pwm_Start(MOTOR_EN_1_PWM_CH,u8_Mot_Speed,FREQ_100_ );
		u8_MotorErrorStatus=E_OK;
		break;
		 
		case MOTOR_2 :
		Pwm_Init(&str_Motor2_EN);
		Pwm_Start(MOTOR_EN_2_PWM_CH,u8_Mot_Speed,FREQ_100_ );
		u8_MotorErrorStatus=E_OK;
		break;
		
		default:
		u8_MotorErrorStatus=E_NOK;
		break;
	}
	return u8_MotorErrorStatus;
	
}
u8_ERROR_STATUS_t Motor_SpeedUpdate(uint8_t u8_Motor_Number, uint8_t u8_Speed){
	uint8_t u8_MotorErrorStatus;
	switch (u8_Motor_Number){
		case MOTOR_1:
		Pwm_Start(MOTOR_EN_1_PWM_CH,u8_Speed,FREQ_100_ );
		u8_MotorErrorStatus=E_OK;
		break;
		
		case MOTOR_2:
		Pwm_Start(MOTOR_EN_2_PWM_CH,u8_Speed,FREQ_100_ );
		u8_MotorErrorStatus=E_OK;
		break;
		
		default:
		u8_MotorErrorStatus=E_NOK;
		break;
	}
	return u8_MotorErrorStatus;
}
u8_ERROR_STATUS_t Motor_Stop(uint8_t u8_Motor_Number){
	uint8_t u8_MotorErrorStatus;
	switch (u8_Motor_Number){
		case MOTOR_1 :
			DIO_Write (MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
			DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
			u8_MotorErrorStatus=E_OK;
			break;
			case MOTOR_2 :
				DIO_Write (MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
				DIO_Write (MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
				u8_MotorErrorStatus=E_OK;
				break;
				default:
				u8_MotorErrorStatus=E_NOK;
				break;
	}
		return 	u8_MotorErrorStatus;
}
u8_ERROR_STATUS_t Motor_GetStatus(uint8_t u8_Motor_Number, uint8_t* pu8_Mot_status){
	uint8_t u8_MotorErrorStatus;
	switch (u8_Motor_Number){
		case MOTOR_1	 :
		* pu8_Mot_status=Motor1_InitFlag;
		u8_MotorErrorStatus=E_OK;
		break;
		case  MOTOR_2 :
		* pu8_Mot_status=Motor2_InitFlag;
		u8_MotorErrorStatus=E_OK;
		break;
		default:
		u8_MotorErrorStatus=E_NOK;
		break;
	}
	return  u8_MotorErrorStatus;
}