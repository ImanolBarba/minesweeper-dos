#include "errors.h"
#include "io.h"
#include "sound.h"
#include "timer.h"

uint16_t read_keyb() {
  uint16_t key = 0;
  
  asm mov ah, 0
  asm int 16h
  asm mov key, ax

  return key;
}

void process_input(board* b) {
  int redraw_board = 0;
  int x, y;
  int ret = 0;

  for(;;) {
    redraw_board = 0;
    x = wherex();
    y = wherey();
    ret = 0;
    switch(read_keyb()) {
      case KEY_F5:
        redraw_board = 1;
        init_cga_mode();
        break;
      case KEY_LEFT:
        if(x != 2) {
          chirp();
          gotoxy(x-1, y);
        }
        break;
      case KEY_UP:
        if(y != 2) {
          chirp();
          gotoxy(x, y-1);
        }
        break;
      case KEY_RIGHT:
        if(x != b->cols+1) {
          chirp();
          gotoxy(x+1, y);
        }
        break;
      case KEY_DOWN:
        if(y != b->rows+1) {
          chirp();
          gotoxy(x, y+1);
        }
        break;
      case KEY_SPACE:
        redraw_board = 1;
        mark_tile(b, x-2, y-2);
        break;        
      case KEY_ENTER:
        redraw_board = 1;
        ret = select_tile(b, x-2, y-2);
        break;
      case KEY_ESCAPE:
        ret = YOU_DIED;
        redraw_board = 1;
        game_over(b);
        break;
      case KEY_F6:
        start_timer_interrupt();
        break;
      case KEY_F7:
        stop_timer_interrupt();
        break;
    }
    if(redraw_board) {
      print_board(b);
      gotoxy(x, y);
    }
    if(ret == YOU_DIED || ret == YOU_WIN) {
      finish_game(b, ret);
      return;
    }
  }
}
