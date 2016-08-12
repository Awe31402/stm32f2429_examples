#include "stm32f4xx.h"
#include <stdint.h>

#define GPIO GPIOB
#define PIN 6

void initGpio()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  GPIO->MODER &= ~GPIO_MODER_MODER6;
  GPIO->MODER |= GPIO_MODER_MODER6_1;

  GPIO->AFR[PIN >> 3] &= 0xf << ((PIN & 0x7) << 2);
  GPIO->AFR[PIN >> 3] |= 0x2 << ((PIN & 0x7) << 2);

  GPIO->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
  GPIO->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR6_0;
  GPIO->PUPDR &= ~GPIO_PUPDR_PUPDR6;
  GPIO->OTYPER &= ~GPIO_OTYPER_OT_6;
}

void initTimer()
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  TIM4->PSC = (uint16_t) 2096;
  TIM4->ARR = (uint16_t) 1000;
  TIM4->CCR1 = (uint16_t) 500;
  TIM4->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1;
  TIM4->CCER |= TIM_CCER_CC1E;
  TIM4->CR1 = TIM_CR1_CEN;
}

void main(void)
{
  initGpio();
  initTimer();
  while(1) {
  }
}

void __attribute__((interrupt)) systick_handler(void)
{
  GPIO->ODR ^= GPIO_ODR_ODR_6;
}
