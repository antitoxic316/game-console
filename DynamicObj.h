#ifndef _dynamicObj_H_
#define _dynamicObj_H_

#include "Obj.h"

#include "functional"
#include "string"

struct Collision{
    Obj *obj;
    enum class Side { TOP, BOTTOM, LEFT, RIGHT} collision_side;
};

class DynamicObj : public Obj
{
private:
    std::function<void(const Collision coll_info)> collisionCallback;
    std::function<void()> framePassedCallback;
public:
    DynamicObj(const std::string &name);
    virtual ~DynamicObj() override;

    void onFramePassed(){
        this->framePassedCallback();
    }

    void onCollision(const Collision coll_info){
        this->collisionCallback(coll_info);
    }

    void setCollisionCallback(std::function<void(const Collision coll_info)> collisionCallback){
        this->collisionCallback = collisionCallback;
    }

    void setFramePassedCallback(std::function<void()> framePassedCallback){
        this->framePassedCallback = framePassedCallback;
    }
};

#endif