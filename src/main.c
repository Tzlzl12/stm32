#include <stm32f4xx_gpio.h>

int main(void)
{
  GPIO_InitTypeDef gpio_cfg;
  gpio_cfg.GPIO_Pin   = GPIO_Pin_10;
  gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;
  return 0;
}
