/*
 * Timer.h
 *
 * Created: 16/02/2020 09:34:17 م
 *  Author: TOSHIBA
 */ 


#ifndef __TIMER_H__
#define __TIMER_H__
/*****************************************************************************************************/
/*                                        INCLUDES                                                  */
/***************************************************************************************************/
#include "std_types.h"
#include "registers.h"
#include "common_macros.h"

/*****************************************************************************************************/
/*                                        DEFINES                                                   */
/***************************************************************************************************/

    /*    TIMER_CHANEELS     */
#define TIMER_CH_0     (0)
#define TIMER_CH_1     (1)
#define TIMER_CH_2     (2)

   /*   TIMER_MOODES        */
#define TIMER_MODE     (0)
#define COUNTER_MODE_FALLING_EDGE   (1)
#define COUNTER_MODE_RISSING_EDGE   (2)

  /* TIMER_INTERRUPT_MODE  */
#define TIMER_MODE_INT   (0)
#define TIMER_MODE_POOLING (1)


/*   TIMER0_PRESCALER  */
#define TIMER0_NO_CLOCK       (0xf8)
#define TIMER0_PRESCALER_NO   (0x01)
#define TIMER0_PRESCALER_8    (0x02)
#define TIMER0_PRESCALER_64   (0x03)
#define TIMER0_PRESCALER_256  (0x04)
#define TIMER0_PRESCALER_1024 (0x05)
/*   TIMER1_PRESCALER  */
#define TIMER1_NO_CLOCK       (0xfff8)
#define TIMER1_PRESCALER_NO   (0x0001)
#define TIMER1_PRESCALER_8    (0x0002)
#define TIMER1_PRESCALER_64   (0x0003)
#define TIMER1_PRESCALER_256  (0x0004)
#define TIMEr1_PRESCALER_1024 (0x0005)
/*   TIMER2_PRESCALER  */
#define TIMER2_NO_CLOCK      (0Xf8)
#define TIMER2_PRESCALER_NO  (0x01)
#define TIMER2_PRESCALER_8   (0x02)
#define TIMER2_PRESCALER_32  (0x03)
#define TIMER2_PRESCALER_64  (0x04)
#define TIMER2_PRESCALER_128 (0x05)
#define TIMER2_PRESCALER_256 (0x06)
#define TIMER2_PRESCALER_1024 (0x07)
 
/*****************************************************************************************************/
/*                                       STRUCTS                                                    */
/***************************************************************************************************/
typedef struct{
	uint8_t u8_TimerCh;
	uint8_t u8_TimerMode;
	uint8_t u8_TimerPrescaler;
	uint8_t u8_Timer_INT_Mode;
		} gstrTimerConfig_t;
			
/*****************************************************************************************************/
/*                                       TIMER FUNCTIONS' PROTOTYPES	                            */
/***************************************************************************************************/

extern uint8_t Timer_Init(gstrTimerConfig_t* pstrTimerConf);
extern uint8_t Timer_Start (uint8_t u8_TimerCh,uint16_t u16_CountNO);
extern uint8_t Timer_Stop(uint8_t u8_TimerCh);
extern uint8_t Timer_GetValue(uint8_t u8_TimerCh,uint16_t *pu16_TimerValue);
extern uint8_t Timer_SetValue(uint8_t TimerCh,uint16_t u16_TimerValue);
extern uint8_t Timer_GetStatus(uint8_t u8_TimerCh,uint8_t *pu8_TimerStatus);
#endif /* __TIMER_H__ */