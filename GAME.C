#include "errors.h"
#include "game.h"
#include "io.h"
#include "sound.h"
#include "timer.h"
#include "video.h"

void print_game_stats(board* b) {
  print_time();
  printf("Mines remaining: %d\n", get_remaining_mines(b));
}

void finish_game(board* b, int status) {
  gotoxy(1, b->rows+4);
  if(status == YOU_WIN) {
    printf("YOU WIN!\n");
  } else {
    printf("GAME OVER\n");
  }
  print_game_stats(b);

  if(status == YOU_WIN) {
    beep(1000, 440);
  } else {
    beep(1000, 220);
  }
}

void start_game(board* b) {
  init_cga_mode();

  print_board(b);
  gotoxy(2,2);

  start_timer_interrupt();
  process_input(b);
  stop_timer_interrupt();

  reset_video();
}
