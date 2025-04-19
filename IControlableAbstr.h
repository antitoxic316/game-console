#ifndef _IControlableAbstr_H_
#define _IControlableAbstr_H_

#include <cstdint>

#include "Obj.h"

class IControlableAbstr : public Obj
{
private:
public:
    IControlableAbstr(const std::string &name) : Obj(name){

    };
    virtual ~IControlableAbstr() = default;
    virtual void onAbstractKeyInput(uint8_t keyByte) = 0;
};

#endif