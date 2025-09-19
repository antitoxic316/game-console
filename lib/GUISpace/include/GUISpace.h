#ifndef _GUISpace_H_
#define _GUISpace_H_

#include <Saturn.h>

#include <ButtonWidget.h>
#include <InteractableGrid.h>
#include <WidgetController.h>

#define ROOT_GRID_SIZE 10

class GUISpace
{
private:
    Saturn gameEnv_;

    std::shared_ptr<InteractableGrid> mainObjGrid_;

    WidgetController wController_;
public:
    GUISpace(GraphEnv &graph_env, SoftwareSerial &controllerInput) 
      : gameEnv_(graph_env, controllerInput),
      mainObjGrid_(std::make_shared<InteractableGrid>("rootGrid")),
      wController_(gameEnv_, mainObjGrid_.get())
    {
      gameEnv_.add_controlableObj(std::make_shared<WidgetController>(wController_));
    };
    ~GUISpace() = default;

    void init();

    void addInteractableWidget(std::shared_ptr<InteractableWidget> widg){
      gameEnv_.add_dynamicObj(widg);
      mainObjGrid_->placeWidget(widg, widg->getGridI(), widg->getGridJ());
    }

    Saturn& getSaturnRef(){
      return gameEnv_;
    }
};

#endif