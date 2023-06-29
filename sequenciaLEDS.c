/*
    Acione os leds em sequência, começando de uma ponta da linha e
    percorrendo até a outra ponta, acionando o proximo led, mantendo o anterior
    acionado. Ao preencher a linha, retornar apagando os leds.
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
  TIM10->PSC=4999; //vai ser 0,5s
  TIM10->ARR=1599;

  //vetor com os leds que tem que ligar
  int tab[8] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};

  while (1)
  {
    //para saber se o tempo passou fazemos:
    for(int i=0; i<8; i++){
        while((TIM10->SR & 0x01)==0x00){};
        GPIOC->ODR|= tab[i];
        TIM10->SR &= ~(0x01); //inverte o status dos bits
    }

    for(int i=7; i>-1; i--){
        while((TIM10->SR & 0x01)==0x00){};
        GPIOC->ODR&=~tab[i];
        TIM10->SR &= ~(0x01); //inverte o status dos bits
    }
  }
}