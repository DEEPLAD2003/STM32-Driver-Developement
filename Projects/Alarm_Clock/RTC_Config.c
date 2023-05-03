#include "RTC_Config.h"

void RTC_Init(void){
	RCC->APB1ENR|=RCC_APB1ENR_PWREN;
	RCC->APB1ENR|=RCC_APB1ENR_BKPEN;
	
	PWR->CR|=PWR_CR_DBP;
	
	RCC->CSR|=RCC_CSR_LSION;
	while (!RCC->CSR>>1);
	
	RCC->BDCR|=0x8200;
	while(!RTC->CRL>>RTC_CRL_RSF);
	
	while(!RTC->CRL>>5);
	
	/*Setting global interrupt for seconds*/
	RTC->CRH|=RTC_CRH_SECIE;
		
	while(!RTC->CRL>>5);
	RTC->CNTL=0x0ABCD;
	RTC->PRLL=0x7FFF;
}
void RTC_GetTime(RTC_Time *time){
	uint16_t ctrl_val=RTC->CNTL;
	uint16_t ctrh_val=(RTC->CNTH & 0xf);
	uint32_t ctr_val= (ctrh_val<<16)+(ctrl_val);
	time->hours=ctr_val/0xE10;
	time->minutes=(ctr_val%0xE10)/0x3C;
	time->seconds=ctr_val%0x3C;
}

	