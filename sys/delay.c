#include "delay.h"
#include <misc.h>
#include <stdint.h>

uint32_t TimDelaying = 0;

void __delay_us(uint32_t us)
{
  TimDelaying = us;
  while (SysTick_Config(85));
  SysTick->CTRL |= 1;

  while (TimDelaying);
  SysTick->CTRL &= ~1;
}

void delay(uint32_t ms)
{
  for (uint32_t i = 0; i < ms; i++)
    __delay_us(1000);
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
