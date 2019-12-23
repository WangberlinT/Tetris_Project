#ifndef BUTTON_H
#define BUTTON_H

#include "sys.h"

typedef struct{
  uint8_t status;
  uint8_t last_status;
  void (*press_fun)(void);
  void (*release_fun)(void);
}Button_t;


extern Button_t *k_wakeup;
extern Button_t *k_key0;
extern Button_t *k_key1;


#define KEY0  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5)
#define KEY1  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15)
#define WK_UP HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)


#define KEY0_PRES	1		//KEY0
#define KEY1_PRES	2		//KEY1
#define WKUP_PRES	3		//WK_UP


extern uint32_t button_scan_interval;

void button_init(void);
void button_task(void);

#endif
