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
        int x, y;
        
        x = this->getX();
        y = this->getY();

        if(Widget *pWidg = getParentWidget()){
            x += pWidg->getX();
            y += pWidg->getY();
        }

        int drawSize = 2;
        if(!selected_){
            drawSize = 1;
        }
        graph_env.drawText(x, y, label_.c_str(), drawSize);
    }

    void setLabel(std::string str){
        label_ = str;
    }
};

#endif