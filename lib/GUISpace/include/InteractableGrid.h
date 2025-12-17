#pragma once

#include <InteractableWidget.h>
#include <ControlableWidget.h>
#include <I_InteractableWidget.h>

#include <InputHandler.h>

//amalgamation on Controlable object and widget obj
class InteractableGrid : public ControlableWidget
{
private:
  bool isRoot_ = false;
protected:
    int widgGridW_ = 10;
    int widgGridH_ = 10;
    std::shared_ptr<InteractableWidget> widgetGrid_[10][10];

    std::shared_ptr<InteractableWidget> selectedWidget_ = nullptr;
    int currentI_ = widgGridH_/2;
    int currentJ_ = widgGridW_/2;


    virtual void onNavigationKeyPressed(const PControlKeys key);
    virtual void onMiscKeyPressed(const PControlKeys key);
    virtual std::shared_ptr<InteractableWidget> getNearestWidget(int i_v, int j_v);
public:
  InteractableGrid(const std::string &name) :
    ControlableWidget(name)
  {
  }

  //puts widget onto a widgetGrid_, for locating widget with user interaction
  void placeWidget(std::shared_ptr<InteractableWidget> widg, int i, int j){
      widgetGrid_[i][j] = widg;
  }

  void onKeyPressed(const PControlKeys key, const InputData input_data) override;
  void onKeyHeld(const PControlKeys key, const InputData input_data) override{

  };
  void onKeyUnpressed(const PControlKeys key, const InputData input_data) override{
    
  };

  std::shared_ptr<InteractableWidget> getChildWidget(int i, int j){
    return widgetGrid_[i][j];
  }

  void setRoot(){
    isRoot_ = true;
  }
};