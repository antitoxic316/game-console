#ifndef _ControlsHandlers_H_
#define _ControlsHandlers_H_

#include <unordered_map>
#include <cstdint>
#include <type_traits>

#include <InputHandler.h>

template<typename KeysEnum>
class ControlsHandler
{
    static_assert(std::is_enum<KeysEnum>::value, 
                    "ControlKeysEnum must be enum");
private:
    std::unordered_map<uint16_t, KeysEnum> keyMap_;
    std::unordered_map<KeysEnum, bool> heldKeys_;
    std::unordered_map<KeysEnum, bool> pressedKeys_;
    std::unordered_map<KeysEnum, bool> unpressedKeys_;
    

    static std::unordered_map<KeysEnum, bool> 
    generatePressedKeysVector(
        std::unordered_map<uint16_t, KeysEnum> keyMap_
    );
public:
    ControlsHandler(std::unordered_map<uint16_t, KeysEnum> keyMap)
        : keyMap_(keyMap),
          heldKeys_(generatePressedKeysVector(keyMap)),
          pressedKeys_(generatePressedKeysVector(keyMap)),
          unpressedKeys_(generatePressedKeysVector(keyMap)){
    };
    ~ControlsHandler() = default;

    void setByteToKeyMap(std::unordered_map<uint16_t, KeysEnum> map){
        keyMap_ = map;
    }

    void processKeyByte(uint16_t input, bool unpressed);
    
    std::unordered_map<KeysEnum, bool> getHeldKeysState(){
        return heldKeys_;
    }
    std::unordered_map<KeysEnum, bool> getPressedKeysState(){
        return pressedKeys_;
    }
    std::unordered_map<KeysEnum, bool> getUnpressedKeysState(){
        return unpressedKeys_;
    }

    //the key still may be pressed, but callbacks for pressed keys won't be called after call
    void softUnpressKey(KeysEnum key){
        auto key_entry = pressedKeys_.find(key);
        if(key_entry == pressedKeys_.end()){
            return;
        }
        pressedKeys_[key] = false;
    }

    //the key still may be unpressed, but callbacks for unpressed keys won't be called after call
    void softPressKey(KeysEnum key){
        auto key_entry = unpressedKeys_.find(key);
        if(key_entry == unpressedKeys_.end()){
            return;
        }
        unpressedKeys_[key] = false;
    }
};

template<typename KeysEnum>
std::unordered_map<KeysEnum, bool> 
ControlsHandler<KeysEnum>::generatePressedKeysVector(std::unordered_map<uint16_t, KeysEnum> keyMap)
{
    std::unordered_map<KeysEnum, bool> heldKeys_;

    for(auto &it: keyMap){
        heldKeys_.insert({it.second, false});
    }

    return heldKeys_;
}

template<typename KeysEnum>
void ControlsHandler<KeysEnum>::processKeyByte(uint16_t input, bool unpressed){
    auto key_binding = keyMap_.find(input);
    if(key_binding == keyMap_.end()){
        return;
    }
    if(!unpressed){
        KeysEnum key = keyMap_.at(input);
        heldKeys_[key] = true;

        pressedKeys_[key] = true;
        unpressedKeys_[key] = false;
    } else {
        KeysEnum key = keyMap_.at(input);
        heldKeys_[key] = false;

        pressedKeys_[key] = false;
        unpressedKeys_[key] = true;
    }
}

#endif