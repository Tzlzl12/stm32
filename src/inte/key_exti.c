#include <key_exti.h>
#include <stm32f4xx_rcc.h>

void Key_ExtiConfig(void)
{
  // 使能key输入
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef gpio_cfg = {
      .GPIO_Pin   = GPIO_Pin_6,
      .GPIO_PuPd  = GPIO_PuPd_UP,
      .GPIO_Mode  = GPIO_Mode_IN,
      .GPIO_Speed = GPIO_Speed_2MHz,
  };
  GPIO_Init(GPIOC, &gpio_cfg);

  // 分配EXTI线
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);

  // 配置EXTI线参数
  EXTI_InitTypeDef exti_cfg = {
      .EXTI_Line    = EXTI_Line6,
      .EXTI_Mode    = EXTI_Mode_Interrupt,
      .EXTI_Trigger = EXTI_Trigger_Rising,
      .EXTI_LineCmd = ENABLE,
  };
  EXTI_Init(&exti_cfg);

  NVIC_InitTypeDef nvic_cfg = {
      .NVIC_IRQChannel                   = EXTI9_5_IRQn,
      .NVIC_IRQChannelPreemptionPriority = 0,
      .NVIC_IRQChannelSubPriority        = 0,
      .NVIC_IRQChannelCmd                = ENABLE,
  };
  NVIC_Init(&nvic_cfg);
}
