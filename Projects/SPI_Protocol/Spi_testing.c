#include "stm32f10x_GPIO.h"
#include "stm32f10x_SPI.h"
#include <string.h>
/*
*		MOSI --> PB5
*		MISO --> PB4
*		SCLK --> PB3
*		NSS  --> PA15
*/
void SPI1_GPIOInits(void);
void SPI1_GPIOInits(void){
	GPIO_Handle_t gpio_spi;
	gpio_spi.pGPIOx=GPIOB;
	gpio_spi.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	gpio_spi.GPIO_PinConfig.GPIO_Config=GPIO_CNF_AFPP;
	//MOSI
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=5;
	GPIO_Init(&gpio_spi);
	//MISO
	//gpio_spi.GPIO_PinConfig.GPIO_PinNumber=4;
	//GPIO_Init(&gpio_spi);
	//SCLK
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=3;
	GPIO_Init(&gpio_spi);
	//NSS
	//gpio_spi.pGPIOx=GPIOA;
	//gpio_spi.GPIO_PinConfig.GPIO_PinNumber=15;
	GPIO_Init(&gpio_spi);
}
int main(void ){
	//User data or buffer
	char data[]="Hello World";
	// Initializing the GPIO pin for SPI.
	SPI1_GPIOInits();
	// Configuringing the SPI pheripheral
	RCC->APB2ENR|=(1<<12);
	SPI1->CR1|=(2<3);
	SPI1->CR1|=(SPI_CPOL_LOW<1);
	SPI1->CR1|=(SPI_CPHA_LOW<0);
	SPI1->CR1|=(SPI_DFF_8BITS<11);
	SPI1->CR1|=(SPI_SSI_ENABLE<8);
	SPI1->CR1|=(SPI_SSM_ENABLE<9);
	SPI1->CR1|=(SPI_DEVICE_MODE_MASTER<2);
	SPI1->CR1|=(ENABLE<6);
	
	//Sending the Data
	SPI_SendData(SPI1,(uint8_t*)data,sizeof(data));
	//Disable the SPI Peripheral
	//SPI_ENABLE_OR_DISABLE(SPI1,DISABLE);
	while(1);
}