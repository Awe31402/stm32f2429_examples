#include "stm32f4xx.h"
#include <stdint.h>

#define GPIO GPIOB
#define PIN 6

void initGpio()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  GPIO->MODER &= ~GPIO_MODER_MODER6;
  GPIO->MODER |= GPIO_MODER_MODER6_0;
  GPIO->OTYPER &= ~GPIO_OTYPER_OT_6;

  GPIO->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
  GPIO->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0;
  GPIO->PUPDR &= ~GPIO_PUPDR_PUPDR6;
}

void main(void)
{
  initGpio();
  GPIO->ODR |= GPIO_ODR_ODR_13;
  SysTick->LOAD = 7200000;
  SysTick->VAL = 0;
  SysTick->CTRL = 0x07;
  while(1) {
  }
}

void __attribute__((interrupt)) systick_handler(void)
{
  GPIO->ODR ^= GPIO_ODR_ODR_6;
}
