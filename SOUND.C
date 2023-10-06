#include "sound.h"
#include "types.h"

extern uint32_t ticks;

void beep(unsigned int millis, unsigned int freq) {
  uint16_t divider;
  uint8_t tmp;
  uint32_t time_start;

  divider = 1193180 / freq;

  asm mov al, 0xb6
  asm out 0x43, al
  asm mov ax, divider
  asm out 0x42, al
  asm mov al, ah
  asm out 0x42, al

  asm in al, 0x61
  asm mov bl, al
  asm or al, 3
  asm cmp al, bl
  asm je start_wait
  asm out 0x61, al
  
  start_wait:
  time_start = ticks;
  while((ticks - time_start) < millis) {
    /* spin */
  }

  asm in al, 0x61
  asm and al, 0xFC
  asm out 0x61, al
}


void chirp() {
  beep(10, 100);
}

