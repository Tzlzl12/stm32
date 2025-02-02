#ifndef __GPIO_H_
#define __GPIO_H_

#include <stm32f4xx_gpio.h>

#define LED_PIN  GPIO_Pin_7
#define LED_PORT GPIOC

#define LED_SET_LOW(GPIOx, GPIO_Pin) \
  do {                               \
    GPIOx->BSRR |= (GPIO_Pin << 16); \
  } while (0)

#define LED_SET_HIGH(GPIOx, GPIO_Pin) \
  do {                                \
    GPIOx->BSRR |= GPIO_Pin;          \
  } while (0)

#define LED_TOGGLE(GPIOx, GPIO_Pin) \
  do {                              \
    GPIOx->ODR ^= GPIO_Pin;         \
  } while (0)

void GPIO_Config(void);

#endif
