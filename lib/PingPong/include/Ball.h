#pragma once

#include <Saturn.h>

class Ball : public DynamicObjBase<Ball>
{
private:
    int x_speed = 2;
    int y_speed = 2;
public:
    Ball(const std::string &name)
    : DynamicObjBase(name){
    }
    ~Ball() = default;

    void onFramePassed(){
        this->move(this->getX() + x_speed, this->getY() + y_speed);
    }

    void onCollision(const Collision coll_info);
};