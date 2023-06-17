#include "PVD.h"

void PVD_Enable(uint8_t status,float threshold){
	RCC->APB1ENR|=RCC_APB1ENR_PWREN;
	/////Enable or Disable the PVD//////
	if (status==ENABLE){
		PWR->CR|=PWR_CR_PVDE;
	}
	else if(status==DISABLE){
		PWR->CR&=(~PWR_CR_PVDE);
	}
	/////////Setting the Threshold value//////////////
	if (threshold==2.2){
		PWR->CR|=PWR_CR_PLS_2V2;
	}
	else if(threshold==2.3){
		PWR->CR|=PWR_CR_PLS_2V3;
	}
	else if(threshold==2.4){
		PWR->CR|=PWR_CR_PLS_2V4;
	}
	else if(threshold==2.5){
		PWR->CR|=PWR_CR_PLS_2V5;
	}
	else if(threshold==2.6){
		PWR->CR|=PWR_CR_PLS_2V6;
	}
	else if(threshold==2.7){
		PWR->CR|=PWR_CR_PLS_2V7;
	}
	else if(threshold==2.8){
		PWR->CR|=PWR_CR_PLS_2V8;
	}
	else if(threshold==2.9){
		PWR->CR|=PWR_CR_PLS_2V9;
	}
}

void PVD_Interrupt_Config(uint8_t status){
	EXTI->IMR|=EXTI_IMR_MR16;
	EXTI->RTSR|=EXTI_RTSR_TR16;
	EXTI->FTSR|=EXTI_FTSR_TR16;
	
	////////Enabling IRQ ///////////
	if (status==ENABLE) 
		NVIC_EnableIRQ(PVD_IRQn);
	if (status==DISABLE)
		NVIC_EnableIRQ(PVD_IRQn);
}
