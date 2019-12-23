#ifndef __GRID_H
#define __GRID_H
#include "sys.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define CELL_LENGTH 15

typedef struct
{
	uint8_t isEmpty;
	uint16_t color;
} cell_t;

extern cell_t grid[GRID_HEIGHT][GRID_WIDTH];
extern cell_t sub_grid[4][4];

uint8_t max_height;

uint8_t grid_scan(void);
void clear_row(uint8_t line);
void empty_row(uint8_t line);
void grid_init(void);
void sub_grid_init(void);
void flush_tetromino(void);

#endif
