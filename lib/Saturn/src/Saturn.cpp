#include "Saturn.h"

#include <cmath>

void Saturn::update_frame(void){
    this->graph_env.clearDisplay();

    this->processInput();

    for(auto &obj: this->dynamic_objects) {
        obj->onFramePassed();
        if(!obj->getBitmap()){
            goto skip_drawing_object;
        }
        this->graph_env.drawBitMap(
            obj->getX(), obj->getY(),
            obj->getBitmap(),
            obj->getWidth(), obj->getHeight()
        );
skip_drawing_object:

        this->handleEvents(obj.get());

        auto obj_colls = this->getObjectCollisions(obj.get());

        if(!obj_colls){
            continue;
        }

        for(auto obj_collision: *obj_colls){
            if(obj_collision.obj->isMovable() && obj->isMovable()){
                double dispositionX = (double)obj_collision.penetrationDepth.x / 2.0;
                if (dispositionX < 0){
                    dispositionX = std::floor(dispositionX);
                } else if (dispositionX > 0) {
                    dispositionX = std::ceil(dispositionX);
                }
                double dispositionY = (double)obj_collision.penetrationDepth.y / 2.0;
                if (dispositionY < 0){
                    dispositionY = std::floor(dispositionY);
                } else if (dispositionY > 0) {
                    dispositionY = std::ceil(dispositionY);
                }
                obj->move(
                    obj->getX() + dispositionX,
                    obj->getY() + dispositionY
                );
            }
            obj->onCollision(obj_collision);
        }
    }

    this->graph_env.display();
}

void Saturn::processInput(){
    InputData input = this->inputHandler_.getInput();
    if(!input.key_byte){
        return;
    }
    for(auto &obj: this->controlable_objects){
        obj->onAbstractInput(input);
    }
}

std::unique_ptr<std::vector<Collision>> Saturn::getObjectCollisions(DynamicObj *obj){
    auto collided_objs = std::make_unique<std::vector<Collision>>();
    
    for(auto &dynamic_obj_p: this->dynamic_objects){
        if(dynamic_obj_p.get()->getName() == obj->getName()){
            continue;
        }
        if(this->areObjectsCollided(obj, dynamic_obj_p.get())){
            Collision coll_info = this->getCollisionInfo(obj, dynamic_obj_p.get());
            collided_objs->push_back(coll_info);
        }
    }

    for(auto &static_obj_p: this->static_objects){
        if(this->areObjectsCollided(obj, static_obj_p.get())){
            Collision coll_info = this->getCollisionInfo(obj, static_obj_p.get());
            collided_objs->push_back(coll_info);
        }
    }

    return collided_objs;
}

bool Saturn::areObjectsCollided(Obj *objA, Obj *objB){
    //top left corner is x=0, y=0

    int objALeftBorder = objA->getX();
    int objARightBorder = objA->getX() + objA->getWidth();
    int objATopBorder = objA->getY();
    int objABottomBorder = objA->getY() + objA->getHeight();
    
    int objBLeftBorder = objB->getX();
    int objBRightBorder = objB->getX() + objB->getWidth();
    int objBTopBorder = objB->getY();
    int objBBottomBorder = objB->getY() + objB->getHeight();

    bool x_aligned = false;
    bool y_aligned = false;

    if(objARightBorder >= objBLeftBorder && objALeftBorder <= objBRightBorder){
        x_aligned = true;
    }
    if(objABottomBorder >= objBTopBorder && objATopBorder <= objBBottomBorder){
        y_aligned = true;
    }

    return x_aligned && y_aligned;
}

Collision Saturn::getCollisionInfo(Obj *objA, Obj *objB){
    Collision coll_info;

    int objALeftBorder = objA->getX();
    int objARightBorder = objA->getX() + objA->getWidth();
    int objATopBorder = objA->getY();
    int objABottomBorder = objA->getY() + objA->getHeight();
    
    int objBLeftBorder = objB->getX();
    int objBRightBorder = objB->getX() + objB->getWidth();
    int objBTopBorder = objB->getY();
    int objBBottomBorder = objB->getY() + objB->getHeight();

    coll_info.obj = objB;

    int overlapX = std::min(objARightBorder, objBRightBorder) - std::max(objALeftBorder, objBLeftBorder);
    int overlapY = std::min(objABottomBorder, objBBottomBorder) - std::max(objATopBorder, objBTopBorder);

    int objACenterX = (objALeftBorder + objARightBorder) / 2;
    int objACenterY = (objATopBorder + objABottomBorder) / 2;
    int objBCenterX = (objBLeftBorder + objBRightBorder) / 2;
    int objBCenterY = (objBTopBorder + objBBottomBorder) / 2;

    if (overlapX < overlapY) {
        if(objACenterX < objBCenterX){
            coll_info.collision_side = Collision::Side::RIGHT;
            coll_info.penetrationDepth.x = -overlapX;
        } else {
            coll_info.collision_side = Collision::Side::LEFT;
            coll_info.penetrationDepth.x = overlapX;
        }
        coll_info.penetrationDepth.y = 0;
    } else {
        if(objACenterY < objBCenterY) {
            coll_info.collision_side = Collision::Side::BOTTOM;
            coll_info.penetrationDepth.y = -overlapY;
        } else {
            coll_info.collision_side = Collision::Side::TOP;
            coll_info.penetrationDepth.y = overlapY;
        }
        coll_info.penetrationDepth.x = 0;
    }

    return coll_info;
}

void Saturn::start(){
    ulong start_time = millis();

    while(true){
        this->inputHandler_.readInput();

        ulong current_time = millis();
        if((current_time - start_time) > 1000/this->frame_rate){
            start_time = current_time;
            this->update_frame();    
        }
        delay(1);
    }
}

//TODO make more advanced engine restart function
void Saturn::clear(){
    this->static_objects.clear();
    this->dynamic_objects.clear();
}