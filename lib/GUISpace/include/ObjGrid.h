#ifndef _ObjGrid_H_
#define _ObjGrid_H_

#include <Saturn.h>

#include "Widget.h"
#include "InteracableWidget.h"

class ObjGrid : public ControlableObjBase<ObjGrid, PControlKeys>
{
private:
    int widgGridW_ = 10;
    int widgGridH_ = 10;
    std::shared_ptr<I_InteractableWidget> widgetGrid_[10][10];

    std::shared_ptr<I_InteractableWidget> selectedWidget_ = NULL;
public:
    ObjGrid(
        std::unordered_map<uint16_t, PControlKeys> keyMap
    ) : ControlableObjBase("rootObjGrid", keyMap){

    }
    ~ObjGrid() = default;

    void onInput(const PControlKeys key, const InputData input_data){
        int i_v = 0, j_v = 0;
        std::shared_ptr<I_InteractableWidget> newWidget = NULL;
        switch(key){
            case LEFT:
                j_v = -1;
                break;
            case RIGHT:
                j_v = 1;
                break;
            case UP:
                i_v = -1;
                break;
            case DOWN:
                i_v = 1;
                break;
            case X:
                selectedWidget_->onXPressed();
                return;
            case Y:
                selectedWidget_->onYPressed();
                return;
            case B:
                selectedWidget_->onBPressed();
                return;
            case A:
                selectedWidget_->onAPressed();
                return;
        };

        int j = 5;
        int i = 5;
        while(
            j >= 0 && j < widgGridW_ &&
            i >= 0 && i < widgGridH_ &&
            newWidget == NULL
        ) {
            i += i_v;
            j += j_v;
            if (widgetGrid_[i][j] != NULL && widgetGrid_[i][j]->isInteractable()){
                newWidget = widgetGrid_[i][j];
            }
        }

        newWidget->onWidgetSelected();
        selectedWidget_->onWidgetUnSelected();
        selectedWidget_ = newWidget;
    }
};

#endif