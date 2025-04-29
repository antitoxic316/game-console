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
#include <SSD1306_GraphEnv.h>

class Saturn
{
private:
    std::vector<std::shared_ptr<IControlableAbstr>> controlable_objects;

    std::vector<std::shared_ptr<StaticObj>> static_objects;
    std::vector<std::shared_ptr<DynamicObj>> dynamic_objects;

    std::unordered_map<std::string, std::function<void(void*)>> eventHandlers_;

    GraphEnv graph_env;
    InputHandler inputHandler_;

    int frame_rate = 25;
public:
    Saturn(uint16_t scr_w, uint16_t src_h)
        : graph_env(scr_w, src_h)
    {
    };
    ~Saturn(){};

    template<typename T>
    void add_dynamicObj(const std::shared_ptr<T> &obj_ptr);
    template<typename T>
    void add_staticObj(const std::shared_ptr<T> &obj_ptr);
    template<typename T>
    void add_controlableObj(const std::shared_ptr<T> &obj_ptr);

    void processInput();
    
    void setGraphicalEnv(Adafruit_SSD1306 *graph_env);

    std::unique_ptr<std::vector<Collision>> getObjectCollisions(DynamicObj *obj);
    bool areObjectsCollided(Obj *objA, Obj *objB);
    Collision getCollisionInfo(Obj *objA, Obj *objB);

    void update_frame(void);

    void start();
    void clear();

    void addEvent(std::string event_name, std::function<void(void*)> handler){
        eventHandlers_[event_name] = handler;
    }
    void handleEvents(DynamicObj* obj){
        std::queue<ObjEvent> emmitedEvents = obj->getEvents();
        
        for(; !emmitedEvents.empty(); emmitedEvents.pop()){
            std::string ev_name = emmitedEvents.front().ev_name;
            auto handler_entry = eventHandlers_.find(ev_name);
            if(handler_entry == eventHandlers_.end()){
                return;
            }

            std::function<void(void*)> event_f = handler_entry->second;
            event_f(emmitedEvents.front().data);
        }
    }
};

template<typename T>
void Saturn::add_dynamicObj(const std::shared_ptr<T> &obj_ptr){
    static_assert(std::is_base_of<DynamicObj, T>::value, 
                       "Argument failed check for inheritence from DynamicObj");
    this->dynamic_objects.push_back(obj_ptr);
}

template<typename T>
void Saturn::add_staticObj(const std::shared_ptr<T> &obj_ptr){
    static_assert(std::is_base_of<StaticObj, T>::value,
                        "Argument failed check for inheritence from DynamicObj");
    this->static_objects.push_back(obj_ptr);
}

template<typename T>
void Saturn::add_controlableObj(const std::shared_ptr<T> &obj_ptr){
    static_assert(std::is_base_of<IControlableAbstr, T>::value,
                        "Argument failed check for inheritence from IControlableAbstr");
    this->controlable_objects.push_back(obj_ptr);

    // for rendering and collisions and more
    static_assert(std::is_base_of<DynamicObj, T>::value,
                        "Argument failed check for inheritence from DynamicObj");
    this->dynamic_objects.push_back(obj_ptr);
}

#endif