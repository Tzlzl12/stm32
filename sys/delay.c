#include "delay.h"
#include <misc.h>
#include <stdint.h>

uint32_t TimDelaying = 0;

void delay_ms(void)
{
  // 设置 SysTick 重载值，每次溢出1ms（假设系统时钟为 72 MHz）
  SysTick->LOAD = SystemCoreClock / 1000 - 1;                            // 系统时钟频率除以1000，产生1ms定时
  SysTick->VAL  = 0;                                                     // 清零计数器
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;  // 启动SysTick计时器

  // 等待直到计数器溢出
  while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) {
    // 当计数器还没溢出时，保持循环等待
  }

  SysTick->CTRL = 0;  // 停止 SysTick
}

void delay(uint32_t ms)
{
  for (uint32_t i = 0; i < ms; i++)
    delay_ms();
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1) {
  }
}
#endif

/**
 * @}
 */
