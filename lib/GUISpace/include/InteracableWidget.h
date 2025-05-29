#ifndef _InteracableWidget_H_
#define _InteracableWidget_H_

#include "I_InteractableWidget.h"
#include "Widget.h"

class InteractableWidget : public Widget, public I_InteractableWidget
{
private:
    bool isInteractable_ = true;
public:
    InteractableWidget(const std::string &name)
    : Widget(name)
    {

    }
    ~InteractableWidget() = default;

    bool isInteractable(){
        return isInteractable_;
    }
};

#endif