#ifndef _DynamicObjBase_H_
#define _DynamicObjBase_H_

/*Inherit from this class for automatic callback
 assignment*/

#include "IDynamicObj.h"

template<class Derived>
class DynamicObjBase : public DynamicObj, public IDynamicObj
{
private:
public:
    DynamicObjBase(const std::string &name)
        : DynamicObj(name)
    {
        setFramePassedCallback(
            [this](DynamicObj *obj){
                static_cast<Derived*>(this)->onFramePassed(obj);
            }
        );
        setCollisionCallback(
            [this](DynamicObj *obj, const Collision coll_info){
                static_cast<Derived*>(this)->onCollision(obj, coll_info);
            }
        );
    };
    ~DynamicObjBase() override = default;
};

#endif