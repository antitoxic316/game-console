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

    std::shared_ptr<WidgetController> wController_;
public:
    GUISpace(GraphEnv &graph_env, SoftwareSerial &controllerInput) 
      : gameEnv_(graph_env, controllerInput),
      mainObjGrid_(std::make_shared<InteractableGrid>("rootGrid")),
      wController_(std::make_shared<WidgetController>(gameEnv_, mainObjGrid_.get()))
    {
      gameEnv_.setHandleCollisionsFlag(false);
      gameEnv_.add_controlableObj(wController_);
    };
    ~GUISpace() = default;

    void init();

    void addInteractableWidget(std::shared_ptr<InteractableWidget> widg){
      gameEnv_.add_dynamicObj(widg);
      mainObjGrid_->placeWidget(widg, widg->getGridI(), widg->getGridJ());
    }

    void addWidgetGrid(std::shared_ptr<InteractableGrid> widg){
      gameEnv_.add_dynamicObj(widg);
      mainObjGrid_->placeWidget(widg, widg->getGridI(), widg->getGridJ());
      for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
          std::shared_ptr<InteractableWidget> child = widg->getChildWidget(i, j);
          if(!child){
            continue;
          }
          gameEnv_.add_dynamicObj(child);
        }
      }
    }

    void addWidget(std::shared_ptr<Widget> w){
      gameEnv_.add_dynamicObj(w);
    }

    Saturn& getSaturnRef(){
      return gameEnv_;
    }
};

#endif