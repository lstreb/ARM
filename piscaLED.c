/*
    Elabore um programa capaz de piscar o Led com um ciclo de trabalho de 50% 
    (metade do tempo ligado, metade desligado) e com período de 200ms 
    (5 Hz ou 5 piscadas/segundo).  O led é ativo em LOW e conectado ao PC0.
    Utilize o TIM11.
*/

#include "stm32f4xx.h"

void delay()
{
    while((TIM11->SR & 0x01)==0x00){};
    TIM11->SR&= ~(0x01);
}

int main(void)
{
  RCC->AHB1ENR=0x87; //habilita o clock das portas
  RCC->APB2ENR|=0x40000; //habilita o timer (nesse caso o timer 11 no pino 18)
  TIM11->CR1|=0x05; //habilita a contagem do timer11
  GPIOC->MODER|=0x5555;

  //agora calcula o valor so ARR e do PSC
  TIM11->PSC=3999;
  TIM11->ARR=799;

  while (1)
  {
   delay();
   GPIOC->ODR|=0x01; //liga

   delay();
   GPIOC->ODR&=~0x01; //desliga
  }
}