#include "lcd.h"
#include "sys.h"
#include "grid.h"
#include "ui.h"
#include "usart.h"
#include "tetromino.h"
#include <stdio.h>
void draw_bg()
{
  POINT_COLOR = WHITE;
  BACK_COLOR = BLACK;
  //main window
  LCD_DrawRectangle(9, 9, 161, 311);
  //sub window
  LCD_DrawRectangle(165, 225, 235, 295);
  //sub sub window
  LCD_DrawRectangle(165, 125, 235, 195);
  LCD_ShowString(182, 300, 200, 16, 16, (unsigned char*)"FIRST");
  LCD_ShowString(175, 200, 200, 16, 16, (unsigned char*)"SECOND");
  LCD_ShowString(177,  20, 200, 16, 16, (unsigned char*)"SCORE:");
  LCD_ShowString(172,  40, 200, 16, 16, (unsigned char*)"   0");
  LCD_ShowString(177,  60, 200, 16, 16, (unsigned char*)"LEVEL:");
  LCD_ShowString(172,  80, 200, 16, 16, (unsigned char*)"   0");
  LCD_Fill(10, 10, 160, 310, BLACK);
  LCD_Fill(166, 226, 234, 294, BLACK);
  LCD_Fill(166, 126, 234, 194, BLACK);
}

void draw_block(uint8_t x, uint8_t y, uint16_t color, uint8_t mode) //mode 0:main window 1:sub winodw
{
  uint16_t rx, ry;

  if (mode == 0)
  {
    rx = 10 + x * CELL_LENGTH;
    ry = 295 - y * CELL_LENGTH;
  }
  else if (mode == 1)
  {
    rx = 170 + x * CELL_LENGTH;
    ry = 275 - y * CELL_LENGTH;
  }
  else if (mode == 2)
  {
    rx = 170 + x * CELL_LENGTH;
    ry = 175 - y * CELL_LENGTH;
  }
  POINT_COLOR = color;
  LCD_DrawRectangle(rx, ry, rx + 15, ry + 15);
  LCD_Fill(rx + 2, ry + 2, rx + 13, ry + 13, color);
}

void grid_render()
{
  int8_t x, y;
  cell_t cell;
  for (y = GRID_HEIGHT - 1; y >= 0; y--)
  {
    for (x = 0; x < GRID_WIDTH; x++)
    {
      cell = grid[y][x];
      if (cell.isEmpty)
      {
        draw_block(x, y, BLACK, 0);
      }
      else
      {
        draw_block(x, y, cell.color, 0);
      }
    }
  }
}

void sub_grid_render()
{
  uint8_t x, y;
  cell_t cell;
  for (y = 0; y < 4; y++)
  {
    for (x = 0; x < 4; x++)
    {
      cell = sub_grid[y][x];
      if (cell.isEmpty)
        continue;

      draw_block(x, y, cell.color, 1);
    }
  }
}

void draw_tetromino(uint8_t clear)
{
  uint8_t i;
  Image_t *it = &tetimg_list[tetromino.shape];
  uint16_t color = it->color;
  if (clear)
  {
    color = BLACK;
  }
  for (i = 0; i < 4; i++)
  {
    draw_block(it->x[tetromino.rotation][i] + tetromino.x, it->y[tetromino.rotation][i] + tetromino.y, color, 0);
  }
}

void draw_next_tetromino(uint8_t clear)
{
  uint8_t i;
  Image_t *it = &tetimg_list[tetromino_next.shape];
  uint16_t color = it->color;
  if (clear)
  {
    color = BLACK;
  }
  for (i = 0; i < 4; i++)
  {
    draw_block(it->x[tetromino_next.rotation][i], it->y[tetromino_next.rotation][i], color, 1);
  }
}

void draw_next_next_tetromino(uint8_t clear)
{
  uint8_t i;
  Image_t *it = &tetimg_list[tetromino_next_next.shape];
  uint16_t color = it->color;
  if (clear)
  {
    color = BLACK;
  }
  for (i = 0; i < 4; i++)
  {
    draw_block(it->x[tetromino_next_next.rotation][i], it->y[tetromino_next_next.rotation][i], color, 2);
  }
}

void update_score(uint16_t score)
{
  char str_score[5];
  char str_level[5];
  if (score > 9999)
    score = 9999;
  sprintf(str_score, "%4d", score);
  uint8_t level = score / 30;
  sprintf(str_level, "%4d", level);
  printf("score:%d str:%s\n", score, str_score);
  POINT_COLOR = WHITE;
  BACK_COLOR = BLACK;
  LCD_ShowString(172,  40, 200, 16, 16, (uint8_t *)str_score);
  LCD_ShowString(172,  80, 200, 16, 16, (uint8_t *)str_level);
}
