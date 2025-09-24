#pragma once

#include <InteractableGrid.h>
#include <ButtonWidget.h>

#define keys_W 2
#define keys_H 2

class Keyboard : public InteractableGrid
{
private:
public:
  Keyboard(const std::string &name) :
    InteractableGrid(name)
  {
    keyboardInit();
  }

  void keyboardInit(){
    for(int i = 0; i < keys_H; i++){
      for(int j = 0; j < keys_W; j++){
        std::string btn_name = std::to_string((i*keys_H + j)+32); //first ascii
        std::shared_ptr<ButtonWidget> key_btn = std::make_shared<ButtonWidget>(btn_name);
        key_btn->setLabel(btn_name);
        key_btn->setGridI(i);
        key_btn->setGridJ(j);
        key_btn->move(60 + i*12, j*12);
        key_btn->setAButtonPressedCallback([this, btn_name](InteractableWidget *w){
          Serial.print(btn_name.c_str());
          Serial.println(" key pressed");
          w->emitEvent("char typed", (void *)(w->getName().c_str())); //first char is the CHARACTER
        });
        placeWidget(key_btn, key_btn->getGridI(), key_btn->getGridI());
      }
    }
  }

  void drawCallback(GraphEnv &env) override {
    env.drawLine(getX(), getY(), getX(), env.getScreenH());
    env.drawLine(getX(), getY(), env.getScreenW(), getY());
  }
};