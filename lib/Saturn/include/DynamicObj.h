#ifndef _dynamicObj_H_
#define _dynamicObj_H_

#include "Obj.h"

#include <functional>
#include <string>
#include <queue>
#include <list>

struct Vec2
{
    int x;
    int y;
};

struct Collision{
    Obj *obj;
    enum class Side { TOP, BOTTOM, LEFT, RIGHT} collision_side;
    Vec2 penetrationDepth;
};

struct ObjEvent {
    const std::string ev_name;
    void *data;
};

class DynamicObj : public Obj
{
private:
    std::queue<ObjEvent, std::list<ObjEvent>> eventQueue_;
    std::function<void(const Collision)> collisionCallback_;
    std::function<void()> framePassedCallback_;
public:
    DynamicObj(const std::string &name)
        : Obj(name),
        collisionCallback_([](const Collision coll_info) {}),
        framePassedCallback_([]() {}){
    };

    void onFramePassed(){
        this->framePassedCallback_();
    }

    void onCollision(const Collision coll_info){
        this->collisionCallback_(coll_info);
    }

    void setCollisionCallback(std::function<void(const Collision coll_info)> collisionCallback_){
        this->collisionCallback_ = collisionCallback_;
    }

    void setFramePassedCallback(std::function<void()> framePassedCallback_){
        this->framePassedCallback_ = framePassedCallback_;
    }

    //TODO make this more c++ish??
    void emitEvent(const std::string &event_name, void* data);
    std::queue<ObjEvent, std::list<ObjEvent>> *getEvents(){
        return &eventQueue_;
    }
};

#endif