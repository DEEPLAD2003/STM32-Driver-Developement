#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"
#include "PVD.h"
#include "RTC_Config.h"
void PVD_IRQHandler(void);
void PVD_IRQHandler(void){
	__WFI();
	EXTI->PR|=EXTI_PR_PR16;
}
extern uint32_t p_count;
extern uint32_t c_count;
RTC_Time *time;
int main(void){
	
	/*RCC->APB1ENR|=(RCC_APB1ENR_PWREN);
	SCB->SCR|=SCB_SCR_SLEEPONEXIT_Msk;
	PWR->CR|=PWR_CR_PDDS;
	PWR->CR|=PWR_CR_CWUF;
	PWR->CSR|=(PWR_CSR_EWUP);
	PVD_Enable(ENABLE,2.9);
	PVD_Interrupt_Config(ENABLE);*/
	RTC_Init();
	while(1){
		p_count=RTC->CNTL;
		RTC_GetTime(time,0xfffff);
	}
}
