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
    ControlableObjBase(const std::string &name, std::unordered_map<uint8_t, KeysEnum> keyMap)
        :ControlableObj<KeysEnum>(name, keyMap)
    {   
        this->setKeyInputCallback(
            [this](const KeysEnum key){
                static_cast<Derived*>(this)->onKeyInput(key);
            }
        );
    }
    ~ControlableObjBase() override = default;
};

#endif