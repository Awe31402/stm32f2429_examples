#include "stm32f4xx.h"
#include <stdint.h>

#define GPIO GPIOB
#define PIN 6
#define DELAY 120000
unsigned int* activate(unsigned int *stack);

void initGpio()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
  GPIO->MODER &= ~GPIO_MODER_MODER6_0;
  GPIO->MODER |= GPIO_MODER_MODER6_0;
  GPIO->OTYPER &= ~GPIO_OTYPER_OT_6;

  GPIO->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
  GPIO->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0;
  GPIO->PUPDR &= ~GPIO_PUPDR_PUPDR6;
}

void user_task(void)
{
  int i;

  while (1) {
    i = DELAY;
    while (i--);
    GPIO->ODR ^= GPIO_ODR_ODR_6;
  }
}

void main(void)
{
  initGpio();
  GPIO->ODR |= GPIO_ODR_ODR_6;
  SysTick->LOAD = 7200000;
  SysTick->VAL = 0;
  SysTick->CTRL = 0x07;

  unsigned int user_task_stack[256];
  unsigned int *user_task_stack_start = user_task_stack + 256 - 16;
  user_task_stack_start[8] = (unsigned int) &user_task;

  user_task_stack_start = activate(user_task_stack_start);
  while(1) {
  }
}

void __attribute__((interrupt)) systick_handler(void)
{
}
