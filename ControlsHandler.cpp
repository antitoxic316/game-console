#include "ControlsHandler.h"

const std::unordered_map<uint8_t, DefaultControlKeys> DEFAULT_KEY_MAPPING = {
    {1, DefaultControlKeys::LEFT},
    {2, DefaultControlKeys::RIGHT},
    {4, DefaultControlKeys::UP},
    {8, DefaultControlKeys::DOWN},
};

template<typename KeysEnum>
void ControlsHandler<KeysEnum>::processInputByte(uint8_t input){
    bool unpress_command = false;

    auto key_binding = this->key_map.find(input);
    if(key_binding == this->key_map.end()){
        // check if command is reversed, then it's byte for unpressed key
        auto key_binding = this->key_map.find(!input);
        if(key_binding == this->key_map.end()){
            return;
        } else {
            unpress_command = true;
        }
    }
    if(!unpress_command){
        KeysEnum key = this->key_map.at(input);
        bool current_key_state = this->pressed_keys.at(key);
        this->pressed_keys[key] = true;
    } else {
        KeysEnum key = this->key_map.at(!input);
        bool current_key_state = this->pressed_keys.at(key);
        this->pressed_keys[key] = false;
    }
}