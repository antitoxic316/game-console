#pragma once

#include "Ball.h"
#include "Player.h"

static const uint8_t ball_bitmap[] PROGMEM  = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static const uint8_t player_bitmap[] PROGMEM  = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const std::unordered_map<uint16_t, PControlKeys> P1_KEY_MAPPING = {
    {1, PControlKeys::UP},
    {2, PControlKeys::DOWN}
};

const std::unordered_map<uint16_t, PControlKeys> P2_KEY_MAPPING = {
    {4, PControlKeys::UP},
    {8, PControlKeys::DOWN}
};


class PingPong
{
private:
    Saturn gameEnv_;
public:
    PingPong(GraphEnv &graph_env, SoftwareSerial &controllerInput)
        :gameEnv_(graph_env, controllerInput)
    {
        gameInit();
    }
    ~PingPong();

    void restart();
    void generateScreenBorders(int screen_w, int screen_h, bool inside, bool visible);

    void onGameOver(void *player_name){
        gameEnv_.getGraphicalEnv().drawText(0,0,"8", 10);
        gameEnv_.getGraphicalEnv().display();
        delay(500);
        gameEnv_.getGraphicalEnv().clearDisplay();
        restart();
        //this->gameEnv_.start();
    }

    void gameInit(){
        this->gameEnv_.addEvent("game over", [this](void *data){ onGameOver(data); });
    }

    void populateObjects();
    void start();
};
