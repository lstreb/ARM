/*
    Esse código gera um número aleatório de 1 a 6 (assim como um dado) quando o usuário aperta um botão.
    O número gerado aparece em um display de 7 segmentos.
*/

#include "stm32f4xx.h"
#include <time.h>

void delay()
{
    int d=0;

    for(int i=0; i <100000; i++){
      d++;
    }
}

int main(void)
{
    int tab[10] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0xff, 0x6f};
    //a = pc0  b = pc1  c = pc2  d = pc3  e = pc4  f = pc5  g = pc6
    int x=0, aux = 0, flag = 1;

    RCC->AHB1ENR=0x87; //habilita o clock das portas
    GPIOC->MODER|=0x5555; //pinos configurados como saida
    GPIOB->MODER|=0x000;

    srand(time(NULL));

    while (1)
    {
        if((GPIOB->IDR & 0x2000)==0x0){
            flag=0;
        }

        if(((GPIOB->IDR & 0x2000)==0x2000) && flag==0){
            x = 1 + (rand() % 6);
            GPIOC->ODR&=~0xff;
            GPIOC->ODR|= tab[x];
            flag=1;
        }
        delay();
    }
}