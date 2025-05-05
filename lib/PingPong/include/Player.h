#pragma once

#include <Saturn.h>

enum PControlKeys {
    UP, DOWN
};

class Player : public ControlableObjBase<Player, PControlKeys>
{
private:
public:
    Player(
        const std::string &name,
        std::unordered_map<uint16_t, PControlKeys> keyMap
    )
        : ControlableObjBase(name, keyMap){
    }
    ~Player() = default;

    void onInput(PControlKeys key, InputData input_data);
};