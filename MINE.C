#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "mine.h"

int valid_coords(board* b, unsigned int x, unsigned int y) {
  if(b->cols <= x || x < 0 || b->rows <= y || y < 0) {
    return 0;
  }
  return 1;
}

unsigned int get_remaining_mines(board* b) {
  unsigned int row;
  unsigned int col;
  unsigned int num_mines = 0;

  for(row = 0; row < b->rows; ++row) {
    for(col = 0; col < b->cols; ++col) {
      if(has_mine(b, col, row) && !is_tile_marked(b, col, row)) {
        ++num_mines;
      }
    }
  }

  return num_mines;
}

int has_mine(board* b, unsigned int x, unsigned int y) {
  if(valid_coords(b, x, y)) {
    if((b->map[y][x] & 0x0F) == BOMB) {
      return 1;
    }
  }
  return 0;
}

int is_tile_discovered(board* b, unsigned int x, unsigned int y) { 
  if(b->map[y][x] & FLAG_DISCOVERED) {
    return 1;
  }
  return 0;
}

int is_tile_marked(board* b, unsigned int x, unsigned int y) { 
  if(b->map[y][x] & FLAG_MARKED) {
    return 1;
  }
  return 0;
}

void discover_tile(board* b, unsigned int x, unsigned int y) {
  if(!valid_coords(b, x, y)) {
    return;
  }
  if(is_tile_discovered(b, x, y)) {
    return;
  }
  b->map[y][x] |= FLAG_DISCOVERED;
  b->undiscovered_tiles--;
  if((b->map[y][x] & EMPTY) == EMPTY) {
    discover_tile(b, x-1, y-1);
    discover_tile(b, x, y-1);
    discover_tile(b, x+1, y-1);
    discover_tile(b, x-1, y);
    discover_tile(b, x+1, y);
    discover_tile(b, x-1, y+1);
    discover_tile(b, x, y+1);
    discover_tile(b, x+1, y+1);
  }
}

void game_over(board* b) {
  unsigned int row;
  unsigned int col;

  for(row = 0; row < b->rows; ++row) {
    for(col = 0; col < b->cols; ++col) {
      if(has_mine(b, col, row)) {
        b->map[row][col] |= FLAG_DISCOVERED;
      }
    }
  }
}

board gen_board(size_t width, size_t height, unsigned int num_mines) {
  unsigned int row;
  unsigned int col;
  unsigned int i;
  unsigned int mine_location;
  unsigned int mine_counter;
  board b;

  b.rows = height;
  b.cols = width;
  b.num_mines = num_mines;
  b.undiscovered_tiles = width * height;
  b.map = malloc(sizeof(uint8_t*) * height);
  for(row = 0; row < height; ++row) {
    b.map[row] = malloc(sizeof(uint8_t) * width);
    memset(b.map[row], EMPTY, width);
  }

  srand(time(NULL));

  /* First pass */  
  for(i = 0; i < num_mines; ++i) {
    mine_location = rand() % (width * height);
    if(b.map[mine_location / width][mine_location % width] == BOMB) {
      --i;
    }
    b.map[mine_location / width][mine_location % width] = BOMB;
  }

  /* Second pass */
  for(row = 0; row < height; ++row) {
    for(col = 0; col < width; ++col) {
      if(has_mine(&b, col, row)) {
        continue;
      }
      mine_counter = 0;
      if(has_mine(&b, col-1, row-1)) {
        ++mine_counter;
      }
      if(has_mine(&b, col, row-1)) {
        ++mine_counter;
      }
      if(has_mine(&b, col+1, row-1)) {
        ++mine_counter;
      }
      if(has_mine(&b, col-1, row)) {
        ++mine_counter;
      }
      if(has_mine(&b, col+1, row)) {
        ++mine_counter;
      }
      if(has_mine(&b, col-1, row+1)) {
        ++mine_counter;
      }
      if(has_mine(&b, col, row+1)) {
        ++mine_counter;
      }
      if(has_mine(&b, col+1, row+1)) {
        ++mine_counter;
      }
      if(mine_counter) {
        b.map[row][col] = mine_counter; 
      }
    }
  }
  return b;
}

int select_tile(board* b, unsigned int x, unsigned int y) {
  if(!valid_coords(b, x, y)) {
    return INVALID_COORDS;
  }
  if(is_tile_discovered(b, x, y)) {
    return 0;
  }
  if(has_mine(b, x, y)) {
    game_over(b);
    return YOU_DIED;
  }
  discover_tile(b, x, y);

  if(b->undiscovered_tiles == b->num_mines) {
    return YOU_WIN;
  }
  return 0;
}

void mark_tile(board* b, unsigned int x, unsigned int y) {
  if(!valid_coords(b, x, y)) {
    return;
  }
  if(is_tile_marked(b, x, y)) {
    b->map[y][x] &= ~FLAG_MARKED;
  } else {
    b->map[y][x] |= FLAG_MARKED;
  }
}

void destroy_board(board* b) {
  unsigned int row;

  for(row = 0; row < b->rows; ++row) {
    free(b->map[row]);
  }
  free(b->map);
}












































































































































































