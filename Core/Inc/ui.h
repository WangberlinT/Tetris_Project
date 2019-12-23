#ifndef __UI_H
#define __UI_H
#include "sys.h"
#include "lcd.h"

void draw_bg(void);
void draw_block(uint8_t x, uint8_t y, uint16_t color, uint8_t mode);
void grid_render(void);
void sub_grid_render(void);
void draw_tetromino(uint8_t clear);
void draw_next_tetromino(uint8_t clear);
void draw_next_next_tetromino(uint8_t clear);
void draw_name(char* name);
void update_score(uint16_t score);
void draw_rank_list(void);

#endif
