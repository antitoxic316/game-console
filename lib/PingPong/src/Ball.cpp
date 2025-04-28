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
        // call event for restarting game
        const std::string &event_name = "game over";
        char *data = "player1";
        this->emitEvent(event_name, (void*)data);
    }
    if(objB_name == "rightBorder"){
        // restart game here
    }
}