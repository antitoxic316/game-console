#include "dynamicObj.h"

DynamicObj::DynamicObj(const std::string &name)
    : Obj(name),
    collisionCallback([](DynamicObj*, const std::string&) {}),
    framePassedCallback([](DynamicObj*) {}){
}

DynamicObj::~DynamicObj()
{
}
