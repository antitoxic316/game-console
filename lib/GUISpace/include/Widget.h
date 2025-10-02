#ifndef _Widget_H_
#define _Widget_H_

#include <Saturn.h>

class Widget : public DynamicObj
{
private:
    Widget *parentWidg_;

    int gridI_ = 0, gridJ_ = 0;
public:
    Widget(const std::string &name, Widget *parent = nullptr)
    : DynamicObj(name),
      parentWidg_(parent)
    {
    }
    ~Widget() = default;

    int getGridI() {
        return gridI_;
    };
    void setGridI(int gridI){
        gridI_ = gridI;
    };

    int getGridJ(){
        return gridJ_;
    };
    void setGridJ(int gridJ){
        gridJ_ = gridJ;
    };

    Widget *getParentWidget(){
        return parentWidg_;
    }

    void setParentWidget(Widget *w){
        parentWidg_ = w;
    }
};

#endif