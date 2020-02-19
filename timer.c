/*
 * timer.c
 *
 * Created: 16/02/2020 10:10:56 م
 *  Author: TOSHIBA
 */ 

/*****************************************************************************************************/
/*                                        INCLUDES                                                  */
/***************************************************************************************************/
#include "timer.h"

#define GENERAL_INTERRUPT_BIT (0x80)
/*#define timer 0*/
#define TIMER0_POLLING              (0)
#define TIMER0_INTERRUPT_NORMAL    (0x01)
#define TIMER0_NORMAL_MODE           (0)
#define COUNTER_FALLING_EDGE 0x06
#define COUNTER_RISSING_EDGE 0x07
#define TIMER0_TOV0_BIT       (0x01)
#define TIMER0_RESLUTION        (255)
//TIMER1
#define TIMER1_TOV1_BIT       (0x04)
#define TIMER1_NORMAL_MODE         (0x00)
#define TIMER1_INTERRUPT_NORMAL (0x04)
#define TIMER1_RESLUTION        (65536)
#define TIMER1_MASK_DIS_EN_I        (0xC3)

//TIMER2 
#define TIMER2_TOV2_BIT         (0x40)
#define TIMER2_INTERRUPT_NORMAL (0x40)
#define TIMER2_NORMAL_MODE      (0x00)
#define TIMER2_RESLUTION        (255)

 
static uint8_t gu8_PrescalerTimer0=0;
static uint8_t gu8_PrescalerTimer1=0;
static uint8_t gu8_PrescalerTimer2=0;




extern uint8_t Timer_Init(gstrTimerConfig_t* pstrTimerConf){
	if(pstrTimerConf!=NULL){
		switch(pstrTimerConf->u8_TimerCh){
			case TIMER_CH_0:
			TCCR0=0x00;
			TCNT0=0x00;
			SET_BIT(TIFR,TIMER0_TOV0_BIT);
			TCCR0|=TIMER0_NORMAL_MODE;
			if(pstrTimerConf->u8_Timer_INT_Mode==TIMER_MODE_INT)
			{
				 TIMSK|=TIMER0_INTERRUPT_NORMAL;
				 SET_BIT(SREG,GENERAL_INTERRUPT_BIT);
			}
// 			switch (pstrTimerConf->u8_TimerMode)
// 			{
// 				case COUNTER_MODE_FALLING_EDGE:
// 				TCCR0|= COUNTER_FALLING_EDGE;
// 				break;
// 				case COUNTER_MODE_RISSING_EDGE:
// 				TCCR0|= COUNTER_RISSING_EDGE;
// 				break;
// 			}
			gu8_PrescalerTimer0=pstrTimerConf->u8_TimerPrescaler;
			break;
			
			
			case TIMER_CH_1 :
			 TCCR1=0;
			 TCNT1=0;
			 SET_BIT(TIFR,TIMER1_TOV1_BIT);
			  TCCR1 |=TIMER1_NORMAL_MODE;
			if(pstrTimerConf->u8_Timer_INT_Mode==TIMER_MODE_INT)
			{
				TIMSK|=TIMER1_INTERRUPT_NORMAL;
				SET_BIT(SREG,GENERAL_INTERRUPT_BIT);
			}
// 			switch (pstrTimerConf->u8_TimerMode)
// 			{
// 				case COUNTER_MODE_FALLING_EDGE:
// 				TCCR0|= COUNTER_FALLING_EDGE;
// 				break;
// 				case COUNTER_MODE_RISSING_EDGE:
// 				TCCR0|= COUNTER_RISSING_EDGE;
// 				break;
// 			}
			gu8_PrescalerTimer1=pstrTimerConf->u8_TimerPrescaler;
			break;
// 			
			case TIMER_CH_2 :
				TCCR2=0x00;
				TCNT2=0x00;
				ASSR=0;
				SET_BIT(TIFR,TIMER2_TOV2_BIT);
				TCCR2|=TIMER2_NORMAL_MODE;
				if(pstrTimerConf->u8_Timer_INT_Mode==TIMER_MODE_INT)
				{
					TIMSK|=TIMER2_INTERRUPT_NORMAL;
					SET_BIT(SREG,GENERAL_INTERRUPT_BIT);
				}
// 				switch (pstrTimerConf->u8_TimerMode)
// 				{
// 					//NOT handle it ASSR 
// 				}
				gu8_PrescalerTimer2=pstrTimerConf->u8_TimerPrescaler;
				break;
				
			break;
			
			default:
			return E_NOK;
 		}
		return E_OK ; 
		
	}
	else 
	return E_NOK ;
}

