#if !defined(_IO_H_)
#define _IO_H_

#include "mine.h"
#include "io.h"
#include "types.h"

#define KEY_LEFT   0x4B00
#define KEY_UP     0x4800
#define KEY_RIGHT  0x4D00
#define KEY_DOWN   0x5000
#define KEY_SPACE  0x3920
#define KEY_ENTER  0x1C0D
#define KEY_ESCAPE 0x011B
#define KEY_F5     0x3F00
#define KEY_F6     0x4000
#define KEY_F7     0x4100

uint16_t read_keyb();
void process_input(board* b);

#endif
