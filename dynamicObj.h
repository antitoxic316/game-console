#ifndef _dynamicObj_H_
#define _dynamicObj_H_

#include "Obj.h"

#include "functional"
#include "string"

class DynamicObj : public Obj
{
private:
    std::function<void(DynamicObj *, const std::string&)> collisionCallback;
    std::function<void(DynamicObj *)> framePassedCallback;
public:
    explicit DynamicObj(const std::string &name);
    virtual ~DynamicObj() override;

    void onFramePassed(){
        this->framePassedCallback(this);
    }

    void onCollision(const std::string& obj_name){
        this->collisionCallback(this, obj_name);
    }

    void setCollisionCallback(std::function<void(DynamicObj *, const std::string&)> collisionCallback){
        this->collisionCallback = collisionCallback;
    }

    void setFramePassedCallback(std::function<void(DynamicObj *)> framePassedCallback){
        this->framePassedCallback = framePassedCallback;
    }
};

#endif