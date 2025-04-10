#ifndef _saturn_H_
#define _saturn_H_

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

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <ctime>

#include "staticObj.h"
#include "dynamicObj.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

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


class Saturn
{
private:
    std::vector<std::shared_ptr<StaticObj>> static_objects;
    std::vector<std::shared_ptr<DynamicObj>> dynamic_objects;

    Adafruit_SSD1306 *graph_env;

    int frame_rate = 15;
public:
    Saturn(/* args */);
    ~Saturn();

    template<typename T>
    void add_dynamicObj(const std::shared_ptr<T> &obj);

    void update_frame(void);

    void setGraphicalEnv(Adafruit_SSD1306 *graph_env);

    void start();
};

template<typename T>
void Saturn::add_dynamicObj(const std::shared_ptr<T> &obj){
    static_assert(std::is_base_of<DynamicObj, T>:: value, 
                       "Argument failed check for inheritence from DynamicObj");
    this->dynamic_objects.push_back(obj);
}

#endif