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
    {256, PControlKeys::P2_UP},
    {512, PControlKeys::P2_DOWN}
};


class PingPong
{
private:
    Saturn gameEnv_;
public:
    PingPong(GraphEnv &graph_env, SoftwareSerial &controllerInput)
        :gameEnv_(graph_env, controllerInput)
    {
        gameEnv_.addEvent("game over", [this](void *data){ onGameOver(data); });
        gameEnv_.game_name = "pingPONG";
    }
    ~PingPong();

    void restart();
    void generateScreenBorders(int screen_w, int screen_h, bool inside, bool visible);

    void onGameOver(void *player_name){
        gameEnv_.interrupt();
        gameEnv_.getGraphicalEnv().drawText(0,0,"8888888", 4);
        gameEnv_.getGraphicalEnv().display();
        delay(500);
        gameEnv_.clearObjects();
        init();
    }

    void populateObjects();
    void init();

    Saturn* getSaturnPtr(){
      return &gameEnv_;
    }
};
