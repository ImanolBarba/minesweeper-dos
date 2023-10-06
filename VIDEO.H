#if !defined (_VIDEO_H_)
#define _VIDEO_H_

#include "mine.h"
#include "types.h"
#include "video.h"

#define TEXT_1_FG 9
#define TEXT_1_BG 0
#define TEXT_2_FG 10
#define TEXT_2_BG 0
#define TEXT_3_FG 12
#define TEXT_3_BG 0
#define TEXT_4_FG 1
#define TEXT_4_BG 0
#define TEXT_5_FG 4
#define TEXT_5_BG 0
#define TEXT_6_FG 3
#define TEXT_6_BG 0
#define TEXT_7_FG 13
#define TEXT_7_BG 0
#define TEXT_8_FG 14
#define TEXT_8_BG 0
#define TEXT_FLAG_FG 12
#define TEXT_FLAG_BG 8
#define TEXT_BOMB_FG 0
#define TEXT_BOMB_BG 12
#define TEXT_EMPTY_FG 15
#define TEXT_EMPTY_BG 0

void init_cga_mode();
void reset_video();
void print_char_color(char z, uint8_t x, uint8_t y, uint8_t fg, uint8_t bg);
void print_box(board* b); 
void print_board(board* b);

#endif
