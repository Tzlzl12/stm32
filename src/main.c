#include <stm32f4xx_gpio.h>
#include <delay.h>
#include "stm32f4xx.h"

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 启用 GPIOC 时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  // 配置 PC13 为推挽输出
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;     // 输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 50 MHz 输出速度
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;  // 无上下拉电阻
  GPIO_Init(GPIOC, &GPIO_InitStructure);             // 初始化 GPIOC
}

int main(void)
{
  GPIO_Configuration();

  while (1) {
    /* LED_On(); */
    GPIO_SetBits(GPIOC, GPIO_Pin_7);
    delay(1000);
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    delay(1000);
    /* delay(500); */
    /* LED_Off(); */
    /* delay(500); */
  }
  return 0;
}
