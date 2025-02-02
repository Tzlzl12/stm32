#include <gpio.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

void GPIO_Config(void)
{
  GPIO_InitTypeDef gpio_cfg;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  gpio_cfg.GPIO_Mode  = GPIO_Mode_OUT;
  gpio_cfg.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  gpio_cfg.GPIO_Pin   = LED_PIN;
  gpio_cfg.GPIO_OType = GPIO_OType_PP;
  gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(LED_PORT, &gpio_cfg);

  LED_SET_HIGH(LED_PORT, LED_PIN);  // 使led灯默认处于熄灭
}
