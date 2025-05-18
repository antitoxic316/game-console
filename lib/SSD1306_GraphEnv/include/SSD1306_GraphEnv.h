#ifndef _SSD1306_GraphEnv_H_
#define _SSD1306_GraphEnv_H_

/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

class GraphEnv
{
private:
    uint32_t screenAdr_ = 0x3c;
    int oledReset_ = -1; // Reset pin # (or -1 if sharing Arduino reset pin)
    uint16_t hwScrW;
    uint16_t hwScrH;
    Adafruit_SSD1306 display_;
public:
    GraphEnv(uint16_t scr_w, uint16_t src_h) 
        : hwScrW(scr_w),
        hwScrH(src_h),
        display_(scr_w, src_h, &Wire, oledReset_)
    {
        this->init();
    }
    ~GraphEnv() = default;

    uint16_t getScreenW(){
        return hwScrW;
    }
    uint16_t getScreenH(){
        return hwScrH;
    }

    void init();
    void drawBitMap(int x, int y, const uint8_t *data, int w, int h);
    void drawText(int x, int y, const char *text, int size);
    void display();
    void clearDisplay();
};


#endif