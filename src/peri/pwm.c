#include <pwm.h>
#include <delay.h>

#include <stm32f4xx_gpio.h>
#include <math.h>

uint32_t Calc_digit(void)
{
  float time = (float)Get_Time() * 0.1f;

  uint32_t data = (uint32_t)((0.5 * (sin(2 * 3.14 * time) + 1)) * 1000);
  return data;
}
void PWM_Config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef pwm_cfg = {
      .GPIO_Pin   = GPIO_Pin_7,
      .GPIO_Mode  = GPIO_Mode_AF,
      .GPIO_PuPd  = GPIO_PuPd_NOPULL,
      .GPIO_Speed = GPIO_Speed_2MHz,
      .GPIO_OType = GPIO_OType_PP,
  };

  GPIO_Init(GPIOC, &pwm_cfg);

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseInitTypeDef tim8_cfg = {
      .TIM_Prescaler         = 83,   // 1us 1MHz
      .TIM_Period            = 999,  // 1ms
      .TIM_CounterMode       = TIM_CounterMode_Up,
      .TIM_ClockDivision     = TIM_CKD_DIV1,
      .TIM_RepetitionCounter = 0,
  };
  TIM_TimeBaseInit(TIM3, &tim8_cfg);
  TIM_Cmd(TIM3, ENABLE);

  TIM_OCInitTypeDef tim8_oc = {
      .TIM_OCPolarity   = TIM_OCPolarity_High,
      .TIM_OCNPolarity  = TIM_OCNPolarity_High,
      .TIM_OutputState  = TIM_OutputState_Enable,
      .TIM_OutputNState = TIM_OutputNState_Enable,
      .TIM_OCMode       = TIM_OCMode_PWM1,
      .TIM_Pulse        = 1000,
  };
  TIM_OC2Init(TIM3, &tim8_oc);
  TIM_CtrlPWMOutputs(TIM3, ENABLE);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM3, ENABLE);
}
