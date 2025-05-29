#ifndef _InteractableWidget_H_
#define _InteractableWidget_H_

#include "I_InteractableWidget.h"
#include "Widget.h"

class InteractableWidget : public Widget, public I_InteractableWidget
{
private:
public:
    InteractableWidget(const std::string &name)
    : Widget(name)
    {

    }
    ~InteractableWidget() = default;
};

#endif