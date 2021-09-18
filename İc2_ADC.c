#include "stm32f10x.h"
#define RCC_APBENR       (*((volatile unsigned long *) 0x40021018))
	
char data[2] = {0x12,0x56};
int  analog;
char adc_data[4];
int  tmp;

void DelayMs(unsigned long t)
{
	for(;t>0;t--)
		{

	SysTick->LOAD = 0x11940;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);

		}
}


int main(void)
{
	
	 	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	
	  //i2c_init(2,i2c_SM);
		RCC->APB1ENR |= 0x400000;
		// Pin enable 
  //init_GP(PB,10,OUT50,O_AF_OD);
	  RCC_APBENR |= 0x8;
	  GPIOB->CRH |=0x0F00;
	
  //init_GP(PB,11,OUT50,O_AF_OD);
    GPIOB->CRH |=0xF000;
	
		I2C2->CR1 |= 0x8000;
		I2C2->CR1 &= ~0x8000;
		I2C2->CR2 =0x8;
		I2C2->CCR =0xB4 ;
		I2C2->TRISE = 0x9;
		I2C2->CR1 |= 1;
	
	
	
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
		analog=ADC1->DR/16;

			I2C2->CR1 |= 0x100;
		  while (!(I2C2->SR1 & 1)){};
			
			I2C2->DR = (0x78|0);//sd1306 oled address
		  while((I2C2->SR1 & 2)==0){};
		  while((I2C2->SR1 & 2)){
			tmp = I2C2->SR1;
			tmp = I2C2->SR2;
			if((I2C2->SR1 & 2)==0)
			{
				break;
			}
		}
		
		I2C2->DR =analog;
		
		tmp = I2C2->SR1;
		tmp = I2C2->SR2;
		I2C2->CR1 |= 0x200;
		
		
		DelayMs(1);
	}
	
}

