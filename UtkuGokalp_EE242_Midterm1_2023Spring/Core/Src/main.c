#include "stm32f407xx.h"

/*
    Question 1:
    ASCII Name: 329 (UTKU)
    ASCII Surname: 446 (GOKALP)
    ASCII Total: 775
    Timer number: (775 % 14) + 1 = 6
    ARRNUMBER: 65536 - 1
    Duration: (446 % 1500) * 30 = 13380
    LED_PIN_NUMBER: (775 % 4) + 12 = 15
*/

const int ARR_NUMBER = 65536 - 1;

int main(void)
{
	int duration = 13380;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= 0x55000000;
	GPIOD->ODR |= 0x00008000;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = 2;
	TIM6->ARR = ARR_NUMBER;
	
	TIM6->CR1 = 1; //Start the timer
	while (1)
	{
		if (TIM6->CNT >= duration)
		{
			TIM6->CR1 = 0; //Stop the timer
			TIM6->CNT = 0;
			GPIOD->ODR ^= 0x00008000;
			TIM6->CR1 = 1; //Start the timer
		}
	}
}
