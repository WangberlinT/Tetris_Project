#include "tetromino.h"
#include <stdlib.h>
#include "grid.h"
#include "lcd.h"

Tetromino_t tetromino;
Tetromino_t tetromino_next;
Tetromino_t tetromino_next_next;
Image_t tetimg_list[SHAPE_NUM];

uint8_t left_shift_check() {
	int8_t a, b;
	uint8_t i;
	Image_t* it = &tetimg_list[tetromino.shape];
	for(i=0;i<4;i++)
	{
	  a = it->x[tetromino.rotation][i]+tetromino.x - 1;
	  b = it->y[tetromino.rotation][i]+tetromino.y;
		if(a<0)
		{
			return 0;
		}
	  if(!grid[b][a].isEmpty)
	  {
			return 0;
	  }
  }
  return 1;
}

uint8_t right_shift_check() {
	int8_t a, b;
	uint8_t i;
	Image_t* it = &tetimg_list[tetromino.shape];
	for(i=0;i<4;i++)
	{
	  a = it->x[tetromino.rotation][i]+tetromino.x + 1;
	  b = it->y[tetromino.rotation][i]+tetromino.y;
		if(a>=GRID_WIDTH) {return 0;}
	  if(!grid[b][a].isEmpty) {return 0;}
  }
  return 1;
}

uint8_t down_shift_check() {
	int8_t a, b;
	uint8_t i;
	Image_t* it = &tetimg_list[tetromino.shape];
	for(i=0;i<4;i++)
	{
	  a = it->x[tetromino.rotation][i]+tetromino.x;
	  b = it->y[tetromino.rotation][i]+tetromino.y - 1;
		if(b<0) {return 0;}
	  if(!grid[b][a].isEmpty) {return 0;}
  }
  return 1;
}

uint8_t rotation_check() {
	int8_t a, b, rot;
	uint8_t i;
	Image_t* it = &tetimg_list[tetromino.shape];
	for(i=0;i<4;i++)
	{
    rot = (tetromino.rotation+1)%4;
	  a = it->x[rot][i]+tetromino.x;
	  b = it->y[rot][i]+tetromino.y;
    if(a>=GRID_WIDTH || a<0 || b>=GRID_HEIGHT || b<0) {return 0;}
	  if(!grid[b][a].isEmpty) {return 0;}
  }
  return 1;
}

void flush_tetromino(){
	uint8_t i,a,b;
	Image_t* it = &tetimg_list[tetromino.shape];
	for(i=0;i<4;i++)
	{
	  a = it->x[tetromino.rotation][i]+tetromino.x;
	  b = it->y[tetromino.rotation][i]+tetromino.y;
		grid[b][a].isEmpty = 0;
		grid[b][a].color = it->color;
	}
}

void tetromino_reset() {
  tetromino = tetromino_next;
  tetromino_next = tetromino_next_next;
  tetromino_next_next = (Tetromino_t){
    .x = 3, .y = GRID_HEIGHT-4,
    .shape = rand()%SHAPE_NUM,
    .rotation = rand()%4
  };
}

void tetromino_init() {
  srand(rand());
  tetromino_reset();
  tetromino_reset();
  tetromino_reset();

  tetimg_list[SHAPE_I] = (Image_t){
      .x={{0,1,2,3},{2,2,2,2},{0,1,2,3},{2,2,2,2}},
      .y={{3,3,3,3},{0,1,2,3},{3,3,3,3},{0,1,2,3}},
  		.color = MAGENTA };
  tetimg_list[SHAPE_J] = (Image_t){
      .x={{0,1,2,2},{0,1,1,1},{0,0,1,2},{1,1,1,2}},
      .y={{3,3,3,2},{1,1,2,3},{3,2,2,2},{1,2,3,3}},
  		.color = GREEN };
  tetimg_list[SHAPE_L] = (Image_t){
      .x={{0,0,1,2},{1,2,2,2},{0,1,2,2},{1,1,1,2}},
      .y={{2,3,3,3},{3,3,2,1},{2,2,2,3},{3,2,1,1}},
  		.color = LIGHTBLUE };
  tetimg_list[SHAPE_O] = (Image_t){
      .x={{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,1,0,1}},
      .y={{3,3,2,2},{3,3,2,2},{3,3,2,2},{3,3,2,2}},
  		.color = BROWN };
  tetimg_list[SHAPE_S] = (Image_t){
      .x={{0,1,1,2},{1,1,2,2},{0,1,1,2},{1,1,2,2}},
      .y={{2,2,3,3},{3,2,2,1},{2,2,3,3},{3,2,2,1}},
  		.color = RED };
  tetimg_list[SHAPE_T] = (Image_t){
      .x={{0,1,1,2},{1,2,2,2},{0,1,1,2},{0,0,0,1}},
      .y={{3,3,2,3},{2,3,2,1},{2,3,2,2},{1,2,3,2}},
  		.color = DARKBLUE };
  tetimg_list[SHAPE_Z] = (Image_t){
      .x={{0,1,1,2},{0,0,1,1},{0,1,1,2},{0,0,1,1}},
      .y={{3,3,2,2},{1,2,2,3},{3,3,2,2},{1,2,2,3}},
  		.color = GRED };
}
