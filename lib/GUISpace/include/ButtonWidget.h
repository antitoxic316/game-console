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
        if(!selected_){
            return;
        }
        graph_env.drawText(0, 0, label_.c_str(), 4);
    }

    void setLabel(std::string str){
        label_ = str;
    }
};

#endif