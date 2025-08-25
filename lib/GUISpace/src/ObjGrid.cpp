#include "ObjGrid.h"

// QUICK HACK, LATER SHOULD BE FIXED
void ObjGrid::onKeyPressed(const PControlKeys key, const InputData input_data) {
    int i_v = 0, j_v = 0;
    std::shared_ptr<InteractableWidget> newWidget(nullptr);

    Serial.println("buffer check00");

    Serial.print("obj grid recieved: ");
    Serial.println(input_data.key_byte);
    
    if(!(key >= 0 && key <= 3)){
        
    }
    
    switch(key){
        case LEFT:
            //j_v = -1;
            break;
        case RIGHT:
            //j_v = 1;
            break;
        case UP:
            newWidget = widgetGrid_[0][0];
            Serial.print("name check");
            Serial.println(newWidget->getName().c_str());
            break;
        case DOWN:
            Serial.print("name check");
            Serial.println(newWidget->getName().c_str());
            newWidget = widgetGrid_[1][0];
            break;
        default:
            break;
    }
    if(!newWidget){
        return;
    }
    newWidget->onWidgetSelected();
    if(selectedWidget_){
        selectedWidget_->onWidgetUnSelected();
    }
    selectedWidget_ = newWidget;

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
            Serial.println(selectedWidget_->getName().c_str());
            selectedWidget_->onAPressed();
            return;
    };
};
