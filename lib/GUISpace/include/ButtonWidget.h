#ifndef _ButtonWidget_H_
#define _ButtonWidget_H_

#include "InteractableWidget.h"

class ButtonWidget : public InteractableWidget
{
private:
    char *label_;
public:
    ButtonWidget(const std::string &name)
    : InteractableWidget(name), label_(nullptr){

    }
    ~ButtonWidget(){
        if(label_){
            free(label_);
        }
    }

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
        graph_env.drawText(x, y, label_, drawSize);
    }

    void setLabel(const char *str){
        label_ = (char*)calloc(1, strlen(str)+1);
        strcpy(label_, str);
    }
};

#endif