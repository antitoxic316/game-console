#ifndef _ControlableObj_H_
#define _ControlableObj_H_

#include "DynamicObj.h"

#include "ControlsHandler.h"
#include "IControlableAbstr.h"

template<typename KeysEnum>
class ControlableObj : public IControlableAbstr, public DynamicObj
{
private:
    std::function<void(KeysEnum, InputData)> keyHeldCallback_;
    std::function<void(KeysEnum, InputData)> keyPressedCallback_;
    std::function<void(KeysEnum, InputData)> keyUnpressedCallback_;

    ControlsHandler<KeysEnum> controlsHandler_;

    InputData currentInputData_;
public:
    ControlableObj(
        const std::string &name,
        std::map<uint16_t, KeysEnum> keyMap
    ) 
        : DynamicObj(name), 
        controlsHandler_(keyMap)
    {
        setFramePassedCallback([this](){
            this->onFramePassed();
        });
    }

    void onAbstractInput(InputData input) override {
        this->onInput(input);
    }

    void onInput(InputData input){
        currentInputData_ = input;
        controlsHandler_.processKeyByte(
            input.key_byte, input.unpressed_key
        );
    }

    void onFramePassed(){
        std::map<KeysEnum, bool> key_states;

        key_states = controlsHandler_.getHeldKeysState();
        for(auto &key_state: key_states){
            if(key_state.second){
                keyHeldCallback_(key_state.first, currentInputData_);
            }
        }
        key_states = controlsHandler_.getPressedKeysState();
        for(auto &key_state: key_states){
            if(key_state.second){
                keyPressedCallback_(key_state.first, currentInputData_);
                controlsHandler_.softUnpressKey(key_state.first);
            }
        }
        key_states = controlsHandler_.getUnpressedKeysState();
        for(auto &key_state: key_states){
            if(key_state.second){
                keyUnpressedCallback_(key_state.first, currentInputData_);
                controlsHandler_.softPressKey(key_state.first);
            }
        }
    }

    void setKeyHeldCallback(std::function<void(KeysEnum, InputData)> keyHeldCallback){
        this->keyHeldCallback_ = keyHeldCallback;
    }

    void setKeyPressedCallback(std::function<void(KeysEnum, InputData)> keyPressedCallback){
        this->keyPressedCallback_ = keyPressedCallback;
    }

    void setKeyUnpressedCallback(std::function<void(KeysEnum, InputData)> keyUnpressedCallback){
        this->keyUnpressedCallback_ = keyUnpressedCallback;
    }

    virtual ~ControlableObj() = default;
};

#endif
