#ifndef _ControlableObj_H_
#define _ControlableObj_H_

#include "DynamicObj.h"

#include "ControlsHandler.h"

template<typename KeysEnum>
class ControlableObj : public Obj
{
private:
    std::function<void(ControlableObj *, KeysEnum)> keyInputCallback;

    ControlsHandler<KeysEnum> controlsHandler;
public:
    ControlableObj(
        const std::string &name,
        std::unordered_map<uint8_t, KeysEnum> &keyMap
    ) 
        : Obj(name),
          controlsHandler(keyMap){
    };

    void onKeyInput(uint8_t input_byte){
        this->controlsHandler.processInputByte(input_byte);
        auto key_states = this->controlsHandler.getKeysState();
        for(auto key: key_states){
            if(key){
                this->keyInputCallback(this, key);
            }
        }
    }

    void setKeyInputCallback(std::function<void(ControlableObj*, KeysEnum)> keyInputCallback){
        this->keyInputCallback = keyInputCallback;
    }

    virtual ~ControlableObj() override;
};

#endif
