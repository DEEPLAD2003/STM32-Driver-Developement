#include "stm32f10x_SPI.h"
#include "stm32f10x_GPIO.h"
/*
*	Enabling/Disabling SPI Peripheral.
*/
void SPI_EN_DIS(SPI_TypeDef *pSPIx,uint8_t EnorDi){
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
			RCC->APB2ENR|=RCC_APB2ENR_SPI1EN;
		}
		else if (pSPIx==SPI2){
			RCC->APB1ENR|=RCC_APB1ENR_SPI2EN;
		}
	}
	else if (EnorDi==DISABLE){
		if (pSPIx==SPI1){
			RCC->APB2ENR&=~RCC_APB2ENR_SPI1EN;
		}
		else if (pSPIx==SPI2){
			RCC->APB1ENR&=~RCC_APB1ENR_SPI2EN;
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
	//1. Clock Speed Selection (Baud rate)
	pSPIHandle->pSPIx->CR1|=(pSPIHandle->SPIConfig.SPI_SclkSpeed<<3);
	
	//2. Clock Phase and Ploarity
	if (pSPIHandle->SPIConfig.SPI_CPHA && pSPIHandle->SPIConfig.SPI_CPOL){
		pSPIHandle->pSPIx->CR1|=SPI_CR1_CPHA;
		pSPIHandle->pSPIx->CR1|=SPI_CR1_CPOL;
	}
	else if (!pSPIHandle->SPIConfig.SPI_CPHA && pSPIHandle->SPIConfig.SPI_CPOL){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_CPHA;
		pSPIHandle->pSPIx->CR1|=SPI_CR1_CPOL;
	}
	else if (pSPIHandle->SPIConfig.SPI_CPHA && !pSPIHandle->SPIConfig.SPI_CPOL){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_CPHA;
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_CPOL;
	}
	else if (!pSPIHandle->SPIConfig.SPI_CPHA && !pSPIHandle->SPIConfig.SPI_CPOL){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_CPHA;
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_CPOL;
	}
	
	//  3. Data frame format (8 bit or 16 bit) 
	if (pSPIHandle->SPIConfig.SPI_DFF){
		pSPIHandle->pSPIx->CR1|=SPI_CR1_DFF;
	}
	else if(~pSPIHandle->SPIConfig.SPI_DFF){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_DFF;
	}
	
	//  4. Data Transmission format (MSB or LSB First)
	if (pSPIHandle->SPIConfig.SPI_Transmission_Format){
		pSPIHandle->pSPIx->CR1|=SPI_CR1_LSBFIRST;
	}
	if (!pSPIHandle->SPIConfig.SPI_Transmission_Format){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_LSBFIRST;
	}
	
	//  5. Slave Management (Hardware or Software) and Multimaster Capability
	if (pSPIHandle->SPIConfig.SPI_SSM){
		pSPIHandle->pSPIx->CR1|=SPI_CR1_SSM;
		pSPIHandle->pSPIx->CR1|=SPI_CR1_SSI;
	}
	else if (!pSPIHandle->SPIConfig.SPI_SSM && pSPIHandle->SPIConfig.SPI_MultiMaster){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_SSM;
		pSPIHandle->pSPIx->CR1|=SPI_CR2_SSOE;
	}
	else if (!pSPIHandle->SPIConfig.SPI_SSM && !pSPIHandle->SPIConfig.SPI_MultiMaster){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_SSM;
		pSPIHandle->pSPIx->CR1&=~SPI_CR2_SSOE;
	}
	
	//  6. Bus Configuration (Full Duplex or Half Duplex)
	if (pSPIHandle->SPIConfig.SPI_BusConfig==1 && pSPIHandle->SPIConfig.SPI_BusConfig==4){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_BIDIMODE;
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_RXONLY;
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig==2){
		pSPIHandle->pSPIx->CR1|=SPI_CR1_BIDIMODE;
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig==3){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_BIDIMODE;
		pSPIHandle->pSPIx->CR1|=SPI_CR1_RXONLY;
	}
	
	//  7. Device Mode (Master or Slave)
	if (pSPIHandle->SPIConfig.SPI_DeviceMode){
		pSPIHandle->pSPIx->CR1|=SPI_CR1_MSTR;
	}
	else if(!pSPIHandle->SPIConfig.SPI_DeviceMode){
		pSPIHandle->pSPIx->CR1&=~SPI_CR1_MSTR;
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
*		Data send and Recieve (This is a Blocking Call)
*/
void SPI_SendData(SPI_Handle_t *pspihandle,uint8_t *pTxBuffer,uint32_t Len){
	uint16_t RxBuffer,buffer;
	uint16_t buffer1,buffer2;
	if(Len%2!=0 && pspihandle->SPIConfig.SPI_DFF==SPI_DFF_16BITS){
			Len++;
	}
	while(!(pspihandle->pSPIx->SR & (SPI_SR_TXE)));
	if(pspihandle->pSPIx->CR1 & (SPI_CR1_DFF)){
		buffer1=*pTxBuffer;
		pTxBuffer++;
		buffer2=*pTxBuffer;
		buffer=(buffer1<<8)+buffer2;
		pspihandle->pSPIx->DR|=buffer;
		pTxBuffer+=1;
		Len-=2;
	}
	else if(!(pspihandle->pSPIx->CR1 & SPI_CR1_DFF)){
		pspihandle->pSPIx->DR|=*pTxBuffer;
		pTxBuffer++;
		Len--;
	}	
	while(Len>0){
		while(!(pspihandle->pSPIx->SR & (SPI_SR_TXE)));
		if(pspihandle->pSPIx->CR1 & SPI_CR1_DFF){
			//16 bit DFF
			buffer1=*pTxBuffer;
			pTxBuffer++;
			buffer2=*pTxBuffer;
			buffer=(buffer1<<8)+buffer2;
			pspihandle->pSPIx->DR|=buffer;
			pTxBuffer+=1;
			Len-=2;
			if (pspihandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_TXONLY){
				while(!pspihandle->pSPIx->SR>>(SPI_SR_RXNE));
				RxBuffer=pspihandle->pSPIx->SR;
			}
		}
		else if(!(pspihandle->pSPIx->CR1 & SPI_CR1_DFF)){
			pspihandle->pSPIx->DR|=*pTxBuffer;
			pTxBuffer++;
			Len--;
			if (pspihandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_TXONLY){
				while(!pspihandle->pSPIx->SR>>(SPI_SR_RXNE));
				RxBuffer=pspihandle->pSPIx->SR;
			}
		}
		if (pspihandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_TXONLY){
				while(!pspihandle->pSPIx->SR>>(SPI_SR_RXNE));
				RxBuffer=pspihandle->pSPIx->SR;
		}
	}
	while(pspihandle->pSPIx->SR & SPI_SR_BSY);
}


void SPI_ReadData(SPI_TypeDef *pSPIx,uint8_t *pRxBuffer,uint32_t Len);

/*
*		IRQ Configuration and ISR Handling.
*/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_Handling(SPI_TypeDef *pHandle);