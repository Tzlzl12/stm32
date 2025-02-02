#include <usart.h>

#include <stm32f4xx_rcc.h>

static void USART_GPIO_Config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef gpio_cfg = {
      .GPIO_Pin   = GPIO_Pin_9,
      .GPIO_Mode  = GPIO_Mode_AF,
      .GPIO_PuPd  = GPIO_PuPd_NOPULL,
      .GPIO_Speed = GPIO_Speed_25MHz,
      .GPIO_OType = GPIO_OType_PP,
  };
  GPIO_Init(GPIOA, &gpio_cfg);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

  gpio_cfg.GPIO_Pin  = GPIO_Pin_10;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &gpio_cfg);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
}

void USART_Config(void)
{
  USART_GPIO_Config();
  USART_InitTypeDef usart_cfg = {
      .USART_BaudRate            = 115200,
      .USART_Parity              = USART_Parity_No,
      .USART_WordLength          = USART_WordLength_8b,
      .USART_Mode                = USART_Mode_Rx | USART_Mode_Tx,
      .USART_StopBits            = USART_StopBits_1,
      .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
  };
  USART_Init(USART1, &usart_cfg);
  USART_Cmd(USART1, ENABLE);
}

void USART_SendBytes(USART_TypeDef* USARTx, uint16_t* bytes, uint8_t size)
{
  for (uint8_t i = 0; i < size; i++) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, bytes[i]);
  }
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC));
}
