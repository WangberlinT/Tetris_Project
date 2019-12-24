#include "button.h"
#include "gpio.h"

#define BUTTON_LIST_LEN 3

Button_t button_list[BUTTON_LIST_LEN];

Button_t *k_wakeup;
Button_t *k_key0;
Button_t *k_key1;

uint32_t button_scan_interval = 10; // ms

void button_init()
{
  //  KEY_Init();

  // init buttons
  k_wakeup = &button_list[0];
  k_key0 = &button_list[1];
  k_key1 = &button_list[2];
  for (uint8_t i = 0; i < BUTTON_LIST_LEN; i++)
  {
    button_list[i] = (Button_t){0, 0, 0, 0};
  }
}

void button_task()
{
  for (uint8_t i = 0; i < BUTTON_LIST_LEN; i++)
  {
    button_list[i].last_status = button_list[i].status;
    button_list[i].status = 0;
  }

  // scan normal key
  static uint8_t key0_last = 0;
  static uint8_t key1_last = 0;
  static uint8_t wakeup_last = 0;
  uint8_t key0_now = KEY0 ? 0 : 1;
  uint8_t key1_now = KEY1 ? 0 : 1;
  uint8_t wakeup_now = WK_UP;

  if (key0_now == key0_last)
  {
    k_key0->status = key0_now;
  }
  else
  {
    k_key0->status = k_key0->last_status;
  }

  if (key1_now == key1_last)
  {
    k_key1->status = key1_now;
  }
  else
  {
    k_key1->status = k_key1->last_status;
  }

  if (wakeup_now == wakeup_last)
  {
    k_wakeup->status = wakeup_now;
  }
  else
  {
    k_wakeup->status = k_wakeup->last_status;
  }

  key0_last = key0_now;
  key1_last = key1_now;
  wakeup_last = wakeup_now;

  // execute function
  for (uint8_t i = 0; i < BUTTON_LIST_LEN; i++)
  {
    Button_t *b = button_list + i;
    if (b->status == 1 && b->last_status == 0)
    {
      if (b->press_fun)
      {
        b->press_fun();
      }
    }
    if (b->status == 0 && b->last_status == 1)
    {
      if (b->release_fun)
      {
        b->release_fun();
      }
    }
  }
}
