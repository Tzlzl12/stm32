#ifndef __I2C_H_
#define __I2C_H_

#include <stm32f4xx_i2c.h>

#define I2C_SDA   GPIO_Pin_7
#define I2C_SCL   GPIO_Pin_6

#define I2C_Speed 400000

typedef enum {
  I2C_CMP,
  I2C_ADDRF,
  I2C_ACKF,
} i2c_t;

void i2c_config(void);
#ifdef OLED_USE_BUFFER
i2c_t i2c_send(I2C_TypeDef* i2cx, uint8_t address, const uint8_t* data, uint16_t size);
#endif
void  i2c_sendAddress(I2C_TypeDef* i2cx, uint8_t address);
i2c_t i2c_sendata(I2C_TypeDef* i2cx, const uint8_t* data, uint8_t length);
i2c_t i2c_stop(I2C_TypeDef* i2cx);
i2c_t i2c_receive(I2C_TypeDef* i2cx, uint8_t address, uint8_t* buf, uint16_t size);

#endif
