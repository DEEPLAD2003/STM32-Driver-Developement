#include "stm32f10x_I2C.h"
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

// API for Deinitalising the I2C Pheripheral.





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