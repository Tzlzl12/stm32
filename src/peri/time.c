#include <time.h>

void TIM3_Config(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  TIM_TimeBaseInitTypeDef tim3_cfg = {
      .TIM_Prescaler         = TIM_PreScaler,
      .TIM_Period            = TIM_Reload,
      .TIM_CounterMode       = TIM_CounterMode_Up,
      .TIM_RepetitionCounter = 0,
      .TIM_ClockDivision     = TIM_CKD_DIV1,
  };

  TIM_TimeBaseInit(TIM3, &tim3_cfg);
  TIM_Cmd(TIM3, ENABLE);
}
