#ifndef _GUISpace_H_
#define _GUISpace_H_

#include <Saturn.h>

#include "ButtonWidget.h"
#include "ObjGrid.h"

class GUISpace
{
private:
    Saturn gameEnv_;
    std::shared_ptr<ObjGrid> mainObjGrid_;
public:
    GUISpace(GraphEnv &graph_env, SoftwareSerial &controllerInput) 
      : gameEnv_(graph_env, controllerInput),
      mainObjGrid_(std::make_shared<ObjGrid>(DEFAULT_KEY_MAPPING))
    {
      gameEnv_.add_controlableObj(mainObjGrid_);
    };
    ~GUISpace() = default;

    void start();

    void addInteractableWidget(std::shared_ptr<InteractableWidget> widg){
      gameEnv_.add_dynamicObj(widg);
      mainObjGrid_->placeWidget(widg, widg->getGridI(), widg->getGridJ());
    }
};

#endif