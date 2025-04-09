#ifndef _dummyObj_H_
#define _dummyObj_H_

#include "saturn.h"

class dummyObj : public DynamicObj
{
private:
    /* data */
public:
    dummyObj(const std::string &name)
    : DynamicObj(name){
        setFramePassedCallback([this](DynamicObj *obj){
            this->onFramePassed(obj);
        });
    }
    ~dummyObj();

    void onFramePassed(DynamicObj *obj){
        return;
    }
};

#endif