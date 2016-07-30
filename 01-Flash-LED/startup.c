#include <stdint.h>

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

extern void main(void);
void reset_handler(void)
{
  uint32_t* idata_begin = &_sidata;
  uint32_t* data_begin = &_sdata;
  uint32_t* data_end = &_edata;
  while (data_begin < data_end) *data_begin++ = *idata_begin++;

  uint32_t* bss_begin = &_sbss;
  uint32_t* bss_end = &_ebss;
  while (bss_begin < bss_end) *bss_begin++ = 0;

  main();
}

__attribute((section(".isr_vector")))
uint32_t *isr_vectors[] = {
  [0x00] = (uint32_t*) &_estack,
  [0x01] = (uint32_t*) reset_handler,
};
