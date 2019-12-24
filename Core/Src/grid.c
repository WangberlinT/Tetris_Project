#include "grid.h"
#include "tetromino.h"

cell_t grid[GRID_HEIGHT][GRID_WIDTH];

cell_t sub_grid[4][4];

uint8_t max_height = 0;

uint8_t grid_scan()
{
  int8_t x, y;
  uint8_t row_num = 0;
  //scan up->down
  for (y = GRID_HEIGHT; y >= 0; y--)
  {
    for (x = 0; x < GRID_WIDTH; x++){
      if(grid[y][x].isEmpty) {break;}
      if(x == GRID_WIDTH-1){
        clear_row(y);
        row_num ++;
      }
    }
  }
  return row_num;
}

void clear_row(uint8_t line)
{
	uint8_t x, y;
    //shift down->up
    for (y = line; y < GRID_HEIGHT; y++)
    {
        for (x = 0; x < GRID_WIDTH; x++)
        {
            grid[y][x] = grid[y+1][x];
        }
    }
}

void empty_row(uint8_t line)
{
	uint8_t x;
    for (x = 0; x < 10; x++)
        grid[line][x].isEmpty = 1;
}

void grid_init()
{
	uint8_t x, y;
    //scan up->down
    for (y = 0; y < GRID_HEIGHT; y++)
        for (x = 0; x < GRID_WIDTH; x++)
            grid[y][x].isEmpty = 1;
}

void sub_grid_init()
{
	uint8_t x, y;
    for (y = 0; y < 4; y++)
        for (x = 0; x < 4; x++)
            sub_grid[y][x].isEmpty=1;
}
