#include "DynamicObj.h"

void DynamicObj::emitEvent(const std::string &event_name, void* data){
    ObjEvent e = {event_name, data};
    this->eventQueue_.push(e);
}
