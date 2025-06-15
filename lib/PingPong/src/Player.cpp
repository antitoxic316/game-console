#include "Player.h"

void Player::onKeyHeld(const PControlKeys key, const InputData input_data){
    if(key == PControlKeys::UP){
        this->move(this->getX(), this->getY() - 1);
    }
    if(key == PControlKeys::DOWN){
        this->move(this->getX(), this->getY() + 1);
    }
}