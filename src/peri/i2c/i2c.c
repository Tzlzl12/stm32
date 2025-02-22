#include <i2c.h>

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

static uint8_t precious_address = 0;
static void    i2c_gpio_config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef gpio_cfg = {
      .GPIO_OType = GPIO_OType_OD,
      .GPIO_PuPd  = GPIO_PuPd_NOPULL,
      .GPIO_Mode  = GPIO_Mode_AF,
      .GPIO_Speed = GPIO_Speed_2MHz,
      .GPIO_Pin   = I2C_SDA | I2C_SCL,
  };

  GPIO_Init(GPIOB, &gpio_cfg);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
}

void i2c_config(void)
{
  i2c_gpio_config();
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  I2C_InitTypeDef i2c_cfg = {
      .I2C_ClockSpeed = I2C_Speed,
      .I2C_DutyCycle  = I2C_DutyCycle_2,
      .I2C_Mode       = I2C_Mode_I2C,
      .I2C_Ack        = I2C_Ack_Enable,
  };
  I2C_Init(I2C1, &i2c_cfg);
  I2C_Cmd(I2C1, ENABLE);
}

void i2c_sendAddress(I2C_TypeDef* i2cx, uint8_t address)
{
  if (address != precious_address) {
    while (I2C_GetFlagStatus(i2cx, I2C_FLAG_BUSY) == SET);
    // while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
    precious_address = address;
  }
  I2C_GenerateSTART(i2cx, ENABLE);
  while (I2C_GetFlagStatus(i2cx, I2C_FLAG_SB) != SET);

  I2C_ClearFlag(i2cx, I2C_FLAG_AF);
  I2C_Send7bitAddress(i2cx, address, I2C_Direction_Transmitter);

  while (I2C_GetFlagStatus(i2cx, I2C_FLAG_ADDR) != SET);
  // clear addr register
  I2C_ReadRegister(i2cx, I2C_Register_SR1);
  I2C_ReadRegister(i2cx, I2C_Register_SR2);
}
i2c_t i2c_sendata(I2C_TypeDef* i2cx, const uint8_t* data, uint8_t length)
{
  for (uint16_t i = 0; i < length; i++) {
    I2C_SendData(i2cx, data[i]);
    while (1) {
      if (I2C_GetFlagStatus(i2cx, I2C_FLAG_AF) == SET)
        return I2C_ACKF;
      if (I2C_GetFlagStatus(i2cx, I2C_FLAG_TXE) == SET)
        break;
    }
  }
  while (I2C_GetFlagStatus(i2cx, I2C_FLAG_BTF) != SET);
  return I2C_CMP;
}
i2c_t i2c_stop(I2C_TypeDef* i2cx)
{
  I2C_GenerateSTOP(i2cx, ENABLE);
  return I2C_CMP;
}
i2c_t i2c_send(I2C_TypeDef* i2cx, uint8_t address, const uint8_t* data, uint16_t size)
{
  if (address != precious_address) {
    while (I2C_GetFlagStatus(i2cx, I2C_FLAG_BUSY) == SET);
    // while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
    precious_address = address;
  }
  I2C_GenerateSTART(i2cx, ENABLE);
  while (I2C_GetFlagStatus(i2cx, I2C_FLAG_SB) != SET);

  I2C_ClearFlag(i2cx, I2C_FLAG_AF);
  I2C_Send7bitAddress(i2cx, address, I2C_Direction_Transmitter);

  while (I2C_GetFlagStatus(i2cx, I2C_FLAG_ADDR) != SET);
  // clear addr register
  I2C_ReadRegister(i2cx, I2C_Register_SR1);
  I2C_ReadRegister(i2cx, I2C_Register_SR2);

  for (uint16_t i = 0; i < size; i++) {
    while (1) {
      if (I2C_GetFlagStatus(i2cx, I2C_FLAG_AF) == SET)
        return I2C_ACKF;
      if (I2C_GetFlagStatus(i2cx, I2C_FLAG_TXE) == SET)
        break;
    }
    I2C_SendData(i2cx, data[i]);
  }
  while (I2C_GetFlagStatus(i2cx, I2C_FLAG_BTF) != SET);
  I2C_GenerateSTOP(i2cx, ENABLE);
  return I2C_CMP;
}

i2c_t i2c_receive(I2C_TypeDef* i2cx, uint8_t address, uint8_t* buf, uint16_t size)
{
  if (precious_address != address) {
    // wait for i2c bus empty
    while (I2C_GetFlagStatus(i2cx, I2C_FLAG_BUSY) == SET);
    // while (I2C_CheckEvent(i2cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
    precious_address = address;
  }
  I2C_GenerateSTART(i2cx, ENABLE);
  while (I2C_GetFlagStatus(i2cx, I2C_FLAG_SB) != SET);

  I2C_Send7bitAddress(i2cx, address, I2C_Direction_Receiver);

  // clear addr register
  I2C_ReadRegister(i2cx, I2C_Register_SR1);
  I2C_ReadRegister(i2cx, I2C_Register_SR2);

  // get the data except the last data
  uint16_t size_except_last = size - 1;
  for (uint16_t i = 0; i < size_except_last; i++) {
    I2C_AcknowledgeConfig(i2cx, ENABLE);
    while (I2C_GetFlagStatus(i2cx, I2C_FLAG_RXNE) != SET);

    buf[i] = I2C_ReceiveData(i2cx);
  }

  /**
   * last data
   * pull up sda(no ack) and generaate stop
   */
  I2C_AcknowledgeConfig(i2cx, DISABLE);
  I2C_GenerateSTOP(i2cx, ENABLE);

  while (I2C_GetFlagStatus(i2cx, I2C_FLAG_RXNE) != SET);
  buf[size - 1] = I2C_ReceiveData(i2cx);
  return I2C_CMP;
}
