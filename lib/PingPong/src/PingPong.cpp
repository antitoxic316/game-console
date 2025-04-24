#include "PingPong.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const std::unordered_map<uint8_t, PControlKeys> P1_KEY_MAPPING = {
    {1, PControlKeys::UP},
    {2, PControlKeys::DOWN}
};

const std::unordered_map<uint8_t, PControlKeys> P2_KEY_MAPPING = {
    {4, PControlKeys::UP},
    {8, PControlKeys::DOWN}
};

PingPong::PingPong()
{
    this->game_env.setGraphicalEnv(&display);

    this->generateScreenBorders(SCREEN_WIDTH, SCREEN_HEIGHT, false, false);

    std::shared_ptr<Ball> ball_obj = std::make_shared<Ball>("ball");
    ball_obj->setBitmap(ball_bitmap, 12, 12);
    ball_obj->move(64, 32);
    this->game_env.add_dynamicObj(ball_obj);

    std::shared_ptr<Player> p1_obj = std::make_shared<Player>("player1", P1_KEY_MAPPING);
    p1_obj->setBitmap(player_bitmap, 4, 32);
    p1_obj->move(10, 20);
    this->game_env.add_controlableObj(p1_obj);

    std::shared_ptr<Player> p2_obj = std::make_shared<Player>("player2", P2_KEY_MAPPING);
    p2_obj->setBitmap(player_bitmap, 4, 32);
    p2_obj->move(110, 20);
    this->game_env.add_controlableObj(p2_obj);
}


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

    this->game_env.add_staticObj(bottom_border);
    this->game_env.add_staticObj(top_border);
    this->game_env.add_staticObj(left_border);
    this->game_env.add_staticObj(right_border);
}

PingPong::~PingPong()
{
}

void PingPong::start(){
    this->game_env.start();
}