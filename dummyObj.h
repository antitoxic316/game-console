#ifndef _dummyObj_H_
#define _dummyObj_H_

#include "saturn.h"

class dummyObj : public DynamicObjBase<dummyObj>
{
private:
    /* data */
public:
    dummyObj(const std::string &name)
    : DynamicObjBase(name){
    }
    ~dummyObj();

    void onFramePassed(DynamicObj *obj){
        if(obj->getX() == 64){
            obj->move(0, 0);
        } else {
            obj->move(obj->getX()+3, 0);
        }
    }

    void onCollision(DynamicObj *obj, const std::string &obj_name){
        if(obj_name == "test"){
            obj->move(0, 0);
        }
    }
};


class testObj : public DynamicObjBase<testObj>
{
private:
    /* data */
public:
    testObj(const std::string &name)
    : DynamicObjBase(name){
    }
    ~testObj();

    void onFramePassed(DynamicObj *obj){
        return;
    }

    void onCollision(DynamicObj *obj, const std::string &obj_name){
        return;
    }
};

#endif