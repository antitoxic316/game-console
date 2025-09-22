#pragma once

#include <ControlableWidget.h>
#include <ControlableObjBase.h>
#include <InputHandler.h>

#include <stack>

class WidgetController : public ControlableObjBase<WidgetController, PControlKeys>
{
private:
  std::stack<ControlableWidget*> controlStack_;

  Saturn &satRef_;
public:
  WidgetController(Saturn &saturn, ControlableWidget *root) 
  : ControlableObjBase("WidgetController", DEFAULT_KEY_MAPPING),
    satRef_(saturn)
  {
    //first object is always main control grid
    controlStack_.push(root);

    //to take or return control controlable widgets should emit appropriate events via Saturn
    satRef_.addEvent("widgetTakeControl", [this](void * caller) { this->onWidgetTakeControl(caller); });
    satRef_.addEvent("widgetReturnControl", [this](void *ommited) { this->onWidgetReturnControl(); });
  }

  void onWidgetTakeControl(void *caller){
    ControlableWidget *cw;
    cw = static_cast<ControlableWidget*>(caller);

    controlStack_.push(cw);
  }

  void onWidgetReturnControl(){
    controlStack_.pop();
  } 

  void onKeyPressed(const PControlKeys key, const InputData input_data) override {
    ControlableWidget *activeWidget;

    activeWidget = controlStack_.top();
    activeWidget->onKeyPressed(key, input_data);
  }
};