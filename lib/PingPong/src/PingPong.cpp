#include "PingPong.h"

// TODO: move this function into engine class or some utils class;
//implement bit map creation
void PingPong::generateScreenBorders(int screen_w, int screen_h, bool inside_screen, bool visible){
    auto bottom_border = std::make_shared<StaticObj>("bottomBorder");
    bottom_border->move(-1, screen_h+1);
    bottom_border->setBitmap(nullptr, screen_w, 1);
    
    auto top_border = std::make_shared<StaticObj>("topBorder");
    top_border->move(-1, -1);
    top_border->setBitmap(nullptr, screen_w, 1);
    
    auto left_border = std::make_shared<StaticObj>("leftBorder");
    left_border->move(-1, -1);
    left_border->setBitmap(nullptr, 1, screen_h);
    
    auto right_border = std::make_shared<StaticObj>("rightBorder");
    right_border->move(screen_w+1, -1);
    right_border->setBitmap(nullptr, 1, screen_h);

    this->gameEnv_.add_staticObj(bottom_border);
    this->gameEnv_.add_staticObj(top_border);
    this->gameEnv_.add_staticObj(left_border);
    this->gameEnv_.add_staticObj(right_border);
}

PingPong::~PingPong()
{
}

void PingPong::start(){
    this->gameEnv_.start();
}