#ifndef _IDynamicObj_H_
#define _IDynamicObj_H_

#include "DynamicObj.h"

class IDynamicObj
{
private:
public:
    IDynamicObj(){

    }
    virtual ~IDynamicObj() = default;
    virtual void onFramePassed(DynamicObj *obj) = 0;
    virtual void onCollision(DynamicObj*, Collision coll_info) = 0;
};

#endif