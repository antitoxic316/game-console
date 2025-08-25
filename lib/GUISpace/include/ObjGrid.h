#ifndef _ObjGrid_H_
#define _ObjGrid_H_

#include <Saturn.h>

#include "Widget.h"
#include "InteractableWidget.h"

class ObjGrid : public ControlableObjBase<ObjGrid, PControlKeys>
{
private:
    int widgGridW_ = 10;
    int widgGridH_ = 10;
    std::shared_ptr<InteractableWidget> widgetGrid_[10][10] = {};

    std::shared_ptr<InteractableWidget> selectedWidget_ = nullptr;

    
public:
    ObjGrid(
        std::unordered_map<uint16_t, PControlKeys> keyMap
    ) : ControlableObjBase("rootObjGrid", keyMap){
    }
    ~ObjGrid() = default;

    //puts widget onto a widgetGrid_, for locating widget with user interaction
    void placeWidget(std::shared_ptr<InteractableWidget> widg, int i, int j){
        widgetGrid_[i][j] = widg;
    }

    void onKeyPressed(const PControlKeys key, const InputData input_data) override;
};

#endif