#include "video.h"

void init_cga_mode() {
  asm mov ah, 0
  asm mov al, 3
  asm int 10h

  asm mov ah, 1
  asm mov cx, 0007h
  asm int 10h
}

void reset_video() {
  asm mov ah, 1
  asm mov cx, 0607h
  asm int 10h
}


void print_char_color(char z, uint8_t x, uint8_t y, uint8_t fg, uint8_t bg) {
  asm push ax
  asm push bx
  asm push di
  asm push es

  asm mov ax, 0B800h
  asm mov es, ax

  asm mov bh, y
  asm mov bl, x
  asm mov ax, 80
  asm mul bh
  asm xor bh, bh
  asm add ax, bx
  asm shl ax, 1
  asm mov di, ax
  
  asm mov ah, bg
  asm shl ah, 4
  asm or ah, fg
  asm mov al, z 
  asm mov byte ptr es:[di], al
  asm mov byte ptr es:[di+1], ah

  asm pop es
  asm pop di
  asm pop bx
  asm pop ax
}

void print_num(uint8_t num, uint8_t x, uint8_t y) {
  switch(num) {
    case 1:
      print_char_color('1', x, y, TEXT_1_FG, TEXT_1_BG);
      break;
    case 2:
      print_char_color('2', x, y, TEXT_2_FG, TEXT_2_BG);
      break;
    case 3:
      print_char_color('3', x, y, TEXT_3_FG, TEXT_3_BG);
      break;
    case 4:
      print_char_color('4', x, y, TEXT_4_FG, TEXT_4_BG);
      break;
    case 5:
      print_char_color('5', x, y, TEXT_5_FG, TEXT_5_BG);
      break;
    case 6:
      print_char_color('6', x, y, TEXT_6_FG, TEXT_6_BG);
      break;
    case 7:
      print_char_color('7', x, y, TEXT_7_FG, TEXT_7_BG);
      break;
    case 8:
      print_char_color('8', x, y, TEXT_8_FG, TEXT_8_BG);
      break;
    
  }
}

void print_box(board* b) {
  unsigned int i;
  print_char_color(0xC9, 0, 0, 0xF, 0x0);  
  print_char_color(0xBB, b->cols+1, 0, 0xF, 0x0);    
  print_char_color(0xC8, 0, b->rows+1, 0xF, 0x0);  
  print_char_color(0xBC, b->cols+1, b->rows+1, 0xF, 0x0);  

  for(i = 1; i < (b->cols+1); ++i) {
    print_char_color(0xCD, i, 0, 0x0F, 0x00);
    print_char_color(0xCD, i, b->rows+1, 0x0F, 0x00);
  }

  for(i = 1; i < (b->rows+1); ++i) {
    print_char_color(0xBA, 0, i, 0x0F, 0x00);
    print_char_color(0xBA, b->cols+1, i, 0x0F, 0x00);
  }
}

void print_board(board* b) {
  unsigned int row;
  unsigned int col;

  print_box(b);

  for(row = 0; row < b->rows; ++row) {
    for(col = 0; col < b->cols; ++col) {
      if(b->map[row][col] & FLAG_DISCOVERED) {
        switch(b->map[row][col] & EMPTY) {
          case BOMB:
            print_char_color('*', col+1, row+1, TEXT_BOMB_FG, TEXT_BOMB_BG);
            break;
          case EMPTY:
            print_char_color(' ', col+1, row+1, TEXT_EMPTY_FG, TEXT_EMPTY_BG);
            break;
          default:
            print_num(b->map[row][col] & 0x0F, col+1, row+1);
            break;
        }
      } else if(b->map[row][col] & FLAG_MARKED) {
        print_char_color('X', col+1, row+1, TEXT_FLAG_FG, TEXT_FLAG_BG);        
      } else {
        print_char_color('#', col+1, row+1, TEXT_EMPTY_FG, TEXT_EMPTY_BG);
      }
    }
  }
}

