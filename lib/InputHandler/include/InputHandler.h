#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include "I_InputHandler.h"

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>

#include <queue>

struct JoystickInfo{
    int8_t acc_x;
    int8_t acc_y;
};

struct InputData{
    uint16_t key_byte;
    bool unpressed_key;
    JoystickInfo j1_info;
    JoystickInfo j2_info;
};

struct SerialMessageState {
    int byte_i;
    long long message;
    bool gotHeader;
};


enum PControlKeys {
    LEFT, RIGHT, UP, DOWN, X, Y, B, A
};

const std::unordered_map<uint16_t, PControlKeys> DEFAULT_KEY_MAPPING = {
    {1, PControlKeys::LEFT},
    {2, PControlKeys::RIGHT},
    {4, PControlKeys::UP},
    {8, PControlKeys::DOWN},
    {16, PControlKeys::X},
    {32, PControlKeys::Y},
    {64, PControlKeys::B},
    {128, PControlKeys::A}
};

class InputHandler : I_InputHandler
{
private:
    std::queue<InputData> inputQueue_;
    SoftwareSerial& sSerial_;

    SerialMessageState currentMessage_ = {};
public:
    InputHandler(SoftwareSerial &s) 
    : sSerial_(s)
    {
        sSerial_.begin(9600);
        delay(100);

        Serial.begin(19200);
        delay(100); 
    };
    ~InputHandler() = default;

    void readInput();
    InputData getInput();
};


#endif