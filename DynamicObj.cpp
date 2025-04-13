#include "DynamicObj.h"

DynamicObj::DynamicObj(const std::string &name)
    : Obj(name),
    collisionCallback([](DynamicObj*, const Collision coll_info) {}),
    framePassedCallback([](DynamicObj*) {}){
}

DynamicObj::~DynamicObj()
{
}
