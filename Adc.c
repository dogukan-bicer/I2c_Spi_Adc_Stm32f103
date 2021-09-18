#include "stm32f10x.h"                  
/*
kurulum
PA0  -> Analog In
3.3v -> Pot
Gnd  -> Pot
SPI - 1
PA4 --> SS
PA5 --> SCLK
PA6 --> MISO
PA7 --> MOSI

*/
int analog;
void Delays(int time) /// Random delay function
{
	int t;
	for(;time>0;time--)
	{
	 for(t=0;t<2000;t++)
		{}
	}
}

int main(void)
{
	RCC->APB2ENR = 0x4; /// GPIOA CLOCK
  GPIOA->CRL = 0xFFFFFFF0; /// A3 pin reset
//////////////////////////////////////////////////////////////////////////////////ADC setup		  
	RCC->APB2ENR = 0x201;	 	//ADC1 clock on
  ADC1->CR2 = 0x3; //adc continuous
  ADC1->CR2 |= 0x4;// calibration	
  ADC1->CR2 |=1; //adc on	
//////////////////////////////////////////////////////////////////////////////////ADC setup	
	while(1)
	 {
    Delays(10);		
	  analog=ADC1->DR;
   }
}