#pragma once

#include <InteractableGrid.h>
#include <ButtonWidget.h>

#define keys_W 5
#define keys_H 5

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
    int offsetDistance = 12;

    for(int i = 0; i < keys_H; i++){
      for(int j = 0; j < keys_W; j++){

        std::string btn_name = std::to_string((char)((i*keys_H + j)+32)); //first ascii
        std::shared_ptr<ButtonWidget> key_btn = std::make_shared<ButtonWidget>(btn_name);
        key_btn->setLabel(btn_name);
        key_btn->setGridI(i);
        key_btn->setGridJ(j);
        key_btn->move(j+offsetDistance*j, i+offsetDistance*i);
        key_btn->setAButtonPressedCallback([this, btn_name](InteractableWidget *w){
          Serial.print(btn_name.c_str());
          Serial.println(" key pressed");
          w->emitEvent("char typed", (void *)(w->getName().c_str())); //first char is the CHARACTER
        });
        key_btn->setParentWidget(this);
        placeWidget(key_btn, key_btn->getGridI(), key_btn->getGridI());

        Serial.printf("i: %d, j: %d, lab: %s \n\r", i, j, btn_name.c_str());
      }
    }
  }

  void drawCallback(GraphEnv &env) override {
    env.drawLine(getX(), getY(), getX(), env.getScreenH());
    env.drawLine(getX(), getY(), env.getScreenW(), getY());
  }
};