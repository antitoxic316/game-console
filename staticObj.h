#ifndef _staticObj_H_
#define _staticObj_H_

#include "Obj.h"

class StaticObj : Obj
{
private:
    /* data */
public:
    StaticObj(std::string &name)
    : Obj(name){

    }
    ~StaticObj();
};

#endif