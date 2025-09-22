#include <WiFiChoser.h>

void WiFiChoser::init(){
  std::shared_ptr<Keyboard> keyboard = std::make_shared<Keyboard>("keyboard");
  keyboard->setGridI(1);
  keyboard->setGridJ(0);
  keyboard->move(20, 0);
  guiEnv_.addWidgetGrid(keyboard);
  
  std::shared_ptr<ButtonWidget> confirm_btn = std::make_shared<ButtonWidget>("confirm");
  confirm_btn->setLabel("confirm");
  confirm_btn->setGridI(0);
  confirm_btn->setGridJ(0);
  confirm_btn->move(0, 50);
  confirm_btn->setAButtonPressedCallback([this](InteractableWidget *w){});
  guiEnv_.addInteractableWidget(confirm_btn);

  std::shared_ptr<Widget> text_buffer = std::make_shared<Widget>("txt_buff");
  text_buffer->move(0, 0);
}