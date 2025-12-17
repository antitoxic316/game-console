#ifndef _InteractableWidget_H_
#define _InteractableWidget_H_

#include "I_InteractableWidget.h"
#include "Widget.h"

class InteractableWidget : public Widget, public I_InteractableWidget
{
private:
    std::function<void(InteractableWidget*)> widgetSelectedCB_;
    std::function<void(InteractableWidget*)> widgetUnselectedCB_;
    std::function<void(InteractableWidget*)> pressedACB_;
    std::function<void(InteractableWidget*)> pressedBCB_;
    std::function<void(InteractableWidget*)> pressedYCB_;
    std::function<void(InteractableWidget*)> pressedXCB_;
protected:
    bool selected_ = false;
public:
    InteractableWidget(const std::string &name)
    :   Widget(name),
        widgetSelectedCB_([](InteractableWidget *){}),
        widgetUnselectedCB_([](InteractableWidget *){}),
        pressedACB_([](InteractableWidget *){}),
        pressedBCB_([](InteractableWidget *){}),
        pressedYCB_([](InteractableWidget *){}),
        pressedXCB_([](InteractableWidget *){})
    {

    }

    void setWidgetSelectedCallback(std::function<void(InteractableWidget *self)> cb){
        widgetSelectedCB_ = cb;
    }
    void setWidgetUnSelectedCallback(std::function<void(InteractableWidget *self)> cb){
        widgetUnselectedCB_ = cb;
    }
    void setAButtonPressedCallback(std::function<void(InteractableWidget *self)> cb){
        pressedACB_ = cb;
    }
    void setBButtonPressedCallback(std::function<void(InteractableWidget *self)> cb);
    void setYButtonPressedCallback(std::function<void(InteractableWidget *self)> cb);
    void setXButtonPressedCallback(std::function<void(InteractableWidget *self)> cb);

    virtual void onWidgetSelected() override {
        selected_ = true;
        Serial.print(this->getName());
        Serial.println(F(" selected"));
    }

    virtual void onWidgetUnSelected() override {
        selected_ = false;
        Serial.print(this->getName());
        Serial.println(F(" unselected"));
    }

    //calls set previously callback if not overriden
    virtual void onXPressed() override {

    }

    //calls set previously callback if not overriden
    virtual void onYPressed() override {
        
    }

    //calls set previously callback if not overriden
    virtual void onBPressed() override {
        
    }

    //calls set previously callback if not overriden
    virtual void onAPressed() override {
        pressedACB_(this);
    }
};

#endif