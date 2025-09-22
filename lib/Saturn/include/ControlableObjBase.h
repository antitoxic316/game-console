#ifndef _ControlableObjBase_H_
#define _ControlableObjBase_H_

/*Inherit from this class for automatic callback
 assigning*/

#include "IControlableObj.h"

template<class Derived, typename KeysEnum>
class ControlableObjBase : public ControlableObj<KeysEnum>, public IControlableObj<KeysEnum>
{
private:
public:
    ControlableObjBase(const std::string &name, std::map<uint16_t, KeysEnum> keyMap)
        :ControlableObj<KeysEnum>(name, keyMap)
    {   
        this->setKeyHeldCallback(
            [this](const KeysEnum key, const InputData i_data){
                static_cast<Derived*>(this)->onKeyHeld(key, i_data);
            }
        );
        this->setKeyPressedCallback(
            [this](const KeysEnum key, const InputData i_data){
                static_cast<Derived*>(this)->onKeyPressed(key, i_data);
            }
        );
        this->setKeyUnpressedCallback(
            [this](const KeysEnum key, const InputData i_data){
                static_cast<Derived*>(this)->onKeyUnpressed(key, i_data);
            }
        );
    }

    virtual void onKeyHeld(const KeysEnum key, const InputData i_data) override{

    }
    virtual void onKeyPressed(const KeysEnum key, const InputData i_data) override{
    
    }
    virtual void onKeyUnpressed(const KeysEnum key, const InputData i_data) override{

    }
    
    ~ControlableObjBase() override = default;
};

#endif