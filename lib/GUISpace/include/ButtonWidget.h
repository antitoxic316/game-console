#ifndef _ButtonWidget_H_
#define _ButtonWidget_H_

#include "InteractableWidget.h"

class ButtonWidget : public InteractableWidget
{
private:
public:
    ButtonWidget(const std::string &name)
    : InteractableWidget(name){

    }
    ~ButtonWidget() = default;

    void onWidgetSelected() override {
        Serial.println("selected");
    }

    void onWidgetUnSelected() override {
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