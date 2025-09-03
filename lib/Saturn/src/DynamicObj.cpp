#include "DynamicObj.h"

#include <Arduino.h>

void DynamicObj::emitEvent(const std::string &event_name, void* data){
    ObjEvent e = {event_name, data};
    eventQueue_.push(e);
}