extern uint8_t Timer_Start (uint8_t u8_TimerCh,uint16_t u16_CountNO){
	uint8_t u8_register_status=0;
	switch(u8_TimerCh){
		case  TIMER_CH_0 :
		if (u16_CountNO<=255){
			
		TCNT0=(TIMER0_RESLUTION-u16_CountNO);
		TCCR0|=	gu8_PrescalerTimer0;// not handle
		}
		
		else
		 return E_NOK;
		break;
		
		case TIMER_CH_1:
		 u8_register_status=TIMSK;
		TIMSK&=TIMER1_MASK_DIS_EN_I ;
		TCNT1 =(TIMER1_RESLUTION-u16_CountNO);
		TIMSK=u8_register_status;
		TCCR1|=gu8_PrescalerTimer1;
			break;
		
		
		case  TIMER_CH_2:
		if (u16_CountNO<=255){//there is special case if the timer is in counter mode not handle 
			
			TCNT2=(TIMER0_RESLUTION-u16_CountNO);
			TCCR2|=	gu8_PrescalerTimer2;
		}
		else 
		return E_NOK;
		break;
		default:
		return E_NOK;
	}
	return E_OK;
	
	}


extern uint8_t Timer_Stop(uint8_t u8_TimerCh){
	
		switch(u8_TimerCh){
		case TIMER_CH_0:
		TCCR0&=TIMER0_NO_CLOCK;
		break;
		
		case TIMER_CH_1:
		TCCR1B&=TIMER1_NO_CLOCK;
		break;
		
		case TIMER_CH_2:
		TCCR2&=TIMER2_NO_CLOCK;
		break;
		default:
		return E_NOK;
		}
		return E_OK;
		}
	


extern uint8_t Timer_GetValue(uint8_t u8_TimerCh,uint16_t *pu16_TimerValue){
	uint8_t u8_TIMSK_StatusRegister=0;
		switch(u8_TimerCh){
			case TIMER_CH_0 :
			*pu16_TimerValue=TCNT0;
			break;
			
			case TIMER_CH_1 :
			
			 u8_TIMSK_StatusRegister=TIMSK;
			TIMSK&=TIMER1_MASK_DIS_EN_I ;
			*pu16_TimerValue=TCNT1;
			TIMSK=u8_TIMSK_StatusRegister;
			break;
			
			case TIMER_CH_2 ://there is special case in counter mode ASSR Note handle 
			*pu16_TimerValue=TCNT2;
			break;
			default:
			return E_NOK;
		}
		
		
		return E_OK;
	}



extern uint8_t Timer_SetValue(uint8_t TimerCh,uint16_t u16_TimerValue){
   uint8_t u8_TIMSK_StatusRegister=0;
   switch(TimerCh){
		case TIMER_CH_0  :
		if (u16_TimerValue<=TIMER0_RESLUTION){
			TCNT0 = u16_TimerValue;
		}
		else 
		return E_NOK;
		break; 
		
		case TIMER_CH_1:
		 u8_TIMSK_StatusRegister=TIMSK;
		TIMSK&=TIMER1_MASK_DIS_EN_I ;
		TCNT1 =u16_TimerValue;
		TIMSK=u8_TIMSK_StatusRegister;
		break;
		
		case TIMER_CH_2 :
		if (u16_TimerValue<=TIMER2_RESLUTION){ //ASSR CASE
		TCNT2 = u16_TimerValue;	
		}
		else
		return E_NOK;
		break;
		default:
		return E_NOK;
   }
		return E_OK;
}

	


extern uint8_t Timer_GetStatus(uint8_t u8_TimerCh,uint8_t *pu8_TimerStatus){//how to handle the high return 
	
		switch(u8_TimerCh){
			
		case TIMER_CH_0 :
		*pu8_TimerStatus=READ_BIT(TIFR,TIMER0_TOV0_BIT);
		SET_BIT(TIFR,TIMER0_TOV0_BIT);

		break;
		
		case TIMER_CH_1:
		*pu8_TimerStatus=READ_BIT(TIFR,TIMER1_TOV1_BIT);
		SET_BIT(TIFR,TIMER1_TOV1_BIT);
		break;
		
		case TIMER_CH_2:
		  	*pu8_TimerStatus=READ_BIT(TIFR,TIMER2_TOV2_BIT);
	        SET_BIT(TIFR,TIMER2_TOV2_BIT);
	   	   SET_BIT(TIFR,TIMER2_TOV2_BIT);//why
			   
         break;
		// return E_OK;
	
       default:
	   return E_NOK;
	 
		}
		return E_OK;

}
