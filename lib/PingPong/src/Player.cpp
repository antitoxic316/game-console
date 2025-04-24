#include "Player.h"

void Player::onKeyInput(PControlKeys key){
    if(key == PControlKeys::UP){
        this->move(this->getX(), this->getY() - 1);
    }
    if(key == PControlKeys::DOWN){
        this->move(this->getX(), this->getY() + 1);
    }
}