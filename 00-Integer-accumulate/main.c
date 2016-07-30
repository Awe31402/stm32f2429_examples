#include <stdint.h>
extern int i;
extern uint32_t _sdata;

void main(void)
{
  while(1) {
    i++;
  }
}
