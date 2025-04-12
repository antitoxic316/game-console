#ifndef _dummyObj_H_
#define _dummyObj_H_

#include "saturn.h"

class dummyObj : public DynamicObjBase<dummyObj>
{
private:
    int x_speed = 2;
    int y_speed = 1;
public:
    dummyObj(const std::string &name)
    : DynamicObjBase(name){
    }
    ~dummyObj();

    void onFramePassed(DynamicObj *obj){
        this->move(this->getX() + x_speed, this->getY() + y_speed);
    }

    void onCollision(DynamicObj *obj, const std::string &objB_name){
        if(objB_name == "test"){
            x_speed *= -1;
            y_speed *= -1;
        }
        
        if(objB_name == "bottomBorder"){
            y_speed = -1;
        }
        if(objB_name == "topBorder"){
            y_speed = 1;
        }
        if(objB_name == "leftBorder"){
            x_speed = 1;
        }
        if(objB_name == "rightBorder"){
            x_speed = -1;
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