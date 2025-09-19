#include  <InteractableGrid.h>

void InteractableGrid::onKeyPressed(const PControlKeys key, const InputData input_data) {
    if(key >= 0 && key <= 3){
        onNavigationKeyPressed(key);
    } else {
        onMiscKeyPressed(key);
    }
};

void InteractableGrid::onNavigationKeyPressed(const PControlKeys key){
    int i_v = 0, j_v = 0;
    std::shared_ptr<InteractableWidget> newWidget(nullptr);

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
        default:
            break;
    }

    newWidget = getNearestWidget(i_v, j_v);

    if(!newWidget)
        return;
    if(selectedWidget_)
        selectedWidget_->onWidgetUnSelected();
    newWidget->onWidgetSelected();
    selectedWidget_ = newWidget;
}

void InteractableGrid::onMiscKeyPressed(const PControlKeys key){
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

std::shared_ptr<InteractableWidget> InteractableGrid::getNearestWidget(int i_v, int j_v){
    std::shared_ptr<InteractableWidget> widg(nullptr);

    // find widget at chosen direction
    if(i_v){
        int j = currentJ_;
        int searchStep = 1;
        int searchDirection = -1;
        bool failedTwice = false;
        while(true){
            int i = currentI_;
            while(true){
                i += i_v;
                if(i >= widgGridH_ || i < 0){
                    break;
                }
                if(widgetGrid_[i][j]){
                    widg = widgetGrid_[i][j];
                    currentI_ = i;
                    currentJ_ = j;
                    return widg; 
                }
            }
i_v_loop_direction_change:
            searchDirection *= -1;
            int newJ = j + (searchDirection * searchStep);
            searchStep++;

            j = newJ;

            if(newJ < 0 || newJ >= widgGridW_){
                if(failedTwice){
                    break;
                }
                failedTwice = true;
                goto i_v_loop_direction_change;
            }
            failedTwice = false;
        }
    }
    
    if(j_v){
        int i = currentI_;
        int searchStep = 1;
        int searchDirection = -1;
        bool failedTwice = false;
        while(true){
            int j = currentJ_;
            while(true){
                j += j_v;
                if(j >= widgGridH_ || j < 0){
                    break;
                }
                if(widgetGrid_[i][j]){
                    widg = widgetGrid_[i][j];
                    currentI_ = i;
                    currentJ_ = j;
                    return widg; 
                }
            }
j_v_loop_direction_change:
            searchDirection *= -1;
            int newI = i + (searchDirection * searchStep);
            searchStep++;

            i = newI;

            if(newI < 0 || newI >= widgGridW_){
                if(failedTwice){
                    break;
                }
                failedTwice = true;
                goto j_v_loop_direction_change;
            }
            failedTwice = false;
        }
    }

    // no widget found
    return nullptr;
}