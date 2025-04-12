#ifndef _dummyObj_H_
#define _dummyObj_H_

#include "saturn.h"

class dummyObj : public DynamicObjBase<dummyObj>
{
private:
    int x_speed = 2;
    int y_speed = 2;
public:
    dummyObj(const std::string &name)
    : DynamicObjBase(name){
    }
    ~dummyObj();

    void onFramePassed(DynamicObj *obj){
        this->move(this->getX() + x_speed, this->getY() + y_speed);
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