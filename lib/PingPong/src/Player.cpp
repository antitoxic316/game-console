#include "Player.h"

void Player::onKeyHeld(const PControlKeys key, const InputData input_data){
    if(key == PControlKeys::UP || key == PControlKeys::P2_UP){
        this->move(this->getX(), this->getY() - 1);
    }
    if(key == PControlKeys::DOWN || key == PControlKeys::P2_DOWN){
        this->move(this->getX(), this->getY() + 1);
    }
}