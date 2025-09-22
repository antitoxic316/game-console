#pragma once

#include <InteractableWidget.h>
#include <IControlableObj.h>

class ControlableWidget : public IControlableObj<PControlKeys>, public InteractableWidget
{
private:
public:
  ControlableWidget(const std::string &name):
    InteractableWidget(name){
  }

  virtual void onWidgetSelected() override {
    InteractableWidget::onWidgetSelected();
    emitEvent("widgetTakeControl", this);
  }

  virtual void onWidgetUnSelected() override {
    InteractableWidget::onWidgetUnSelected();
    emitEvent("widgetReturnControl", nullptr);
  }
};