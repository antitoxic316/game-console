#include "dummyPlayerObj.h"

void dummyPlayerObj::onKeyHeld(const PControlKeys key, const InputData i_data){
    if(key == PControlKeys::LEFT){
        this->move(this->getX() - 1, this->getY());
    }
    if(key == PControlKeys::RIGHT){
        this->move(this->getX() + 1, this->getY());
    }
    if(key == PControlKeys::UP){
        this->move(this->getX(), this->getY() - 1);
    }
    if(key == PControlKeys::DOWN){
        this->move(this->getX(), this->getY() + 1);
    }
}