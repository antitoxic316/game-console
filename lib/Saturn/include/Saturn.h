#ifndef _saturn_H_
#define _saturn_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <ctime>
#include <queue>
#include <any>

#include "StaticObj.h"
#include "DynamicObjBase.h"
#include "ControlableObjBase.h"

#include <InputHandler.h>
#include <NetworkHandler.h>
#include <Program.h>
#include <SSD1306_GraphEnv.h>


class Saturn : public Program
{
private:
    std::vector<std::shared_ptr<IControlableAbstr>> controlableObjects_;

    std::vector<std::shared_ptr<StaticObj>> staticObjects_;
    std::vector<std::shared_ptr<DynamicObj>> dynamicObjects_;

    std::vector<std::shared_ptr<NetworkedObj>> clientControlledObjects_;
    std::vector<std::shared_ptr<NetworkedObj>> serverControlledObjects_;

    std::unordered_map<std::string, std::function<void(void*)>> eventHandlers_;

    GraphEnv &graphEnv_;
    InputHandler inputHandler_;

    NetworkHandler nh_;
    //DatabaseHandler dbh_;



    int frame_rate = 25;
public:
    std::string game_name;

    Saturn(GraphEnv &graph_env, SoftwareSerial &controllerInput)
    : graphEnv_(graph_env),
    inputHandler_(controllerInput)
    {
        nh_.WPA2Connect(ssid, pass);
        nh_.gameSyncInit();
    };
    ~Saturn(){};

    template<typename T>
    void add_dynamicObj(std::shared_ptr<T> obj_ptr, uint16_t flags = OBJ_PASSIVE);
    template<typename T>
    void add_staticObj(std::shared_ptr<T> obj_ptr, uint16_t flags = OBJ_PASSIVE);
    template<typename T>
    void add_controlableObj(std::shared_ptr<T> obj_ptr, uint16_t flags = OBJ_CLIENT_CONTROLLED);

    void processInput();
    
    GraphEnv &getGraphicalEnv(){
        return graphEnv_;
    };

    std::unique_ptr<std::vector<Collision>> getObjectCollisions(DynamicObj *obj);
    bool areObjectsCollided(Obj *objA, Obj *objB);
    Collision getCollisionInfo(Obj *objA, Obj *objB);

    void update_frame(void);

    void run() override;

    void addEvent(std::string event_name, std::function<void(void*)> handler){
        eventHandlers_[event_name] = handler;
    }

    void clearObjects();
    void handleEvents(DynamicObj* obj);

};

template<typename T>
void Saturn::add_dynamicObj(std::shared_ptr<T> obj_ptr, uint16_t flags){
    static_assert(std::is_base_of<DynamicObj, T>::value, 
                       "Argument failed check for inheritence from DynamicObj");
    dynamicObjects_.push_back(obj_ptr);

    nh_.registerObj(obj_ptr, flags);
}

template<typename T>
void Saturn::add_staticObj(std::shared_ptr<T> obj_ptr, uint16_t flags){
    static_assert(std::is_base_of<StaticObj, T>::value,
                        "Argument failed check for inheritence from DynamicObj");
    staticObjects_.push_back(obj_ptr);

    nh_.registerObj(obj_ptr, flags);
}

template<typename T>
void Saturn::add_controlableObj(std::shared_ptr<T> obj_ptr, uint16_t flags){
    static_assert(std::is_base_of<IControlableAbstr, T>::value,
                        "Argument failed check for inheritence from IControlableAbstr");
    controlableObjects_.push_back(obj_ptr);

    // for rendering and collisions and more
    this->add_dynamicObj(obj_ptr, flags);
}

#endif