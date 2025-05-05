#ifndef _IControlableAbstr_H_
#define _IControlableAbstr_H_

#include <cstdint>

#include "Obj.h"
#include <InputHandler.h>

class IControlableAbstr
{
private:
public:
    IControlableAbstr(){

    };
    virtual ~IControlableAbstr() = default;
    virtual void onAbstractInput(InputData input) = 0;
};

#endif