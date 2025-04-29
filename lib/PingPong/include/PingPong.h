#pragma once

#include "Ball.h"
#include "Player.h"

static const uint8_t ball_bitmap[] PROGMEM  = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static const uint8_t player_bitmap[] PROGMEM  = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const std::unordered_map<uint8_t, PControlKeys> P1_KEY_MAPPING = {
    {1, PControlKeys::UP},
    {2, PControlKeys::DOWN}
};

const std::unordered_map<uint8_t, PControlKeys> P2_KEY_MAPPING = {
    {4, PControlKeys::UP},
    {8, PControlKeys::DOWN}
};


class PingPong
{
private:
    Saturn game_env;
public:
    PingPong(int scr_w, int scr_h) 
        :game_env(scr_w, scr_h)
    {
        this->game_env.addEvent("game over", [this](void *data){ onGameOver(data); });

        this->generateScreenBorders(scr_w, scr_h, false, false);

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
    ~PingPong();

    void start();
    void generateScreenBorders(int screen_w, int screen_h, bool inside, bool visible);

    void onGameOver(void *player_name){
        this->game_env.clear();
        this->game_env.start();
    }
};
