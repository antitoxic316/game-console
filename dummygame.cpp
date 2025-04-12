#include "dummygame.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Dummygame::Dummygame()
{
    this->game_env.setGraphicalEnv(&display);

    this->generateScreenBorders(SCREEN_WIDTH, SCREEN_HEIGHT, false, false);

    std::shared_ptr<dummyObj> ralsei_obj = std::make_shared<dummyObj>("ralsei");
    ralsei_obj->setBitmap(ralsei_bitmap, 24, 24);
    this->game_env.add_dynamicObj(ralsei_obj);

    std::shared_ptr<testObj> test_obj = std::make_shared<testObj>("test");
    test_obj->setBitmap(ralsei_bitmap, 24, 24);
    test_obj->move(94, 0);
    this->game_env.add_dynamicObj(test_obj);
}


// TODO: move this function into engine class or some utils class;
//implement bit map creation
void Dummygame::generateScreenBorders(int screen_w, int screen_h, bool inside_screen, bool visible){
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

    this->game_env.add_staticObj(bottom_border);
    this->game_env.add_staticObj(top_border);
    this->game_env.add_staticObj(left_border);
    this->game_env.add_staticObj(right_border);
}

Dummygame::~Dummygame()
{
}

void Dummygame::start(){
    this->game_env.start();
}