#include "DynamicObj.h"

DynamicObj::DynamicObj(const std::string &name)
    : Obj(name),
    collisionCallback([](const Collision coll_info) {}),
    framePassedCallback([]() {}){
}

DynamicObj::~DynamicObj()
{
}
