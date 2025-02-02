#include <oled.h>
#ifdef OLED_USE_BUFFER
#include <delay.h>

extern uint8_t font6x8[][6];
static uint8_t oled_buf[oled_page][oled_line];

// #define oled_sendcmd(cmd)                                  \
//   do {                                                     \
//     uint8_t init_cmd[] = {0x00, cmd};                      \
//     i2c_send(I2C1, OLED_ADDR, init_cmd, sizeof(init_cmd)); \
//   } while (0)
#define oled_sendcmd(cmd)                \
  const uint8_t cmd_command = 0x00;      \
  do {                                   \
    i2c_sendAddress(I2C1, OLED_ADDR);    \
    i2c_sendata(I2C1, &cmd_command, 1);  \
    i2c_sendata(I2C1, cmd, sizeof(cmd)); \
    i2c_stop(I2C1);                      \
  } while (0)
// #define oled_sendata(data)                           \
//   do {                                               \
//     uint8_t digit[] = {0x40, data};                  \
//     i2c_send(I2C1, OLED_ADDR, digit, sizeof(digit)); \
//   } while (0)
#define oled_sendata()                           \
  uint8_t sendata_cmd = 0x40;                    \
  do {                                           \
    for (uint8_t i = 0; i < oled_page; i++) {    \
      oled_setCursor(i, 0);                      \
      i2c_sendAddress(I2C1, OLED_ADDR);          \
      i2c_sendata(I2C1, &sendata_cmd, 1);        \
      i2c_sendata(I2C1, oled_buf[i], oled_line); \
    }                                            \
  } while (0)

void oled_init(void)
{
  i2c_config();
  // uint8_t init[] = {0x00, 0x8d, 0x14, 0xaf, 0xa5};
  // i2c_send(I2C1, OLED_ADDR, init, sizeof(init) / sizeof(init[0]));
  const uint8_t init[] = {
      0xAE,  // 关闭OLED
      0xD5,
      0x80,  // 设置显示时钟分频因子/振荡器频率
      0x20,
      0x02,  // 设置内存寻址模式
      0xA8,
      0x3F,  // 设置多路传输比率
      0xDA,
      0x12,  // 设置列引脚硬件配置
      /* ----- 方向显示配置 ----- */
      0xA1,  // 设置段重映射 (0xA1 正常)
      0xC8,  // 设置行输出扫描方向(0xC8 正常)
      /* ----- END ----- */
      0x40,  // 设置屏幕起始行
      0xD3,
      0x00,  // 设置显示偏移(not offset)
      0x81,
      0xCF,  // 设置对比度
      0xD9,
      0xF1,  // 设置预充电期间的持续时间
      0xDB,
      0x20,  // 调整VCOMH调节器的输出
      0x8D,
      0x14,  // 电荷泵设置
      0xA4,  // 全局显示开启(黑屏/亮屏) ON/OFF(A5)
      0xA6,  // 设置显示方式(正常/反显)
      0xAF   // 打开 OLED 显示
  };
  delay(100);

  // for (uint8_t i = 0; i < sizeof(init) / sizeof(init[0]); i++) {
  //   oled_sendcmd(init[i]);
  // }
  oled_sendcmd(init);
  delay(100);
}

static void oled_setCursor(uint8_t page, uint8_t x)
{
  const uint8_t cmd[] = {x & 0x0f, ((x >> 4) & 0x0f), (0xb0 | (page & 0x07))};
  oled_sendcmd(cmd);
  // const uint8_t low  = x & 0x0f;
  // const uint8_t high = (x >> 4) & 0x0f;
  // oled_sendcmd(0x00 | low);
  // oled_sendcmd(0x10 | high);

  // oled_sendcmd(0xb0 | (page & 0x07));
}
#if false
static void oled_clearRegion(uint8_t page, uint8_t from, uint8_t to)
{
  // oled_setCursor(page, from);
  for (uint8_t i = 0; i < to - from + 1; i++) {
    oled_buf[page][i + from] = 0;
  }
}

#endif

/**
 * @brief
 * @param x    range 0-15
 * @param page range 0-7
 * */
void oled_showChar(uint8_t page, uint8_t x, uint8_t c)
{
#define offset 32

  // oled_setCursor(page, x * 6);

  for (uint8_t i = 0; i < 6; i++) {
    // oled_sendata(font6x8[c - offset][i]);
    oled_buf[page][(x * 6) + i] = font6x8[c - offset][i];
  }
}

void oled_showString(uint8_t page, uint8_t x, const uint8_t* s)
{
  // oled_clearRegion(page, x, x + strlen((char*)s));
  while (*s != '\0') {
    oled_showChar(page, x++, *s);
    s++;
  }
}

static uint32_t oled_pow(uint8_t x)
{
  uint32_t ret = 1;
  for (uint8_t i = 0; i < x; i++) {
    ret *= 10;
  }
  return ret;
}

void oled_showNumber(uint8_t page, uint8_t x, uint32_t number, uint8_t length)
{
  // oled_clearRegion(page, x, x + length);
  for (uint8_t i = 0; i < length; i++) {
    uint8_t unit = number / oled_pow(length - 1 - i) % 10;
    oled_showChar(page, x + i, unit + '0');
  }
}
void oled_showImage(uint8_t page, uint8_t x, uint8_t width, uint8_t height, const uint8_t* ptr)
{
  uint8_t h            = height >> 3;
  uint8_t image_offset = 0;
  for (uint8_t j = 0; j < h; j++) {
    // oled_setCursor(page + j, x);
    for (uint8_t i = 0; i < width; i++) {
      image_offset = j * width + i;
      // oled_sendata(ptr[image_offset]);
      oled_buf[j + page][x + i] = ptr[image_offset];
    }
  }
}

void oled_clear(void)
{
  for (uint8_t j = 0; j < oled_page; j++) {
    // oled_setCursor(j, 0);
    for (uint8_t i = 0; i < oled_line; i++) {
      oled_buf[j][i] = 0;
    }
  }
}

void oled_updata(void)
{
  oled_sendata();
  // uint8_t sendata_cmd = 0x40;  //   do {
  // for (uint8_t i = 0; i < oled_page; i++) {
  //   oled_setCursor(i, 0);
  //   i2c_sendAddress(I2C1, OLED_ADDR);
  //   i2c_sendata(I2C1, &sendata_cmd, 1);
  //   i2c_sendata(I2C1, oled_buf[i], oled_line);
  // }
}

#endif
