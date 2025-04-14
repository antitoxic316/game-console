#ifndef _IConstrolableObj_H_
#define _IConstrolableObj_H_

#include "ControlableObj.h"

class IControlableObj
{
private:
    /* data */
public:
    IControlableObj(){
        
    }
    virtual ~IControlableObj() = default;
    virtual void onKeyInput(ControlableObj *obj_self, ControlKeys key) = 0;
};

#endif