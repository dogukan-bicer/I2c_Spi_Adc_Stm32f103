#include "stm32f10x.h" 
#include "systick_time.h"
//#include "gp_drive.h" 

/*
Actual setup

SPI - 1
--> 
PA4 --> SS
PA5 --> SCLK
PA6 --> MISO
PA7 --> MOSI

*/

int main(void)
{
systick_init();
// Activate SPI-1 peripheral / AFIO function
RCC->APB2ENR |= 5; //Enable AFIO function 0x4 +0x1
RCC->APB2ENR |= 0x1000; // Enabling the SPI-1 periph
GPIOA->CRL = 0x98930000; /// A7,A5 pin push pull	output
//*******Setup SPI peripherals*****
SPI1->CR1 |= 0x4; // Master Mode
SPI1->CR1 |= 0x31; // fclk / 265
SPI1->CR2 |= 0x4;
SPI1->CR1 |= 0x40; // Enabling SPI SPI periph
GPIOA->ODR =0x000;	

	while(1)
	{
		//Sending some data
		DelayUs(50000);
		GPIOA->ODR =0x000;
		DelayUs(1);
		SPI1->DR = 0x55;
		while(SPI1->SR & 0x80){}
		GPIOA->ODR =0x010;
		GPIOA->ODR =0x000;
                DelayUs(1);
		SPI1->DR = 0x25;//spi data
		while(SPI1->SR & 0x80){}
		GPIOA->ODR =0x010;
		GPIOA->ODR =0x000;
		DelayUs(1);
		SPI1->DR = 0x35;//spi data
		while(SPI1->SR & 0x80){}
		GPIOA->ODR =0x010;
		GPIOA->ODR =0x000;
		DelayUs(1);
		SPI1->DR = 0xAA;//spi data
		while(SPI1->SR & 0x80){}
		GPIOA->ODR =0x010;
		
	}
	
}
