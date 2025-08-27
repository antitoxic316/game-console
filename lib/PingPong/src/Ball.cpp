#include "Ball.h"

void Ball::onCollision(const Collision coll_info){
    const std::string objB_name = coll_info.obj->getName();
    if(objB_name == "player1" || objB_name == "player2") {
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
        y_speed *= -1;
    }
    if(objB_name == "topBorder"){
        y_speed *= -1;
    }
    if(objB_name == "leftBorder"){
        const std::string event_name = "game over";
        std::string data = "player1";
        char *c_data = strdup(data.c_str());
        this->emitEvent(event_name, (void*)(c_data));
    }
    if(objB_name == "rightBorder"){
        const std::string event_name = "game over";
        std::string data = "player2";
        char *c_data = strdup(data.c_str());
        this->emitEvent(event_name, (void*)(c_data));
    }
}