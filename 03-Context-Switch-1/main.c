#include "stm32f4xx.h"
#include <stdint.h>

#define _RCC_AHB1ENR_GPIOEN(PORT) RCC_AHB1ENR_GPIO## PORT ##EN
#define _GPIO_MODER_MODER(PIN) GPIO_MODER_MODER## PIN
#define _GPIO_MODER_MODER_0(PIN) GPIO_MODER_MODER## PIN ##_0
#define _GPIO_OTYPER_OT(PIN) GPIO_OTYPER_OT_## PIN
#define _GPIO_OSPEEDER_OSPEEDR(PIN) GPIO_OSPEEDER_OSPEEDR## PIN
#define _GPIO_OSPEEDER_OSPEEDR_0(PIN) GPIO_OSPEEDER_OSPEEDR## PIN ##_0
#define _GPIO_PUPDR_PUPDR(PIN) GPIO_PUPDR_PUPDR## PIN
#define _GPIO_ODR_ODR(PIN) GPIO_ODR_ODR_## PIN

#ifdef BOARD_LED
  #define GPIO GPIOG
  #define RCC_AHB1ENR_GPIOEN _RCC_AHB1ENR_GPIOEN(G)

  #define PIN 13
  #define GPIO_MODER_MODER _GPIO_MODER_MODER(13)
  #define GPIO_MODER_MODER_0 _GPIO_MODER_MODER_0(13)
  #define GPIO_OTYPER_OT _GPIO_OTYPER_OT(13)
  #define GPIO_OSPEEDER_OSPEEDR _GPIO_OSPEEDER_OSPEEDR(13)
  #define GPIO_OSPEEDER_OSPEEDR_0 _GPIO_OSPEEDER_OSPEEDR_0(13)
  #define GPIO_PUPDR_PUPDR _GPIO_PUPDR_PUPDR(13)
  #define GPIO_ODR_ODR _GPIO_ODR_ODR(13)
#else
  #define GPIO GPIOB
  #define RCC_AHB1ENR_GPIOEN _RCC_AHB1ENR_GPIOEN(B)

  #define PIN 6
  #define GPIO_MODER_MODER _GPIO_MODER_MODER(6)
  #define GPIO_MODER_MODER_0 _GPIO_MODER_MODER_0(6)
  #define GPIO_OTYPER_OT _GPIO_OTYPER_OT(6)
  #define GPIO_OSPEEDER_OSPEEDR _GPIO_OSPEEDER_OSPEEDR(6)
  #define GPIO_OSPEEDER_OSPEEDR_0 _GPIO_OSPEEDER_OSPEEDR_0(6)
  #define GPIO_PUPDR_PUPDR _GPIO_PUPDR_PUPDR(6)
  #define GPIO_ODR_ODR _GPIO_ODR_ODR(6)
#endif

#define DELAY 12000000
unsigned int* activate(unsigned int *stack);

void initGpio()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEN;
  GPIO->MODER &= ~GPIO_MODER_MODER;
  GPIO->MODER |= GPIO_MODER_MODER_0;
  GPIO->OTYPER &= ~GPIO_OTYPER_OT;

  GPIO->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR;
  GPIO->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR_0;
  GPIO->PUPDR &= ~GPIO_PUPDR_PUPDR;
}

void user_task(void)
{
  int i;

  while (1) {
    i = DELAY;
    while (i--);
    GPIO->ODR ^= GPIO_ODR_ODR;
  }
}

void main(void)
{
  initGpio();
  GPIO->ODR |= GPIO_ODR_ODR;
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
