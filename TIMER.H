#if !defined(_TIMER_H_)
#define _TIMER_H_

#include "types.h"

#define TIMER_FREQ 1000

void start_timer_interrupt(); 
void stop_timer_interrupt();
void print_time();

#endif
