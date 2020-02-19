/*
 * PWM.c
 *
 * Created: 18/02/2020 09:53:30 ص
 *  Author: TOSHIBA
 */ 

#include "PWM.h"
#define OCR1A_NON_INVERTING_MODE (0x80)
#define OCR1B_NON_INVERTING_MODE (0x20)
#define PHASE_CORRECT_WG11_00BITS  (0x02)
#define PHASE_CORRECT_WG12_13BITS  (0x10)
#define WRITE_TO_TCCRA  (0xf3);
#define STOP_OCR1A   (0x3F)
#define STOP_OCR1B   (0xCF)



#define FRE_100_ICR_ (78)




#define TIMER1_NO_CLOCK       (0xfff8)
#define TIMER1_PRESCALER_NO   (0x0001)
#define TIMER1_PRESCALER_8    (0x0002)
#define TIMER1_PRESCALER_64   (0x0003)
#define TIMER1_PRESCALER_256  (0x0004)
#define TIMEr1_PRESCALER_1024 (0x0005)


static uint8_t u8_PWM_CH1A_Prescaler=0;
static uint8_t u8_PWM_CH1B_Prescaler=0;

extern u8_ERROR_STATUS_t Pwm_Init(gstr_Pwm_Cfg_t *psrt_Pwm_Cfg){
	
	if (psrt_Pwm_Cfg!=NULL){
		switch (psrt_Pwm_Cfg->u8_Channel){
			case  PWM_CH1A :
			

		    PORTD_DIR|=BIT5;
			//TCCR1A&=WRITE_TO_TCCRA  ;    
		    TCCR1A|=OCR1A_NON_INVERTING_MODE| PHASE_CORRECT_WG11_00BITS;
			TCCR1B|= PHASE_CORRECT_WG12_13BITS ;
			
			switch(psrt_Pwm_Cfg->u8_Prescaler){
				case PWM_PRESCALER_NO:
				u8_PWM_CH1A_Prescaler=TIMER1_PRESCALER_NO;
				break;
				case PWM_PRESCALER_8 :
				u8_PWM_CH1A_Prescaler=TIMER1_PRESCALER_8;
				break;
				case PWM_PRESCALER_64:
				u8_PWM_CH1A_Prescaler=TIMER1_PRESCALER_64;
				break;
				case PWM_PRESCALER_256:
				u8_PWM_CH1A_Prescaler=TIMER1_PRESCALER_256;
				break;
				case PWM_PRESCALER_1024:
				u8_PWM_CH1A_Prescaler=TIMEr1_PRESCALER_1024;
				break;
				default: 
				return E_NOK;	
			}
			  PORTD_DIR|=BIT5;
			
			break;
			case PWM_CH1B:
			TCNT1=0;
			ICR1=0;
			OCR1B=0;
				PORTD_DIR|=BIT4;
				TCCR1A&=WRITE_TO_TCCRA  ;
				TCCR1A|=OCR1B_NON_INVERTING_MODE| PHASE_CORRECT_WG11_00BITS;
				TCCR1B|= PHASE_CORRECT_WG12_13BITS ;
				
				switch(psrt_Pwm_Cfg->u8_Prescaler){
					case PWM_PRESCALER_NO:
					u8_PWM_CH1B_Prescaler=TIMER1_PRESCALER_NO;
					break;
					case PWM_PRESCALER_8 :
					u8_PWM_CH1B_Prescaler=TIMER1_PRESCALER_8;
					break;
					case PWM_PRESCALER_64:
					u8_PWM_CH1B_Prescaler=TIMER1_PRESCALER_64;
					break;
					case PWM_PRESCALER_256:
					u8_PWM_CH1B_Prescaler=TIMER1_PRESCALER_256;
					break;
					case PWM_PRESCALER_1024:
					u8_PWM_CH1B_Prescaler=TIMEr1_PRESCALER_1024;
					break;
					default:
					return E_NOK;
				}
				
			break;
			default:
			return E_NOK;
		}
		return E_OK;
	}
	else 
	return E_NOK;
}

extern u8_ERROR_STATUS_t Pwm_Start(uint8_t u8_Channel,uint8_t u8_Duty,uint32_t u32_Frequncy)
{
	switch (u8_Channel){
		
		case PWM_CH1A:
		switch(u32_Frequncy){
			
			case FREQ_100_:
			ICR1=FRE_100_ICR_;
			OCR1A=((uint32_t) FRE_100_ICR_*u8_Duty)/100;
			TCCR1|=TIMEr1_PRESCALER_1024 ;
			break;
			default:
			return E_NOK;
		}
		
		break;
		
		case PWM_CH1B :
		switch(u32_Frequncy){
			
			case FREQ_100_:
			ICR1=FRE_100_ICR_;
			OCR1B=((uint32_t) FRE_100_ICR_*u8_Duty)/100;
			TCCR1|=TIMEr1_PRESCALER_1024 ;
			break;
			default:
			return E_NOK;
		}
		break;	
		default:
		return E_NOK;
	}
	return E_OK;
}

extern u8_ERROR_STATUS_t Pwm_Update(uint8_t u8_Channel,uint8_t u8_Duty,uint32_t u32_Frequncy)	
	{
		switch (u8_Channel){
			
			case PWM_CH1A:
			switch(u32_Frequncy){
				
				case FREQ_100_:
				ICR1=FRE_100_ICR_;
				OCR1A=(FRE_100_ICR_*u8_Duty)/100;
				break;
				default:
				return E_NOK;
			}
			
			break;
			
			case PWM_CH1B :
			switch(u32_Frequncy){
				
				case FREQ_100_:
				ICR1=FRE_100_ICR_;
				OCR1A=(FRE_100_ICR_*u8_Duty)/100;
				break;
				default:
				return E_NOK;
			}
			break;
		default:
		return E_NOK;
		}
		return E_OK;
	}

extern u8_ERROR_STATUS_t Pwm_Stop(uint8_t u8_Channel){
	switch (u8_Channel){
		case PWM_CH1A  :
		TCCR1A&= STOP_OCR1A;
		break;
		case PWM_CH1B:
		TCCR1A&= STOP_OCR1B;
		break;
		default:
		return E_NOK;
	}
	return E_OK;
}