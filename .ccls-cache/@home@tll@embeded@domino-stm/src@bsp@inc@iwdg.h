#ifndef __IWDG_H_
#define __IWDG_H_

#include <stm32f4xx_iwdg.h>
#define IWDG_FeedDog()   \
  do {                   \
    IWDG_ReloadCounter() \
  } while (0)

void IWDG_Config();

#endif
