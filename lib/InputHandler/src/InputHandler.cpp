#include "InputHandler.h"

#include <cstdint>

void InputHandler::readInput(){
    long long key_input_mask = 0xFFFF;
    long long joystick_1_x_v_mask = 0xFF << 16;
    long long joystick_1_y_v_mask = 0xFF << 24;
    long long joystick_2_x_v_mask = 0xFF << 32;
    long long joystick_2_y_v_mask = 0xFF << 40;
    long long unpress_button_bit = 1 << 62;

    uint8_t HEADER_BYTE = 0xF2;

    int b = sSerial.read();
    if(b == HEADER_BYTE && !currentMessage_.gotHeader){
        currentMessage_ = {};
        currentMessage_.gotHeader = true;
        return;
    } else if (b >= 0 && currentMessage_.gotHeader) {
        currentMessage_.message |= ((long long)b << (8 * currentMessage_.byte_i));
        currentMessage_.byte_i++;
        // continue to the byte_i check;
        Serial.println(currentMessage_.message);
    } else {
        return;
    }

    if(currentMessage_.byte_i < 7){
        return;
    }
    
    uint16_t key_input = currentMessage_.message & key_input_mask;
    Serial.println(currentMessage_.message);

    InputData in;
    in.key_byte = key_input;
    in.unpressed_key = currentMessage_.message & unpress_button_bit;
    in.j1_info.acc_x = (int8_t)(currentMessage_.message & joystick_1_x_v_mask);
    in.j1_info.acc_y = (int8_t)(currentMessage_.message & joystick_1_y_v_mask);
    in.j2_info.acc_x = (int8_t)(currentMessage_.message & joystick_2_x_v_mask);
    in.j2_info.acc_y = (int8_t)(currentMessage_.message & joystick_2_y_v_mask);
    
    currentMessage_ = {};
    
    this->inputQueue.push(in);
}

InputData InputHandler::getInput(){
    InputData input = this->inputQueue.front();
    if(!input.key_byte){
        return input;
    }
    this->inputQueue.pop();
    return input;
}