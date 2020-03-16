/*
 * SOS-project.c
 *
 * Created: 10/03/2020 06:49:25 م
 * Author : TOSHIBA
 */ 

#include "Infrastructure\registers.h"
#include "MCAL\Sleep_Mood\sleep.h"
#include "Service/SOS/SOS.h"
#include "Service/SOS/SOS_PbCfg.h"

void toggle_1(void){
	PORTC_DATA^=0x0F;

}
void toggle_2(void){
	
	PORTC_DATA^=0xF0;
}
void toggle_3(void){
	PORTD_DATA^=0x0F;
}


int main(void)
{
	PORTA_DIR = 0xff;
	PORTB_DIR = 0xff;
	PORTC_DIR = 0xff;
	PORTD_DIR = 0xff;
	strSOS_CreatTask_t str_toggle_1={5,PERUDIC,1,toggle_1};
	strSOS_CreatTask_t str_toggle_2={5,PERUDIC,0,toggle_2};
	strSOS_CreatTask_t str_toggle_3={5,PERUDIC,2,toggle_3};
	 SOS_Init(&gstr_SOS_PbCfg);
	 SOS_Create_Task(&str_toggle_1);
	 SOS_Create_Task(&str_toggle_2);
	 SOS_Create_Task(&str_toggle_3);
	 SOS_Run();
	
}
