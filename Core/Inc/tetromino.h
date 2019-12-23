#ifndef TETROMINO_H
#define TETROMINO_H
#include "sys.h"

typedef struct{
	int8_t x[4][4];
	int8_t y[4][4];
	uint16_t color;
} Image_t;

typedef struct{
	int8_t x;
	int8_t y;
	uint8_t shape;
	uint8_t rotation;
} Tetromino_t;


#define SHAPE_I 0
#define SHAPE_J 1
#define SHAPE_L 2
#define SHAPE_O 3
#define SHAPE_S 4
#define SHAPE_T 5
#define SHAPE_Z 6
#define SHAPE_NUM 7

extern Tetromino_t tetromino;
extern Tetromino_t tetromino_next;
extern Image_t tetimg_list[SHAPE_NUM];

uint8_t left_shift_check(void);
uint8_t right_shift_check(void);
uint8_t down_shift_check(void);
uint8_t rotation_check(void);
void flush_tetromino(void);
void tetromino_reset(void);
void tetromino_init(void);
#endif
