#include "stm32f103xx_GPIO.h"
#include "stdint.h"
/*
	******************************    API's Used     ******************************************
		1. 		GPIO_PCLK_CNF(GPIOx, Enable/Disable)
		2. 		GPIO_Init( &GPIO_Handler )
		3. 		GPIO_Dinit( $GPIO_Handler )
		4. 		GPIO_Write_Pin( GPIOx, SET/RESET )
		5. 		GPIO_Toggle_Pin( GPIOx,SET/RESET )
		6. 		GPIO_Read_Pin( GPIOx )
		7. 		GPIO_Locking()
		8. 		GPIO_IRQ_Interrupt_Config( GPIOx, Enable/Disable )
		9. 		GPIO_IRQ_Interrupt_Priority( IRQ_Number, Priority )
		10. 	GPIO_IRQ_Interrupt_Handglin( Pin_Number )    
	*******************************************************************************************

	**********************  Steps for using GPIO pins as INPUT/OUTPUT  ************************
		1. Configuring the respective GPIO Port(A,B,C,D) Periheral Clock.
		2. Select the GPIO Port. 
		3. Select the Pin Number.
		4. Select the Mode : Input or Output (With Speed).
		5. Select the Configuration (GP -> Push Pull/Open Drain, AltFn -> Push Pull/Open Drain).
		6. Call the Iinit Function (for applying the changes).		
	*******************************************************************************************
*/

void GPIO_PCLK_CNF(GPIO_TypeDef* GPIOx, uint8_t State){
	if (State){
		if (GPIOx==GPIOA){
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		}
		else if (GPIOx==GPIOB){
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		}
		else if (GPIOx==GPIOC){
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		}
		else if (GPIOx==GPIOD){
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
		}
		else if (GPIOx==GPIOE){
			RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
		}
	}
	else if(!State){
		if (GPIOx==GPIOA){
			RCC->APB2ENR &= ~RCC_APB2ENR_IOPAEN;
		}
		else if (GPIOx==GPIOB){
			RCC->APB2ENR &= ~RCC_APB2ENR_IOPBEN;
		}
		else if (GPIOx==GPIOC){
			RCC->APB2ENR &= ~RCC_APB2ENR_IOPCEN;
		}
		else if (GPIOx==GPIOD){
			RCC->APB2ENR &= ~RCC_APB2ENR_IOPDEN;
		}
		else if (GPIOx==GPIOE){
			RCC->APB2ENR &= ~RCC_APB2ENR_IOPEEN;
		}
	}
}

