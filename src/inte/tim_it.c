#include <tim_it.h>

void TIM3_ITConfig(void)
{
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  NVIC_InitTypeDef nvim_cfg = {
      .NVIC_IRQChannel                   = TIM3_IRQn,
      .NVIC_IRQChannelPreemptionPriority = 1,
      .NVIC_IRQChannelSubPriority        = 0,
      .NVIC_IRQChannelCmd                = ENABLE,
  };
  NVIC_Init(&nvim_cfg);
  NVIC_EnableIRQ(TIM3_IRQn);
}
