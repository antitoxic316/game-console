#ifndef _dynamicObj_H_
#define _dynamicObj_H_

#include "Obj.h"

#include <functional>
#include <string>
#include <queue>

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
    std::queue<ObjEvent> eventQueue_;
    std::function<void(const Collision)> collisionCallback;
    std::function<void()> framePassedCallback;
public:
    DynamicObj(const std::string &name)
        : Obj(name),
        collisionCallback([](const Collision coll_info) {}),
        framePassedCallback([]() {}){
    };
    virtual ~DynamicObj() = default;

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

    //TODO make this more c++ish??
    void emitEvent(const std::string &event_name, void* data);
    std::queue<ObjEvent> getEvents(){
        return this->eventQueue_;
    }
};

#endif