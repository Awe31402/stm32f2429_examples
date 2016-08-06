#include "stm32f4xx.h"
#include <stdint.h>

#define GPIO GPIOG
#define PIN 13
#define DELAY 12000000
unsigned int* activate(unsigned int *stack);
void syscall(void);
volatile uint32_t uptime = 0;

void initGpio()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
  GPIO->MODER &= ~GPIO_MODER_MODER13;
  GPIO->MODER |= GPIO_MODER_MODER13_0;
  GPIO->OTYPER &= ~GPIO_OTYPER_OT_13;

  GPIO->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13;
  GPIO->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_0;
  GPIO->PUPDR &= ~GPIO_PUPDR_PUPDR13;
}

void user_task(void)
{
  int i;

  while (1) {
    /*light up led int kernel mode*/
    GPIO->ODR |= GPIO_ODR_ODR_13;
    syscall();
  }
}

void main(void)
{
  initGpio();
  GPIO->ODR |= GPIO_ODR_ODR_13;
  SysTick->LOAD = 7200000;
  SysTick->VAL = 0;
  SysTick->CTRL = 0x07;

  unsigned int user_task_stack[256];
  unsigned int *user_task_stack_start = user_task_stack + 256 - 16;
  user_task_stack_start[8] = (unsigned int) &user_task;

  while(1) {
    /*close led in OS mode*/
    GPIO->ODR &= ~GPIO_ODR_ODR_13;
    user_task_stack_start = activate(user_task_stack_start);
  }
}

void __attribute__((interrupt)) systick_handler(void)
{
  uptime ++;
}
