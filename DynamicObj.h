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
    std::function<void(DynamicObj *, const Collision coll_info)> collisionCallback;
    std::function<void(DynamicObj *)> framePassedCallback;
public:
    DynamicObj(const std::string &name);
    virtual ~DynamicObj() override;

    void onFramePassed(){
        this->framePassedCallback(this);
    }

    void onCollision(const Collision coll_info){
        this->collisionCallback(this, coll_info);
    }

    void setCollisionCallback(std::function<void(DynamicObj *, const Collision coll_info)> collisionCallback){
        this->collisionCallback = collisionCallback;
    }

    void setFramePassedCallback(std::function<void(DynamicObj *)> framePassedCallback){
        this->framePassedCallback = framePassedCallback;
    }
};

#endif