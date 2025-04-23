#ifndef _ControlableObj_H_
#define _ControlableObj_H_

#include "DynamicObj.h"

#include "ControlsHandler.h"
#include "IControlableAbstr.h"

template<typename KeysEnum>
class ControlableObj : public IControlableAbstr, public DynamicObj
{
private:
    std::function<void(KeysEnum)> keyInputCallback;

    ControlsHandler<KeysEnum> controlsHandler;
public:
    ControlableObj(
        const std::string &name,
        std::unordered_map<uint8_t, KeysEnum> keyMap
    ) 
        : controlsHandler(keyMap),
          DynamicObj(name)
    {
        setFramePassedCallback([this](){
            this->onFramePassed();
        });
    }

    void onAbstractKeyInput(uint8_t inputByte) override {
        this->onKeyInput(inputByte);
    }

    void onKeyInput(uint8_t input_byte){
        this->controlsHandler.processInputByte(input_byte);
    }

    void onFramePassed(){
        auto key_states = this->controlsHandler.getKeysState();
        for(auto key_state: key_states){
            if(key_state.second){
                this->keyInputCallback(key_state.first);
            }
        }
    }

    void setKeyInputCallback(std::function<void(KeysEnum)> keyInputCallback){
        this->keyInputCallback = keyInputCallback;
    }

    virtual ~ControlableObj() = default;
};

#endif
