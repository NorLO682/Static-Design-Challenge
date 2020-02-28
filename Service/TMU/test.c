/*
 * test.c
 *
 * Created: 24/02/2020 03:03:38 م
 *  Author: TOSHIBA
 */ 
#include "TMU.h"
#include "TMU_PbCfg.h"
//#include "../../MCAL/Timer/Timer.h"

void toggle_A(void){
	PORTA_DATA^=0xff;

}
void toggle_D(void){
	
	PORTD_DATA^=0xff;
}
void toggle_C(void){
	PORTC_DATA^=0xff;
}

void Test_Case_One(void)
{   PORTA_DIR=0xff;
	PORTB_DIR=0xff;
	PORTC_DIR=0xff;
	PORTD_DIR=0xff;
	PORTA_DATA=0xF0;
	PORTC_DATA=0xf0;
	PORTD_DATA=0xf0;
	PORTB_DATA=0x00;
	TMU_Init(&gstr_TMU_PbCfg);
	
	TMU_Start_Timer(6,PERUDIC,0,toggle_D);
	TMU_Start_Timer(4, PERUDIC,1,toggle_C);
	 if(TMU_Start_Timer(4, PERUDIC,2,toggle_A) ==( MODULE_ERROR_NUMBER +ERROR_FULL_BUFFER))
	 {
		 PORTB_DATA|=0x01;
	 }
	while (1)
	{
		TMU_Dispatcher();
	
	
	}
}
	
	
void Test_Case_Two(void)
{ PORTB_DIR = 0xFF;
	TMU_Init(&gstr_TMU_PbCfg);
	while (1)
	{
		if(TMU_Dispatcher() ==E_OK)
		{
			PORTB_DATA |= 0x01;
		}
			
			
	}
	
}

void Test_Case_Three(void)
{  PORTA_DIR=0xff;
	PORTB_DIR=0xff;
	PORTC_DIR=0xff;
	PORTD_DIR=0xff;
	PORTA_DATA=0xF0;
	PORTC_DATA=0xf0;
	PORTD_DATA=0xf0;
	PORTB_DATA=0x00;
	TMU_Init(&gstr_TMU_PbCfg);
	
	TMU_Start_Timer(6,PERUDIC,0,toggle_D);
	TMU_Start_Timer(6,PERUDIC,1,toggle_C);
	TMU_Stop_Timer(0);
	
	if( TMU_Stop_Timer(0) ==( MODULE_ERROR_NUMBER+ERROR_ELEMENT_NOT_EXIST))
	{
		PORTB_DATA|=0x01;
	}
	while (1)
	{
		TMU_Dispatcher();
		
		
	}
}

void Test_Case_Four(void)
{ 
	PORTB_DIR = 0xFF;
	TMU_Init(&gstr_TMU_PbCfg);
   
	
	if(TMU_Stop_Timer(0)==(MODULE_ERROR_NUMBER + ERROR_EMPTY_BUFFER))
	{
		PORTB_DATA |= 0x01;
	}
	while (1)
	{
		TMU_Dispatcher();	
	}
	
}

int main (){
	//Test_Case_One();
 	//Test_Case_Two();
	//Test_Case_Three();
	Test_Case_Four();

	return 0;
}
