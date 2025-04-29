#ifndef _DummyGame_H_
#define _DummyGame_H_

#include <Saturn.h>
#include "dummyObj.h"
#include "dummyPlayerObj.h"

static const uint8_t ralsei_bitmap[] PROGMEM  = {
  0x00, 0x00, 0x00, 
  0x00, 0x01, 0x84, 
  0xc0, 0x0b, 0xd4, 
  0xe0, 0x09, 0xec, 
  0xf0, 0x07, 0xf8, 
  0x50, 0x00, 0xfe, 
  0xd0, 0x05, 0x3e, 
  0xe0, 0x0d, 0xbe, 
  0xc0, 0x0f, 0xbe, 
  0xc0, 0x1f, 0xf4, 
  0xc3, 0xff, 0x5c, 
  0xe1, 0xf8, 0x1c, 
  0x31, 0xf8, 0x00, 
  0x01, 0x80, 0x00, 
  0x00, 0x0d, 0x00, 
  0x00, 0x08, 0x80, 
  0x00, 0x08, 0x80, 
  0x00, 0x1f, 0xb8, 
  0x00, 0x07, 0xc8, 
  0x00, 0x07, 0x80, 
  0x00, 0x06, 0x00, 
  0x00, 0x00, 0x38, 
  0x00, 0x00, 0x18, 
  0x00, 0x00, 0x00
};

class Dummygame
{
private:
    Saturn game_env;
public:
    Dummygame(int scr_w, int scr_h) 
      : game_env(scr_w, scr_h)
    {
      this->generateScreenBorders(scr_w, scr_h, false, false);

      this->game_env.addEvent("game over", [this](void *data){ this->game_env.clear(); });

      std::shared_ptr<dummyObj> ralsei_obj = std::make_shared<dummyObj>("ralsei");
      ralsei_obj->setBitmap(ralsei_bitmap, 24, 24);
      this->game_env.add_dynamicObj(ralsei_obj);

      std::shared_ptr<dummyPlayerObj> player_obj = std::make_shared<dummyPlayerObj>("player", DEFAULT_KEY_MAPPING);
      player_obj->setBitmap(ralsei_bitmap, 24, 24);
      player_obj->move(94, 0);
      this->game_env.add_controlableObj(player_obj);
    };
    ~Dummygame();

    void start();
    void generateScreenBorders(int screen_w, int screen_h, bool inside, bool visible);
};

#endif