#include "scene.h"
//#include "millis.h"
#include "button.h"
#include "game.h"
#include "ui.h"
#include <stdlib.h>
#include "stm32f1xx_it.h"

void (*scene_task)(void);

void start_scene()
{
  ;
}

void rank_scene()
{
  ;
}

void game_scene()
{
  // tetromino fall down task
  if (millis() - fall_task_stamp >= tet_fall_interval)
  {
    fall_task_stamp += tet_fall_interval;
    fall_down_task();
  }
}

void sw_game_scene()
{
  // asign button function
  k_wakeup->press_fun = tet_rotation;
  k_key0->press_fun = tet_move_right;
  k_key1->press_fun = tet_move_left;

  k_wakeup->release_fun = NULL;
  k_key0->release_fun = NULL;
  k_key1->release_fun = NULL;
  // scene_task
  scene_task = game_scene;
  fall_task_stamp = millis();
  // display
  LCD_Clear(BLACK);
  draw_bg();
  grid_render();
  draw_tetromino(0);
  draw_next_tetromino(0);
}

void sw_rank_sence()
{
  // asign button function
  k_wakeup->press_fun = NULL;
  k_key0->press_fun = NULL;
  k_key1->press_fun = NULL;

  k_wakeup->release_fun = NULL;
  k_key0->release_fun = NULL;
  k_key1->release_fun = NULL;
  // scence task
  scene_task = NULL;
  // display
  draw_rank_list();
}

void scence_switch()
{
  ;
}
