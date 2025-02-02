#include <stm32f4xx_rcc.h>
#include <stm32f4xx_flash.h>

void SystemClockInit(void)
{
  RCC_DeInit();
  FLASH_PrefetchBufferCmd(ENABLE);
  FLASH_SetLatency(FLASH_Latency_3);
  RCC_HSEConfig(RCC_HSE_ON);
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
  // 配置PLL 输入分8倍频, 倍频168, 输出分2倍频
  RCC_PLLConfig(RCC_PLLSource_HSE, 8, 168, 2, 7);
  RCC_PLLCmd(ENABLE);

  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while (RCC_GetSYSCLKSource() != 0x08);

  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  RCC_PCLK1Config(RCC_HCLK_Div2);
  RCC_PCLK2Config(RCC_HCLK_Div1);
}
