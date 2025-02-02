#ifndef __KEY_H_
#define __KEY_H_

#include <stm32f4xx_gpio.h>
#include <stdbool.h>

#define KEY_PORT GPIOC
#define KEY_PIN  GPIO_Pin_6

#ifdef __KEY_EXTI_H_
void Key_Config(void);
bool key_scan(void);
#endif

#endif
