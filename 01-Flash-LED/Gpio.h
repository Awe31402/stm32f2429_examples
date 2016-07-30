#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/*
 * gpio.h
 * =========================
 * this header defines gpio register
 * type and setting indicated address
 * for each gpio.
 * see. stm32f429 spec. p.288
 */
#define __IO
typedef struct {
  __IO uint32_t MODER;
  __IO uint16_t OTYPER;
       uint16_t rev0;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __IO uint16_t IDR;
       uint16_t rev1;
  __IO uint16_t ODR;
       uint16_t rev2;
  __IO uint16_t BSRRL;
  __IO uint16_t BSRRH;
  __IO uint32_t LCKR;
  __IO uint32_t AFR[2];
} Gpio_TypeDef;

#define GPIOA ((Gpio_TypeDef*) 0x40020000)
#define GPIOB ((Gpio_TypeDef*) 0x40020400)
#define GPIOC ((Gpio_TypeDef*) 0x40020800)
#define GPIOD ((Gpio_TypeDef*) 0x40020C00)
#define GPIOE ((Gpio_TypeDef*) 0x40021000)
#define GPIOF ((Gpio_TypeDef*) 0x40021400)
#define GPIOG ((Gpio_TypeDef*) 0x40021800)
#define GPIOH ((Gpio_TypeDef*) 0x40021C00)
#define GPIOI ((Gpio_TypeDef*) 0x40022000)
#define GPIOJ ((Gpio_TypeDef*) 0x40022400)
#define GPIOK ((Gpio_TypeDef*) 0x40022800)

#endif
