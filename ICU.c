/*
 * ICU.c
 *
 * Created: 18/02/2020 09:50:58 م
 *  Author: TOSHIBA
 */ 

#include "ICU.h"

#define  SWICU_EDGE_MASK (0x40)

#define TICK_TIME_IN_MICRO 64

#define  INT2_INTER_FLAG_BIT  BIT5
#define  INT2_INTER_BIT       BIT5

#define GENERAL_INTERRUPT_BIT BIT7


#define EN_SW_ICU_PORT  GPIOB
#define EN_SW_ICU_PIN   BIT2


#define RISSING_EDGGE 1
#define FALLING_EDGGE 2
#define STOP_INERE  3

#define TIMER_COUNT_NU   (255)

static uint8_t TimerCH;

volatile uint8_t interrupt_phase= RISSING_EDGGE;


gstr_DIO_Cfg_t  str_ICU_CH2={ EN_SW_ICU_PORT,EN_SW_ICU_PIN,INPUT};

gstrTimerConfig_t str_ICU_TIMER_CH2={TIMER_CH_2,TIMER_MODE,TIMER2_PRESCALER_1024,TIMER_MODE_POOLING};	//1024			
											

u8_ERROR_STATUS_t Icu_Init(gstr_Icu_cfg_t * str_Icu_Cfg){
	 uint8_t u8_MotorErrorStatus;
	 if(str_Icu_Cfg!=NULL){
		 
		 switch(str_Icu_Cfg->ICU_Ch_No){
			 case ICU_CH2:
			 DIO_init (&str_ICU_CH2);
			  SET_BIT(MCUCSR,SWICU_EDGE_MASK);
			  SET_BIT(GIFR,INT2_INTER_FLAG_BIT);
			  SET_BIT(GICR, INT2_INTER_BIT);
			 u8_MotorErrorStatus=E_OK;
			 break;
			 default:
			 u8_MotorErrorStatus=E_NOK;
			 break;
		 }
		 switch (str_Icu_Cfg->ICU_Ch_Timer){
			 
			 case ICU_TIMER_CH0 :
			 Timer_Init(&str_ICU_TIMER_CH2);
			 TimerCH=TIMER_CH_2;
			 u8_MotorErrorStatus=E_OK;
			 break;
			 
			 default:
			 u8_MotorErrorStatus=E_NOK;
			 break;	 
		 }		
		
		 SET_BIT(SREG,GENERAL_INTERRUPT_BIT);
	 }
	 else 
	 u8_MotorErrorStatus=E_NOK;
	 return  u8_MotorErrorStatus;
	 }
	 
	 
	 
	 
u8_ERROR_STATUS_t Icu_ReadTime(uint8_t u8_Icu_Channel, uint8_t u8_Icu_EdgeToEdge, uint32_t * pu32_Icu_Time){
	uint8_t u8_MotorErrorStatus;
	if(pu32_Icu_Time!=NULL){
	switch (u8_Icu_Channel){
		case ICU_CH2 :
		
		switch (u8_Icu_EdgeToEdge){

			case ICU_RISE_TO_FALL:
			while( interrupt_phase!=STOP_INERE);
			
			Timer_GetValue( TimerCH ,(uint16_t*)pu32_Icu_Time);
			
			interrupt_phase= RISSING_EDGGE;
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
	}
	
	else 
	u8_MotorErrorStatus=E_NOK;
	return  u8_MotorErrorStatus;
}


MY_ISR(INT2_vect){
	switch (interrupt_phase){
		case RISSING_EDGGE:
		Timer_Start(TimerCH,TIMER_COUNT_NU );
		CLEAR_BIT(GICR, INT2_INTER_BIT);
		CLEAR_BIT(MCUCSR,SWICU_EDGE_MASK);
		 SET_BIT(GICR, INT2_INTER_BIT);
		interrupt_phase=FALLING_EDGGE;
	
		break;
		
		case FALLING_EDGGE:
		Timer_Stop(TimerCH);
		CLEAR_BIT(GICR, INT2_INTER_BIT);
		SET_BIT(MCUCSR,SWICU_EDGE_MASK);
		SET_BIT(GICR, INT2_INTER_BIT);
		interrupt_phase=STOP_INERE;
		break;
	}
}