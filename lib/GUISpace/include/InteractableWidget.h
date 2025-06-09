#ifndef _InteractableWidget_H_
#define _InteractableWidget_H_

#include "I_InteractableWidget.h"
#include "Widget.h"


struct IGUICallbacks {
    std::function<void(I_InteractableWidget*)> pressedACallback;
};

class InteractableWidget : public Widget, public I_InteractableWidget
{
private:
    IGUICallbacks callbacks_;
protected:
    bool selected_;
public:
    InteractableWidget(const std::string &name)
    : Widget(name)
    {

    }
    ~InteractableWidget() = default;

    void onWidgetSelected() override {
        selected_ = false;
        Serial.println("selected");
    }

    void onWidgetUnSelected() override {
        selected_ = true;
        Serial.println("unselected");
    }

    void onXPressed() override {

    }

    void onYPressed() override {
        
    }

    void onBPressed() override {
        
    }

    void onAPressed() override {
        Serial.println("a pressed");
    }
};

#endif