#pragma once

#include <Saturn.h>

class Player : public ControlableObjBase<Player, PControlKeys>
{
private:
public:
    Player(
        const std::string &name,
        std::map<uint16_t, PControlKeys> keyMap
    )
        : ControlableObjBase(name, keyMap){
    }
    ~Player() = default;

    void onKeyHeld(const PControlKeys key, const InputData input_data);
};