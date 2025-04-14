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

    void onFramePassed(DynamicObj *self_obj){
        this->move(this->getX() + x_speed, this->getY() + y_speed);
    }

    void onCollision(DynamicObj *self_obj, const Collision coll_info){
        const std::string objB_name = coll_info.obj->getName();

        if(objB_name == "player") {
            if(coll_info.collision_side == Collision::Side::LEFT || 
            coll_info.collision_side == Collision::Side::RIGHT) {
                x_speed *= -1;
            }
            if(coll_info.collision_side == Collision::Side::TOP || 
            coll_info.collision_side == Collision::Side::BOTTOM) {
                y_speed *= -1;
            }
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

#endif