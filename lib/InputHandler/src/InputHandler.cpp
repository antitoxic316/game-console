#include "InputHandler.h"

#include <cstdint>

void InputHandler::readInput(){
    int b_control = sSerial.read();
        if(b_control > 0){
            this->inputQueue.push((uint8_t)b_control);
        }
}

uint8_t InputHandler::getInputByte(){
    uint8_t input = this->inputQueue.front();
    if(!input){
        return 0;
    }
    this->inputQueue.pop();
    return input;
}