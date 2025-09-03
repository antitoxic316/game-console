#include "InputHandler.h"

#include <cstdint>

void InputHandler::readInput(){
    sSerial_.listen();

    uint64_t key_input_mask = 0xFFFF;
    uint64_t joystick_1_x_v_mask = 0xFF << 16;
    uint64_t joystick_1_y_v_mask = 0xFF << 24;
    uint64_t joystick_2_x_v_mask = 0xFF << 32;
    uint64_t joystick_2_y_v_mask = 0xFF << 40;
    uint32_t unpress_button_bit = 0x80000000;

    uint8_t HEADER_BYTE = 0xF2;

    if(!sSerial_.available()){
        return;
    }

    int b = sSerial_.read();
    if(b == HEADER_BYTE && !currentMessage_.gotHeader){
        currentMessage_ = {};
        currentMessage_.gotHeader = true;
        return;
    } else if (b >= 0 && currentMessage_.gotHeader) {
        currentMessage_.message |= ((uint64_t)b << (8 * currentMessage_.byte_i));
        currentMessage_.byte_i++;
        // continue to the byte_i check;
    } else {
        return;
    }

    if(currentMessage_.byte_i < 4){
        return;
    }

    uint16_t key_input = currentMessage_.message & key_input_mask;



    InputData in;
    in.key_byte = key_input;
    in.unpressed_key = currentMessage_.message & unpress_button_bit;
    in.j1_info.acc_x = (int8_t)((currentMessage_.message & joystick_1_x_v_mask) >> 16);
    in.j1_info.acc_y = (int8_t)((currentMessage_.message & joystick_1_y_v_mask) >> 24);
    in.j2_info.acc_x = (int8_t)((currentMessage_.message & joystick_2_x_v_mask) >> 32);
    in.j2_info.acc_y = (int8_t)((currentMessage_.message & joystick_2_y_v_mask) >> 40);
    
    currentMessage_ = {};
    
    this->inputQueue_.push(in);
}

std::unique_ptr<InputData> InputHandler::getInput(){
    if(inputQueue_.empty()){
        return nullptr;
    }

    InputData input = inputQueue_.front();
    
    inputQueue_.pop();

    std::unique_ptr<InputData> id_ptr = std::make_unique<InputData>(input);
    
    return id_ptr;
}