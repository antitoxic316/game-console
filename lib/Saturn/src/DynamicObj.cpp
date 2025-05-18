#include "DynamicObj.h"

#include <Arduino.h>

void DynamicObj::emitEvent(const std::string &event_name, void* data){
    Serial.println(event_name.c_str());
    ObjEvent e = {event_name, data};
    eventQueue_.push(e);
}