void GPIO_Init(GPIO_Handle_t gpiox){
	GPIO_PCLK_CNF(gpiox.GPIOx,ENABLE);
	if(gpiox.Pin_Config.Pin_Number<=7){																/* Configurning the GPIO CRL Register (Pins:0-7) */
		uint8_t temp=gpiox.Pin_Config.Config & 0x0F;
		/* Clearning the Bits. */
		gpiox.GPIOx->CRH&=~((uint32_t)(0xF<<gpiox.Pin_Config.Pin_Number*4));
		/* Setting the Required bits according to the configuration.  */
		gpiox.GPIOx->CRL|=(uint32_t)(gpiox.Pin_Config.Mode<<gpiox.Pin_Config.Pin_Number*4);
		if (gpiox.Pin_Config.Mode==0 && (temp<=0x02)){ /* Protecting to go into the Reserved State.*/
			gpiox.GPIOx->CRL|=(uint32_t)(temp<<(gpiox.Pin_Config.Pin_Number*4+2));
			if (gpiox.Pin_Config.Config==GPIO_CNF_IN_PU)                 /* Pulling up GPIO(INPUT_PULLUP) */
				gpiox.GPIOx->BSRR=(uint32_t)(1<<gpiox.Pin_Config.Pin_Number);
			else if(gpiox.Pin_Config.Config==GPIO_CNF_IN_PD)             /* Pulling down GPIO(INPUT_PULLDOWN) */
				gpiox.GPIOx->BRR=(uint32_t)(1<<gpiox.Pin_Config.Pin_Number);
		}
		else if (gpiox.Pin_Config.Mode<=0x3 && gpiox.Pin_Config.Config<=0x3){ 
			gpiox.GPIOx->CRL|=(uint32_t)(gpiox.Pin_Config.Config<<(gpiox.Pin_Config.Pin_Number*4+2));
		}
	}
	else if(gpiox.Pin_Config.Pin_Number>7 && gpiox.Pin_Config.Pin_Number<=15){ /* Configurning the GPIO CRH Register (Pins:8-15) */
		uint8_t temp_pin=gpiox.Pin_Config.Pin_Number-8;
		uint8_t temp=gpiox.Pin_Config.Config & 0x0F;
		/* Clearning the Bits. */
		gpiox.GPIOx->CRH&=~((uint32_t)(0xF<<temp_pin*4));
		/* Setting the Required bits according to the configuration.  */
		gpiox.GPIOx->CRH|=(uint32_t)(gpiox.Pin_Config.Mode<<temp_pin*4);
		if (gpiox.Pin_Config.Mode==0 && (temp <=0x02)){ /* Protecting to go into the Reserved State.*/
			gpiox.GPIOx->CRH|=(uint32_t)(temp<<(temp_pin*4+2));
			if (gpiox.Pin_Config.Config==GPIO_CNF_IN_PU)                 /* Pulling up GPIO(INPUT_PULLUP) */
				gpiox.GPIOx->BSRR=(uint32_t)(1<<gpiox.Pin_Config.Pin_Number);
			else if(gpiox.Pin_Config.Config==GPIO_CNF_IN_PD)             /* Pulling down GPIO(INPUT_PULLDOWN) */
				gpiox.GPIOx->BRR=(uint32_t)(1<<gpiox.Pin_Config.Pin_Number);
		}
		else if(gpiox.Pin_Config.Mode<=0x3 && gpiox.Pin_Config.Config<=0x3){ 
			gpiox.GPIOx->CRL|=(uint32_t)(gpiox.Pin_Config.Config<<(temp_pin*4+2));
		}
	}
}
 

void GPIO_Deinit(GPIO_Handle_t gpiox){
	if (gpiox.Pin_Config.Pin_Number<7){
		gpiox.GPIOx->CRH&=~((uint32_t)(0xF<<gpiox.Pin_Config.Pin_Number*4));
		gpiox.GPIOx->CRH|=((uint32_t)(0x4<<gpiox.Pin_Config.Pin_Number*4));
	}
	else if(gpiox.Pin_Config.Pin_Number>=7 && gpiox.Pin_Config.Pin_Number<=15){
		uint8_t temp_pin=gpiox.Pin_Config.Pin_Number-8;
		gpiox.GPIOx->CRH&=~((uint32_t)(0xF<<temp_pin*4));
		gpiox.GPIOx->CRH|=((uint32_t)(0x4<<temp_pin*4));
	}
	GPIO_PCLK_CNF(gpiox.GPIOx,DISABLE);
}
void GPIO_Write_Pin(GPIO_TypeDef* GPIOx,uint8_t Pin_Number,uint8_t State){
	if (State==ENABLE){
		GPIOx->BSRR=(uint32_t)(1<<Pin_Number);
	}
	else if(State==DISABLE){
		GPIOx->BRR|=(uint32_t)(1<<Pin_Number);
	}
}
uint8_t GPIO_Read_Pin(GPIO_TypeDef* GPIOx,uint8_t Pin_Number){
	uint16_t input_val=((uint16_t)GPIOx->IDR>>Pin_Number);
	if(input_val){
		return 1;
	}
	else{
		return 0;
	}
}
void Delay(void){
	uint32_t i=0;
	for (i=0;i<=1000000;i++);
}
