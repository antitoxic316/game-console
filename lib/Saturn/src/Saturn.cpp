#include "Saturn.h"

#include <cmath>
#include <secrets.h>

Saturn::Saturn(GraphEnv &graph_env, SoftwareSerial &controllerInput)
: graphEnv_(graph_env),
inputHandler_(controllerInput)
{
};

void Saturn::update_frame(void){
    graphEnv_.clearDisplay();

    //user input handling
    processInput();

    //drawing objects
    for(auto &obj: dynamicObjects_) {
        obj->onFramePassed();
        obj->drawCallback(graphEnv_);

        //object custom events handling(for example game over event in ping pong)
        handleEvents(obj.get());

        //object collisions resolvment
        if(!handleColisions_){
            continue;
        }
        auto obj_colls = getObjectCollisions(obj.get());
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

    // drawing buffer to display
    graphEnv_.display();
}

void Saturn::processInput(){
    std::unique_ptr<InputData> input = inputHandler_.getInput();
    if(input == nullptr) return;
    for(auto &obj: controlableObjects_){
        obj->onAbstractInput(*input);
    }
}

std::unique_ptr<std::vector<Collision>> Saturn::getObjectCollisions(DynamicObj *obj){
    auto collided_objs = std::make_unique<std::vector<Collision>>();
    
    for(auto &dynamic_obj_p: dynamicObjects_){
        if(dynamic_obj_p.get()->getName() == obj->getName()){
            continue;
        }
        if(areObjectsCollided(obj, dynamic_obj_p.get())){
            Collision coll_info = getCollisionInfo(obj, dynamic_obj_p.get());
            collided_objs->push_back(coll_info);
        }
    }

    for(auto &static_obj_p: staticObjects_){
        if(areObjectsCollided(obj, static_obj_p.get())){
            Collision coll_info = getCollisionInfo(obj, static_obj_p.get());
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

void Saturn::run(){
    ulong start_time = millis();


    //nh_.WPA2Connect(ssid, pass);
    //nh_.gameSyncInit();

    while(true){
        if(isInterrupted()){
            return;
        }

        inputHandler_.readInput();
        //nh_.syncServer();

        ulong current_time = millis();
        if((current_time - start_time) > 1000ul/frame_rate){
            start_time = current_time;
            update_frame();
        }
        delay(1);
    }
}

void Saturn::clearObjects(){
   staticObjects_.clear();
   dynamicObjects_.clear();
   controlableObjects_.clear(); 

   nh_.clearObjects();
}

void Saturn::handleEvents(DynamicObj* obj){
    std::queue<ObjEvent> *emmitedEvents = obj->getEvents();

    for(; !emmitedEvents->empty(); emmitedEvents->pop()){
        std::string ev_name = emmitedEvents->front().ev_name;
        auto handler_entry = eventHandlers_.find(ev_name);
        if(handler_entry == eventHandlers_.end()){
            return;
        }

        std::function<void(void*)> event_f = handler_entry->second;
        event_f(emmitedEvents->front().data);
    }
}