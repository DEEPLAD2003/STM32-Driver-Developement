#include "stm32f10x_I2C.h"
// API to get the peripheral Clock value.
uint8_t Peripherial[2]={1,2};
uint32_t RCC_GET_PERI_VAL(uint8_t peri){
	
	uint16_t 		AHB_PRE_SCLR[8]={2,4,8,16,32,54,128,512};
	uint16_t 		APB1PRE_SCLR[4]={2,4,8,16};
	uint16_t 		APB2PRE_SCLR[4]={2,4,8,16};

	uint8_t 		temp;
	uint8_t 		ahb_presclr;
	uint8_t     apb1_preclr;	
	uint8_t     apb2_preclr;	

	uint8_t  		clksrc;	
	uint32_t 		System_Clk;
	uint32_t	  apb1_pclk;
	uint32_t	  apb2_pclk;	
	
	//Clock multiplexer selector
	clksrc =((RCC->CFGR>>2)&0x3);
	if (clksrc==0){
		System_Clk=8000000;
	}
	else if (clksrc==1){
		System_Clk=8000000;
	}
	else if (clksrc==2){
		System_Clk=72000000;
	}
	
	//AHB 
	temp |= ((RCC->CFGR>>4)&0xF);
	if (temp>8){
		ahb_presclr=1;
	}
	else{
		ahb_presclr=AHB_PRE_SCLR[temp-8];
	}
	
	//APB1
	temp |= ((RCC->CFGR>>8)&0x4);
	if (temp>4){
		ahb_presclr=1;
	}
	else{
		apb1_preclr=APB1PRE_SCLR[temp-4];
	}
	
	//APB2
	temp |= ((RCC->CFGR>>11)&0x4);
	if (temp>4){
		ahb_presclr=1;
	}
	else{
		apb2_preclr=APB2PRE_SCLR[temp-4];
	}
	
	if(peri==1){
		apb1_pclk=System_Clk/ahb_presclr;
		apb1_pclk=apb1_pclk/apb1_preclr;
		return apb1_pclk;
	}
	else if(peri==2){
		apb2_pclk=System_Clk/ahb_presclr;
		apb2_pclk=apb1_pclk/apb2_preclr;
		return apb2_pclk;
	}
}


// API for enabling te I2C pheripheral 
void I2C_ENABLE_OR_DISABLE(I2C_TypeDef *pI2Cx,uint8_t EnorDi){
	if (EnorDi){
		pI2Cx->CR1|=(1<<I2C_PERI_ENABLE);
	}
	else{
		pI2Cx->CR1&=~(1<<I2C_PERI_ENABLE);
	}
}

// Peripheral Clock Enable or Disable API.
void I2C_PCLK_CRT(I2C_TypeDef *pI2Cx,uint8_t EnorDi){
	if (EnorDi){
		if(pI2Cx==I2C1){
			RCC->APB1ENR|=(1<<I2C1_PERI_CLK);
		}
		else if(pI2Cx==I2C2){
			RCC->APB1ENR|=(1<<I2C2_PERI_CLK);
		}
	}
	else{
		if(pI2Cx==I2C1){
			RCC->APB1ENR&=~(1<<I2C1_PERI_CLK);
		}
		else if(pI2Cx==I2C2){
			RCC->APB1ENR&=~(1<<I2C2_PERI_CLK);
		}
	}
}

// API for Iinitalising the I2C Pheripheral.
void I2C_Init(I2C_Handle_t *pI2CHandle){
	uint32_t tempreg =0;
	tempreg|=(pI2CHandle->I2C_Config.I2C_AckControl<<I2C_CR1_ACK);
}





// API for Deinitalising the I2C Pheripheral.
void I2C_Dinit(I2C_TypeDef *pI2Cx){
	if (pI2Cx==I2C1){
			RCC->APB2RSTR|=(1<<I2C1_PERI_RST);
			RCC->APB2RSTR&=~(1<<I2C1_PERI_RST);
		}
		else if(pI2Cx==I2C2){
			RCC->APB2RSTR|=(1<<I2C1_PERI_RST);
			RCC->APB2RSTR&=~(1<<I2C1_PERI_RST);
		}
}