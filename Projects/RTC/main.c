#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"
#include "RTC_Config.h"
int main(void){
	RTC_Time time;
	RTC_Date date;
	
	/////// setting initial time /////////////
	time.seconds=45;
	time.minutes=59;
	time.hours=4;
	/////// setting initial date //////////
	date.day=31;
	date.month=12;
	date.year=2023;
	
	RTC_Init();
	while(1){
		RTC_GetTime(&time);
		RTC_GetDate(&date);
	}
}
