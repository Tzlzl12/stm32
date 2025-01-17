#ifndef __GPIO_H_
#define __GPIO_H_

#include <stm32f4xx_gpio.h>

#define LED_PIN  GPIO_Pin_7
#define LED_PORT GPIOC

void GPIO_Config(void);

#endif
