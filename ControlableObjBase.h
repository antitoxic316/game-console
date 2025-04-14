#ifndef _ControlableObjBase_H_
#define _ControlableObjBase_H_

/*Inherit from this class for automatic callback
 assigning*/

#include "IControlableObj.h"

template<class Derived>
class ControlableObjBase : public ControlableObj, public IControlableObj
{
private:
public:
    ControlableObjBase(const std::string name)
        :ControlableObj(name)
    {
        this->setKeyInputCallback([this](ControlableObj *obj, const ControlKeys key){
            static_cast<Derived*>(this)->onKeyInput(obj, key);
        });
    }
    ~ControlableObjBase() override = default;
};

#endif