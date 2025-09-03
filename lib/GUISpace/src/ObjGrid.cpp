#include "ObjGrid.h"

// QUICK HACK, LATER SHOULD BE FIXED
void ObjGrid::onKeyPressed(const PControlKeys key, const InputData input_data) {
    if(key >= 0 && key <= 3){
        onNavigationKeyPressed(key);
    } else {
        onMiscKeyPressed(key);
    }
};

void ObjGrid::onNavigationKeyPressed(const PControlKeys key){
    int i_v = 0, j_v = 0;
    std::shared_ptr<InteractableWidget> newWidget(nullptr);

    
    switch(key){
        case LEFT:
            //j_v = -1;
            break;
        case RIGHT:
            //j_v = 1;
            break;
        case UP:
            newWidget = widgetGrid_[0][0];
            Serial.print("name check ");
            Serial.println(newWidget->getName().c_str());
            break;
        case DOWN:
            newWidget = widgetGrid_[1][0];
            Serial.print("name check ");
            Serial.println(newWidget->getName().c_str());
            break;
        default:
            break;
    }
    if(!newWidget)
        return;
    if(selectedWidget_)
        selectedWidget_->onWidgetUnSelected();
    newWidget->onWidgetSelected();
    selectedWidget_ = newWidget;
}

void ObjGrid::onMiscKeyPressed(const PControlKeys key){
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
        default:
            break;
    };   
}