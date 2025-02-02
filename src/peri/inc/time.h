#ifndef __TIME_H_
#define __TIME_H_

#include <stm32f4xx_tim.h>

#define TIM_PreScaler 83
#define TIM_Reload    999  // 1ms重装载一次

void TIM3_Config(void);

#endif
