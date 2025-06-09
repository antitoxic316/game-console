#include "ObjGrid.h"

// QUICK HACK, LATER SHOULD BE FIXED
void ObjGrid::onInput(const PControlKeys key, const InputData input_data){
    int i_v = 0, j_v = 0;
    std::shared_ptr<I_InteractableWidget> newWidget(nullptr);

    Serial.println("buffer check00");

    Serial.print("obj grid recieved: ");
    Serial.println(input_data.key_byte);
    
    
    switch(key){
        case LEFT:
            //j_v = -1;
            break;
        case RIGHT:
            //j_v = 1;
            break;
        case UP:
            selectedWidget_ = widgetGrid_[0][0];
            break;
        case DOWN:
            selectedWidget_ = widgetGrid_[1][0];
            break;
        default:
            break;
    }
    if(!selectedWidget_){
        return;
    }
    switch(key){
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
    /*
    newWidget->onWidgetSelected();
    selectedWidget_->onWidgetUnSelected();
    selectedWidget_ = newWidget;
    */
}