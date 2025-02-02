#ifndef __USART_H_
#define __USART_H_
#include <stm32f4xx_usart.h>
#define SIZE_OF(arr) {sizeof(arr) / sizeof(arr[0])}

void USART_Config(void);
void USART_SendBytes(USART_TypeDef* USARTx, uint16_t* bytes, uint8_t size);
#endif
