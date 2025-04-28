#pragma once

#include "Ball.h"
#include "Player.h"

static const uint8_t ball_bitmap[] PROGMEM  = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static const uint8_t player_bitmap[] PROGMEM  = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

class PingPong
{
private:
    Saturn game_env;
public:
    PingPong(/* args */);
    ~PingPong();

    void start();
    void generateScreenBorders(int screen_w, int screen_h, bool inside, bool visible);

    void onGameOver(void *player_name){
        this->game_env.clear();
        this->game_env.start();
    }
};
