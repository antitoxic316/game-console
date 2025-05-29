#ifndef _ControlableObj_H_
#define _ControlableObj_H_

#include "DynamicObj.h"

#include "ControlsHandler.h"
#include "IControlableAbstr.h"

template<typename KeysEnum>
class ControlableObj : public IControlableAbstr, public DynamicObj
{
private:
    std::function<void(KeysEnum, InputData)> keyInputCallback;

    ControlsHandler<KeysEnum> controlsHandler_;

    InputData currentInputData_;
public:
    ControlableObj(
        const std::string &name,
        std::unordered_map<uint16_t, KeysEnum> keyMap
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
        this->controlsHandler_.processKeyByte(
            input.key_byte, input.unpressed_key
        );
    }

    void onFramePassed(){
        std::unordered_map<KeysEnum, bool> key_states = controlsHandler_.getKeysState();
        for(auto key_state: key_states){
            if(key_state.second){
                this->keyInputCallback(key_state.first, currentInputData_);
            }
        }
    }

    void setInputCallback(std::function<void(KeysEnum, InputData)> keyInputCallback){
        this->keyInputCallback = keyInputCallback;
    }

    virtual ~ControlableObj() = default;
};

#endif
