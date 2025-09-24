#pragma once

#include <Widget.h>

class TextBufferWidget : public Widget {
private:
  std::string buff;
public:
  TextBufferWidget(const std::string &name)
  : Widget(name){
  }
  void addChar(char ch){
    buff += ch;
  }

  void drawCallback(GraphEnv &env) override {
    env.drawText(getX(), getY(), buff.c_str(), 1);
  }
};