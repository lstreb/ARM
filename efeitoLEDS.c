/*
    Crie (invente, inove, seja criativo) um efeito visual na linha de leds, a exemplo dos exercícios anteriores.
*/

#include "stm32f4xx.h"

int main(void)
{
  RCC->AHB1ENR=0x87; //habilita o clock das portas

  RCC->APB2ENR|=0x20000; //habilita o timer (nesse caso o timer 10 no pino 17)
  TIM10->CR1|=0x05; //habilita a contagem do timer10

  GPIOC->MODER|=0x5555; //pinos c configurados como saida
  GPIOA->MODER|=0x28555500; //pa5 como saida

  //agora calcula o valor so ARR e do PSC
  TIM10->PSC=1279; //vai ser 0,08s
  TIM10->ARR=999;

  //vetor com os leds que tem que ligar
  int tab[10] = {0x01, 0x3, 0x6, 0xC, 0x18, 0x30, 0x60, 0xC0, 0x80};

  while (1)
  {
 //para saber se o tempo passou fazemos:
    for(int i=0; i<9; i++){
        while((TIM10->SR & 0x01)==0x00){};
        GPIOC->ODR&=~0xff;
        GPIOC->ODR|= tab[i];
        TIM10->SR &= ~(0x01); //inverte o status dos bits
    }
  }
}