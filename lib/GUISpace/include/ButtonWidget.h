#ifndef _ButtonWidget_H_
#define _ButtonWidget_H_

#include "InteractableWidget.h"

class ButtonWidget : public InteractableWidget
{
private:
    std::string label_;
public:
    ButtonWidget(const std::string &name)
    : InteractableWidget(name){

    }
    ~ButtonWidget() = default;

    virtual void drawCallback(GraphEnv &graph_env) override {
        int drawSize = 2;
        if(!selected_){
            drawSize = 1;
        }
        graph_env.drawText(this->getX(), this->getY(), label_.c_str(), drawSize);
    }

    void setLabel(std::string str){
        label_ = str;
    }
};

#endif