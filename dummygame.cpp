#include "dummygame.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Dummygame::Dummygame()
{
    this->game_env.setGraphicalEnv(&display);

    std::shared_ptr<dummyObj> ralsei_obj = std::make_shared<dummyObj>("ralsei");
    ralsei_obj->setBitmap(img_bitmap, 64, 64);
    

    this->game_env.add_dynamicObj(ralsei_obj);
}

Dummygame::~Dummygame()
{
}

void Dummygame::start(){
    this->game_env.start();
}