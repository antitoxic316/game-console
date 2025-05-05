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

class InputHandler : I_InputHandler
{
private:
    std::queue<InputData> inputQueue;
    SoftwareSerial sSerial = SoftwareSerial(0, 1);

    SerialMessageState currentMessage_ = {};
public:
    InputHandler(){
        sSerial.begin(9600);
        delay(100);

        Serial.begin(19200);
        delay(100);
    };
    ~InputHandler() = default;

    void readInput();
    InputData getInput();
};


#endif