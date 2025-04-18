#ifndef _IConstrolableObj_H_
#define _IConstrolableObj_H_

#include "ControlableObj.h"

template<typename KeysEnum>
class IControlableObj
{
private:
    /* data */
public:
    IControlableObj(){
        
    }
    virtual ~IControlableObj() = default;
    virtual void onKeyInput(ControlableObj *obj_self, KeysEnum key) = 0;
};

#endif