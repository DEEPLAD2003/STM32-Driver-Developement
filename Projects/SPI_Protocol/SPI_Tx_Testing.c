#include "stm32f10x_GPIO.h"
#include "stm32f10x_SPI.h"
#include <string.h>
/*
*		MOSI --> PA7
*		MISO --> PA6
*		SCLK --> PA5
*		NSS  --> PA4
*/
void SPI1_GPIOInits(void){
	GPIO_Handle_t gpio_spi;
	gpio_spi.pGPIOx=GPIOA;
	gpio_spi.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	gpio_spi.GPIO_PinConfig.GPIO_Config=GPIO_CNF_AFPP;
	//MOSI
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=7;
	GPIO_Init(&gpio_spi);
	//MISO
	//gpio_spi.GPIO_PinConfig.GPIO_PinNumber=6;
	//GPIO_Init(&gpio_spi);
	//SCLK
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=5;
	GPIO_Init(&gpio_spi);
	//NSS
	//gpio_spi.GPIO_PinConfig.GPIO_PinNumber=4;
	//GPIO_Init(&gpio_spi);
	
}
void SPI1_Inits(void){
	SPI_Handle_t SPI1Handle;
	SPI1Handle.pSPIx=SPI1;
	SPI1Handle.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
	SPI1Handle.SPIConfig.SPI_BusConfig=SPI_BUS_CONFIG_FD;
	SPI1Handle.SPIConfig.SPI_SclkSpeed=SPI_CLK_SPEED_DIV256;
	SPI1Handle.SPIConfig.SPI_DFF=SPI_DFF_8BITS;
	SPI1Handle.SPIConfig.SPI_CPOL=SPI_CPOL_LOW;
	SPI1Handle.SPIConfig.SPI_CPHA=SPI_CPHA_LOW;
	SPI1Handle.SPIConfig.SPI_SSM=SPI_SSM_ENABLE;
	SPI_Init(&SPI1Handle);
}


int main(void){
	char data[]="Hello World";
	SPI1_GPIOInits();
	RCC->APB2ENR|=(1<<12);
	SPI1->CR1|=(1<<2);
	SPI1->CR1|=(1<<9);
	SPI1->CR1|=(1<<8);
	SPI1->CR1|=(0b111<<3);
	SPI1->CR1|=(1<<6);
	while(1){
		
	}
}
