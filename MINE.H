#if !defined(_MINE_H_)
#define _MINE_H_

#include <stdlib.h>

#include "types.h"

#define FLAG_MARKED 0x40
#define FLAG_DISCOVERED 0x80
#define EMPTY 0x0F
#define BOMB 0x00

typedef struct board {
  size_t rows;
  size_t cols;
  size_t num_mines;
  size_t undiscovered_tiles;
  uint8_t** map;
} board;

board gen_board(size_t width, size_t height, unsigned int num_mines);
int select_tile(board* b, unsigned int x, unsigned int y);
void mark_tile(board* b, unsigned int x, unsigned int y);
unsigned int get_remaining_mines(board* b);
void destroy_board(board* b);

#endif
