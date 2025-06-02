#include "ObjGrid.h"

void ObjGrid::onInput(const PControlKeys key, const InputData input_data){
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
    if(i_v){
        while(
            i >= 0 && i < widgGridH_ &&
            newWidget == NULL
        ) {
            if (widgetGrid_[i][j] != NULL){
                newWidget = widgetGrid_[i][j];
                break;
            }
            for(int k = 0; k < widgGridW_; k++){
                if (widgetGrid_[i][k] != NULL){
                    newWidget = widgetGrid_[i][k];
                    break;
                }
            }
            i += i_v;
        }
    } else if (j_v) {
        while(
            j >= 0 && j < widgGridW_ &&
            newWidget == NULL
        ) {
            if (widgetGrid_[i][j] != NULL){
                newWidget = widgetGrid_[i][j];
                break;
            }
            for(int k = 0; k < widgGridH_; k++){
                if (widgetGrid_[k][j] != NULL){
                    newWidget = widgetGrid_[k][j];
                    break;
                }
            }
            j += j_v;
        }
    }
    

    

    newWidget->onWidgetSelected();
    selectedWidget_->onWidgetUnSelected();
    selectedWidget_ = newWidget;
}