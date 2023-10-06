#include <dos.h>
#include <stdlib.h>

#include "timer.h"

#define TIMER_FREQ 1000

uint32_t ticks = 0; 
void interrupt far (*old_handler)();

void interrupt tick_counter(void) {
  if((++ticks % 55) == 0) {
    (*old_handler)();
  }
  asm mov ax, 20h
  asm out 0x20, ax 
}

void start_timer_interrupt() {
  uint16_t count;
  
  count = (0x1234DC / TIMER_FREQ) & 0xFFFE;

  asm cli
  
  old_handler = getvect(8);
  setvect(8, tick_counter);

  asm mov al, 0x34
  asm out 0x43, al
  asm mov ax, count
  asm out 0x40, al
  asm mov al, ah
  asm out 0x40, al
  asm sti
}

void stop_timer_interrupt() {
  asm cli
  
  asm mov al, 0x34
  asm out 0x43, al
  asm xor al,al
  asm out 0x40, al
  asm out 0x40, al

  setvect(8, old_handler);

  asm sti
}

void print_time() {
  uint32_t millis;
  uint32_t seconds;
  uint32_t minutes;
  uint32_t hours;
  uint32_t days;

  asm cli
  millis = ticks;
  asm sti

  seconds = millis / 1000; 
  millis = millis % 1000;

  minutes = seconds / 60;
  seconds = seconds %  60;

  hours = minutes / 60;
  minutes = minutes % 60;

  days = hours / 24;
  hours = hours % 24;

  printf("Time: ");
  if(days) {
    printf("%d:", days);
  }
  if(hours) {
    printf("%02d:", hours);
  }
  printf("%02d:", minutes);
  printf("%02d.", seconds);
  printf("%03d\n", millis);
}
