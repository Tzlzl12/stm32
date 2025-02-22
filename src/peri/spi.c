#include <spi.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
static void spi_gpio_config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef gpio_cfg = {
      .GPIO_OType = GPIO_OType_PP,
      .GPIO_PuPd  = GPIO_PuPd_NOPULL,
      .GPIO_Pin   = SPI_SCL,
      .GPIO_Mode  = GPIO_Mode_AF,
      .GPIO_Speed = GPIO_Speed_2MHz,
  };

  GPIO_Init(GPIOB, &gpio_cfg);

  gpio_cfg.GPIO_Pin = SPI_MOSI;
  GPIO_Init(GPIOB, &gpio_cfg);

  gpio_cfg.GPIO_Pin  = SPI_MISO;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &gpio_cfg);

  gpio_cfg.GPIO_Pin  = SPI_CS;
  gpio_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpio_cfg.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOB, &gpio_cfg);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_SPI1);
}
void spi_config(void)
{
  spi_gpio_config();
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
}
