#ifndef __OLED_H_
#define __OLED_H_

#define OLED_ADDR 0x78
#define OLED_USE_BUFFER
#include <i2c.h>

enum {
  oled_page = 8,
  oled_line = 128
};

enum {
  font_size = 6
};

void oled_init(void);
void oled_showChar(uint8_t page, uint8_t x, uint8_t c);
void oled_showString(uint8_t page, uint8_t x, const uint8_t* s);
void oled_showNumber(uint8_t page, uint8_t x, uint32_t number, uint8_t length);
void oled_showImage(uint8_t page, uint8_t x, uint8_t width, uint8_t height, const uint8_t* ptr);
void oled_clear(void);

#ifdef OLED_USE_BUFFER
void oled_updata(void);
#endif

void oled_test(void);
#endif
