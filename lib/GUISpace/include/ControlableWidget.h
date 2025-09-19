#pragma once

#include <InteractableWidget.h>
#include <IControlableObj.h>

class ControlableWidget : public IControlableObj<PControlKeys>, public InteractableWidget
{
private:
public:
  ControlableWidget(std::string name):
    InteractableWidget(name){
  }
};