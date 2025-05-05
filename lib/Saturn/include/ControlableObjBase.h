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
    ControlableObjBase(const std::string &name, std::unordered_map<uint16_t, KeysEnum> keyMap)
        :ControlableObj<KeysEnum>(name, keyMap)
    {   
        this->setInputCallback(
            [this](const KeysEnum key, const InputData i_data){
                static_cast<Derived*>(this)->onInput(key, i_data);
            }
        );
    }
    ~ControlableObjBase() override = default;
};

#endif