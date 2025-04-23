#ifndef _IControlableAbstr_H_
#define _IControlableAbstr_H_

#include <cstdint>

#include "Obj.h"

class IControlableAbstr
{
private:
public:
    IControlableAbstr(){

    };
    virtual ~IControlableAbstr() = default;
    virtual void onAbstractKeyInput(uint8_t keyByte) = 0;
};

#endif