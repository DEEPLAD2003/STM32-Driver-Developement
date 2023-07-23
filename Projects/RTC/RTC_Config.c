#include "RTC_Config.h"

p_sec=0;   //((RTC->CNTH<<16)+(RTC->CNTL));
uint32_t c_sec=0;

static uint32_t p_days=0;//((RTC->CNTH<<16)+(RTC->CNTL))/86400;
uint32_t c_days=0;

void RTC_Init(void){
	RCC->APB1ENR|=RCC_APB1ENR_PWREN;
	RCC->APB1ENR|=RCC_APB1ENR_BKPEN;
	
	PWR->CR|=PWR_CR_DBP;
	
	RCC->BDCR&=~RCC_BDCR_BDRST;
	RCC->BDCR|=RCC_BDCR_LSEON;
	while (!(RCC->BDCR && RCC_BDCR_LSERDY));
	RCC->BDCR|=RCC_BDCR_RTCSEL_LSE;
	
	RCC->BDCR|=RCC_BDCR_RTCEN;
	
	while(!(RTC->CRL && RTC_CRL_RSF));
	while(!(RTC->CRL && RTC_CRL_RTOFF));
	RTC->CRL|=RTC_CRL_CNF;
	RTC->CRH|=RTC_CRH_SECIE;
	RTC->PRLL=0x7FFF;
	RTC->CRL&=~RTC_CRL_CNF;
}


void RTC_GetTime(RTC_Time *time){
	uint16_t counter_low=RTC->CNTL;
	uint16_t counter_high=RTC->CNTH;
	uint32_t counter=(counter_high<<16)+counter_low;
	c_sec=counter;
	uint32_t sec=c_sec-p_sec;
	if( (time->seconds+sec)>=60){
		if(time->minutes>=60){
			if(time->hours>=23){
				time->hours=0;
				time->minutes=0;
				time->seconds=0;
				p_sec=c_sec;
			}
			else{
				time->hours++;
				time->minutes=0;
				time->seconds=0;
				p_sec=c_sec;
			}
		}
		else if((time->minutes)<60){
			time->minutes++;
			time->seconds=0;
			 p_sec=c_sec;
		}
	}
	else if(time->seconds<60){
		time->seconds+=sec;
		p_sec=c_sec;
	}
	
	
	/*
	time->hours=ctr_val/0xE10;
	time->minutes=(ctr_val%0xE10)/0x3C;
	time->seconds=(ctr_val%0xE10)%0x3C;*/
}


void RTC_GetDate(RTC_Date *date){
	uint16_t counter_low=RTC->CNTL;
	uint16_t counter_high=RTC->CNTH;
	uint32_t counter=(counter_high<<16)+counter_low;
	c_days=counter/86400;
	uint32_t days=c_days-p_days;
	/////////////// IF MONTH IS OF 31 DAYS ///////////////////////////
	if ( (date->month%2 & date->month<=7) || (~date->month%2 & date->month>7) & (date->month!=2) ){
		if((date->day+c_days)==31){
			if(date->month==12){
				date->year++;
				date->month=1;
				date->day=1;
				p_days=c_days;
			}
			else{
				date->day+=days;
				p_days=c_days;
			}
		}
		else if((date->day+days)<31){
			date->day+=days;
			p_days=c_days;
		}
	}
	/////////////// IF MONTH IS OF 30 DAYS ////////////////////////////
	else if(date->month!=2){
		if((date->day+days)==30){
			date->month++;
			date->day=1;
			p_days=c_days;
		}
		else if((date->day+days)<30){
			date->day+=days;
			p_days=c_days;
		}
	}
	//////////////// IF MONTH IS FEBRUARY /////////////////////////////
	else{
		if(Leap_Year(date->year)){
			if((date->day+days)==29){
				date->month++;
				date->day=1;
				p_days=c_days;
			}
			else if(date->day+days){
				date->day+=days;
				p_days=c_days;
			}
		}
		else{
			if((date->day+days)){
				date->month++;
				date->day=1;
				p_days=c_days;
			}
			else{
				date->day+=days;
				p_days=c_days;
			}
		}
	}
}

uint8_t Leap_Year(uint32_t year){
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


void Enable_Alarm(void){
	//Polling RTOFF bit in CRL register
	while(!(RTC->CRL & RTC_CRL_RTOFF));
	
	//Settiing the CNF bit to configure one or more register.
	RTC->CRL|=RTC_CRL_CNF;
	
	// Enabling the Interrupt for the alarm.
	RTC->CRH|=RTC_CRH_ALRIE;
	
	// Clearing the the CNF bit 
	RTC->CRL&=~RTC_CRL_CNF;
}
void Disable_Alarm(void)
{
	//Polling RTOFF bit in CRL register
	while(!(RTC->CRL & RTC_CRL_RTOFF));
	
	//Settiing the CNF bit to configure one or more register.
	RTC->CRL|=RTC_CRL_CNF;
	
	// Disabling the Interrupt for the alarm.
	RTC->CRH&=~RTC_CRH_ALRIE;
	
	// Clearing the the CNF bit 
	RTC->CRL&=~RTC_CRL_CNF;
	
	while(!(RTC->CRL & RTC_CRL_RTOFF));
}

void RTC_SetAlarm(uint8_t hour,uint8_t minutes,uint8_t seconds){
	uint32_t alarm_count=(hour*3600)+(minutes*60)+seconds;
	uint32_t actual_count=((uint32_t)RTC->CNTH<<16)+(uint32_t)(RTC->CNTL);
	alarm_count+=actual_count;
	while(!(RTC->CRL & RTC_CRL_RTOFF));
	RTC->CRL|=RTC_CRL_CNF;
	RTC->ALRH=(uint16_t)(alarm_count>>16 & 0xFFFF);
	RTC->ALRL=(uint16_t)(alarm_count & 0xFFFF);
	RTC->CRL&=~RTC_CRL_CNF;
}

void RTC_AlarmInterrupt(uint8_t EnorDi){
	EXTI->IMR|=EXTI_IMR_MR17;
	EXTI->FTSR|=EXTI_FTSR_TR17;
	if (EnorDi==ENABLE){
		NVIC_EnableIRQ(41);
	}
	if (EnorDi==DISABLE){
		NVIC_DisableIRQ(41);
	}
}


	