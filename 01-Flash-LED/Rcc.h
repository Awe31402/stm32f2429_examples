#ifndef RCC_H
#define RCC_H

#include <stdint.h>

#define __IO
typedef struct {
  __IO uint32_t CR;
  __IO uint32_t PLLCFGR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t AHB1RSTR;
  __IO uint32_t AHB2RSTR;
  __IO uint32_t AHB3RSTR;
       uint32_t rev0;
  __IO uint32_t APB1RSTR;
  __IO uint32_t APB2RSTR;
       uint32_t rev1;
       uint32_t rev2;
  __IO uint32_t AHB1ENR;
  __IO uint32_t AHB2ENR;
  __IO uint32_t AHB3ENR;
  __IO uint32_t rev3;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef*) 0x40023800)
#endif
