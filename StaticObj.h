#ifndef _staticObj_H_
#define _staticObj_H_

#include "Obj.h"

class StaticObj : public Obj
{
private:
    /* data */
public:
    StaticObj(const std::string &name)
    : Obj(name){

    }
    virtual ~StaticObj() override;
};

#endif