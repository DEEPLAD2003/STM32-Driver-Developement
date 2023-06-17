#include "RTC_Config.h"
void RTC_Init(void){
	uint16_t presclr;
	RCC->APB1ENR|=RCC_APB1ENR_PWREN;
	RCC->APB1ENR|=RCC_APB1ENR_BKPEN;
	
	
	PWR->CR|=PWR_CR_DBP;
	
	
	RCC->CSR|=RCC_CSR_LSION;
	RCC->BDCR|=RCC_BDCR_LSEBYP;
	
	while (!RCC->CSR>>1);
	RCC->BDCR|=RCC_BDCR_RTCSEL_1;
	RCC->BDCR|=RCC_BDCR_RTCEN;
	
	while(!RTC->CRL>>RTC_CRL_RSF);
	RTC->CRH|=RTC_CRH_SECIE;
		
  
	RTC->CRL|=(1<<4);
	while(!RTC->CRL>>5);
	RTC->PRLL=0x7FFF;
	RTC->CRL&=~(1<<4);
	while(!RTC->CRL>>5);
	presclr=RTC->PRLL;


	
}
void RTC_GetTime(RTC_Time *time,uint32_t initial_count){
	uint16_t ctrl_val=RTC->CNTL;
	uint16_t ctrh_val=(RTC->CNTH & 0xF);
	uint32_t ctr_val= (ctrh_val<<16)+(ctrl_val)+initial_count;
	time->hours=ctr_val/0xE10;
	time->minutes=(ctr_val%0xE10)/0x3C;
	time->seconds=(ctr_val%0xE10)%0x3C;
}

uint32_t p_count=0;
uint32_t c_count=0;
void RTC_GetDate(RTC_Date *date){
	uint16_t ctrl_val=RTC->CNTL;
	uint16_t ctrh_val=(RTC->CNTH & 0xF);
	uint32_t ctr_val= (ctrh_val<<16)+(ctrl_val);
	uint32_t days=ctr_val/86400; 
	uint32_t c_days=0;
	uint32_t p_days=0;
	uint32_t count=p_days-c_days;
	
}

void RTC_SetAlarm(uint8_t hour,uint8_t minutes,uint8_t seconds){
	uint16_t alarm;
	uint16_t counter=(hour*3600)+(minutes*60)+seconds;
	RTC->CRH|=(1<<1);
	RTC->CRL|=(1<<4);
	while(!RTC->CRL>>5);
	RTC->ALRL=counter;
	RTC->CRL&=~(1<<4);
	while(!RTC->CRL>>5);
	alarm=RTC->ALRL;

}
uint8_t Leap_Year(uint8_t year){
	if (year%400)
		return 1;
	else{
		if(year%100)
				return 0;
		else{
			if(year%4)
					return 1;
			else 
				return 0;
		}
	}
}




	