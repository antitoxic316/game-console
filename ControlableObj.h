#ifndef _ControlableObj_H_
#define _ControlableObj_H_

#include "DynamicObj.h"

class ControlableObj : public DynamicObj
{
private:
    /* data */
public:
    ControlableObj(const std::string &name) 
        : DynamicObj(name){
    };
    virtual ~ControlableObj() override;
};

#endif
