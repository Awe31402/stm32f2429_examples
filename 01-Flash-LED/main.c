#include <stdint.h>
#include "stm32f4xx.h"

#define GPIO GPIOB
#define NUMBER 6

void GpioClockEnable()
{
  /*Enable clock to GPIO port G*/
  RCC->AHB1ENR |= 1 << 1;
}

void GpioPinInit()
{
  /* Set pin 6 I/O mode as general
   * purpose output.
   * 00 = digital input,        01 = digital output
   * 10 = alternative function, 11 = analog
   */

  /*clear mode of pin6 as 00*/
  GPIO->MODER &= ~(0x03 << (2 * NUMBER));
  /*set GPIOB pin 6 as output mode*/
  GPIO->MODER |= (0x01 << (2 * NUMBER));

  /*set output type as push-pull*/
  GPIO->OTYPER &= ~(1 << NUMBER);

  /*set IO output speed
   * 00 = 400KHz, 01 = 2 MHz,
   * 10 = 10MHz,  11 = 40MHz
   */
  GPIO->OSPEEDR &= ~(0x03 << (2 * NUMBER));
  GPIO->OSPEEDR |= 0x01 << (2 * NUMBER);

  GPIO->PUPDR &= ~(0x03 << (2 * NUMBER));
}

void main(void)
{
  uint32_t i;
  GpioClockEnable();
  GpioPinInit();
  GPIO->ODR |= (1 << NUMBER);
  while (1) {
    for (i = 0; i < 120000; i++);
    GPIO->ODR ^= (1 << NUMBER);
  }
}
