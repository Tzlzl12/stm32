#ifndef __SPI_H_
#define __SPI_H_

#include <stm32f4xx_spi.h>
#define SPI_SCL  GPIO_Pin_3
#define SPI_MOSI GPIO_Pin_4
#define SPI_MISO GPIO_Pin_5
#define SPI_CS   GPIO_Pin_6
void spi_config(void);

#endif
