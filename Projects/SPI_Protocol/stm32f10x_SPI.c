#include "stm32f10x_SPI.h"

/*
*	Enabling/Disabling SPI Peripheral.
*/
void SPI_ENABLE_OR_DISABLE(SPI_TypeDef *pSPIx,uint8_t EnorDi){
	if (EnorDi==ENABLE){
		pSPIx->CR1|=(1<<6);
	}
	else if(EnorDi==DISABLE){
		pSPIx->CR1&=~(1<<6);
	}
}


/*
*		Peripheral clock Setup.
*/
void SPI_PCLK_CRT(SPI_TypeDef *pSPIx,uint8_t EnorDi){
	if (EnorDi==ENABLE){
		if (pSPIx==SPI1){
			RCC->APB2ENR|=(1<<12);
		}
		else if (pSPIx==SPI2){
			RCC->APB1ENR|=(1<<14);
		}
		else if (pSPIx==SPI3){
			RCC->APB1ENR|=(1<<15);
		}
	}
	else if (EnorDi==DISABLE){
		if (pSPIx==SPI1){
			RCC->APB2ENR&=~(1<<12);
		}
		else if (pSPIx==SPI2){
			RCC->APB1ENR&=~(1<<14);
		}
		else if (pSPIx==SPI3){
			RCC->APB1ENR&=~(1<<15);
		}
	}
}

/*
*		Initializing SPI peripheral
*/
void SPI_Init(SPI_Handle_t *pSPIHandle){
	//Enabling the Clock for the Peripheral
	SPI_PCLK_CRT(pSPIHandle->pSPIx,ENABLE);
	
	//Configuring SPI_CR1 register.
	//1. Device Mode
	if (pSPIHandle->SPIConfig.SPI_DeviceMode==SPI_DEVICE_MODE_MASTER){
		pSPIHandle->pSPIx->CR1|=(1<<2);
	}
	else if (pSPIHandle->SPIConfig.SPI_DeviceMode==SPI_DEVICE_MODE_SLAVE){
		pSPIHandle->pSPIx->CR1&=~(1<<2);
	}
	
	//2. BUS Configuration
	if (pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_FD){
		pSPIHandle->pSPIx->CR1&=~(1<<15);
		
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_HD){
		pSPIHandle->pSPIx->CR1|=(1<<15);
	}
	/*else if (pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_RXONLY){
		pSPIHandle->pSPIx->CR1|=(1<<15);
		pSPIHandle->pSPIx->CR1&=~(1<<10);
	}*/
	//3. Clock Configuration
	pSPIHandle->pSPIx->CR1|=(pSPIHandle->SPIConfig.SPI_SclkSpeed<<3);
	
	//4. DFF Configuration
	pSPIHandle->pSPIx->CR1|=(pSPIHandle->SPIConfig.SPI_DFF<<11);
	
	//5. CPOL Configuration
	pSPIHandle->pSPIx->CR1|=(pSPIHandle->SPIConfig.SPI_CPOL<<1);
	
	//6. CPHA Configuration
	pSPIHandle->pSPIx->CR1|=(pSPIHandle->SPIConfig.SPI_CPHA<<0);
	
	//7 SSM Configuration.
	if (pSPIHandle->SPIConfig.SPI_SSM==ENABLE){
		pSPIHandle->pSPIx->CR1|=(1<<9);
	}
	else if (pSPIHandle->SPIConfig.SPI_SSM==DISABLE){
		pSPIHandle->pSPIx->CR1&=~(1<<9);
	}
}

/*
*		Deinitalizing SPI peripheral
*/
void SPI_Dinit(SPI_TypeDef *pSPIx){
		if (pSPIx==SPI1){
			RCC->APB2RSTR|=(1<<12);
			RCC->APB2RSTR&=~(1<<12);
		}
		else if(pSPIx==SPI2){
			RCC->APB1RSTR|=(1<<14);
			RCC->APB1RSTR&=~(1<<14);
		}
		else if(pSPIx==SPI3){
			RCC->APB1RSTR|=(1<<15);
			RCC->APB1RSTR&=~(1<<15);
		}
}	

/*
*		Data send and Recieve
*/
// Thi is a Blocking Call.
void SPI_SendData(SPI_TypeDef *pSPIx,uint8_t *pTxBuffer,uint32_t Len){  
	while(Len>0){
		// Waiting for Tx Buffer to clear
		while(!(pSPIx->SR & (1<<1)));
		if (pSPIx->CR1 & (1<<11)){
			// 16 bit data
			// Load data to Data register
			pSPIx->DR	|= *((uint16_t*)pTxBuffer);
			Len-=2;
			(uint16_t*)pTxBuffer++;
		}
		else{
			// 8 bit data
			// Load data to Data register
			pSPIx->DR |= *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}


/*
*	SSI Configuration
*/
void SPI_SSI_Config(SPI_TypeDef *pSPIx,uint8_t EnorDi){
	if (EnorDi==ENABLE){
		pSPIx->CR1|=(1<<8);
	}
	else if(EnorDi==DISABLE){
		pSPIx->CR1&=~(1<<8);
	}
}

void SPI_ReadData(SPI_TypeDef *pSPIx,uint8_t *pRxBuffer,uint32_t Len);

/*
*		IRQ Configuration and ISR Handling.
*/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_Handling(SPI_TypeDef *pHandle);