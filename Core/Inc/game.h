#ifndef GAME_H
#define GAME_H

#include "sys.h"

typedef struct{
  char name[10];
  uint16_t score;
}Hiscore_t;


extern Hiscore_t hiscore;
extern uint32_t tet_fall_interval; //ms
extern uint32_t fall_task_stamp;

void tet_move_left(void);
void tet_move_right(void);
void tet_fall_speedup(uint32_t);
void tet_fall_normal(void);
void tet_rotation(void);
void fall_down_task(void);
void game_reset(void);
void speed_up(uint32_t);

#endif
