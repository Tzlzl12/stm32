#include <stm32f4xx_gpio.h>
#include <misc.h>

#include <oled.h>
#include <delay.h>
#include <gpio.h>
#include <key.h>
#include <time.h>
#include <key_exti.h>
#include <tim_it.h>
#include <pwm.h>
extern void SystemClockInit(void);

#ifdef __KEY_EXTI_H_
volatile unsigned char led_flag = 0;
#endif

int main(void)
{
  SystemClockInit();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
#ifdef TIM_IT
  TIM3_Config();
  TIM3_ITConfig();
#endif
  // PWM_Config();
  GPIO_Config();
#ifndef __KEY_EXTI_H_
  Key_Config();
#endif
  // uint16_t cnt = 0;
  oled_init();
  // oled_test();
  Key_ExtiConfig();
  oled_clear();
  oled_update();
  while (1) {
    // oled_showc(0, 0, 'A');
    // LED_SET_LOW(GPIOC, GPIO_Pin_7);
    // if (oled_test() == 0)
    //   LED_SET_LOW(GPIOC, GPIO_Pin_7);
    // else
    //   LED_SET_HIGH(GPIOC, GPIO_Pin_7);
    // if (cnt > 1000)
    //   cnt = 0;
    // else
    //   cnt++;
    // delay(10);
    // TIM_SetCompare2(TIM3, cnt);
    // LED_SET_LOW(GPIOC, GPIO_Pin_7);
    // if (!led_flag)
    //   LED_SET_HIGH(LED_PORT, LED_PIN);
    // else
    //   LED_SET_LOW(LED_PORT, LED_PIN);
    // GPIO_SetBits(GPIOC, GPIO_Pin_7);
    // LED_ON(LED_PORT, LED_PIN);
    // LED_TOGGLE(LED_PORT, LED_PIN);
    // delay(1000);
    // delay(500);
    // GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    //
    // LED_OFF(LED_PORT, LED_PIN);
    // delay(1000);
    // delay(500);
  }
  return 0;
}
