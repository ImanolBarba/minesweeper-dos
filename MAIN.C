#include <stdio.h>
#include <string.h>

#include "game.h"
#include "mine.h"

void print_help(const char* argv0) {
  printf("%s MODE [WIDTH] [HEIGHT] [MINES]\n", argv0);
  printf("\n");
  printf("Modes: EASY, MEDIUM, HARD, CUSTOM\n");
  printf("\n");
}

int main(int argc, char** argv) {
  size_t width = 0;
  size_t height = 0;
  size_t num_mines = 0;
  board b;

  if(argc == 1 || argc > 5) {
    printf("Invalid number of arguments\n");
    print_help(argv[0]);
    return 1;
  }

  if(!strncmp(argv[1], "EASY", 4)) {
    width = 8;
    height = 8;
    num_mines = 10;
  } else if(!strncmp(argv[1], "MEDIUM", 4)) {
    width = 16;
    height = 16;
    num_mines = 40;
  } else if(!strncmp(argv[1], "HARD", 4)) {
    width = 30;
    height = 16;
    num_mines = 99;
  } else if(!strncmp(argv[1], "CUSTOM", 4)) {
    width = atoi(argv[2]);
    height = atoi(argv[3]);
    num_mines = atoi(argv[4]);
  } else {
    printf("Invalid mode: %s\n", argv[1]);
    print_help(argv[0]);
    return 1;
  }

  b = gen_board(width, height, num_mines);

  start_game(&b);
  
  destroy_board(&b);

  return 0;
}
























































