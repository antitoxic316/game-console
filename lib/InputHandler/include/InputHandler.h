#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include "I_InputHandler.h"

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>

#include <queue>

class InputHandler : I_InputHandler
{
private:
    std::queue<uint8_t> inputQueue;
    SoftwareSerial sSerial = SoftwareSerial(0, 1);
public:
    InputHandler(){
        sSerial.begin(9600);
        delay(100);
    };
    ~InputHandler() = default;

    void readInput();
    uint8_t getInputByte();
};


#endif