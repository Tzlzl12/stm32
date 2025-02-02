#include <key.h>
#include <delay.h>
#include <stm32f4xx_rcc.h>

void Key_Config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef gpio_cfg = {
      .GPIO_Pin   = KEY_PIN,
      .GPIO_Mode  = GPIO_Mode_IN,
      .GPIO_PuPd  = GPIO_PuPd_UP,
      .GPIO_Speed = GPIO_Speed_2MHz};

  GPIO_Init(KEY_PORT, &gpio_cfg);
}

bool key_scan(void)
{
  bool flag = false;
  if (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET) {
    delay(20);
    if (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET)
      flag = true;
  } else {
    flag = false;
  }
  return flag;
}
