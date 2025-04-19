#include "dummyPlayerObj.h"

void dummyPlayerObj::onKeyInput(DefaultControlKeys key){
    if(key == DefaultControlKeys::LEFT){
        this->move(this->getX() - 1, this->getY());
    }
    if(key == DefaultControlKeys::RIGHT){
        this->move(this->getX() + 1, this->getY());
    }
    if(key == DefaultControlKeys::UP){
        this->move(this->getX(), this->getY() - 1);
    }
    if(key == DefaultControlKeys::DOWN){
        this->move(this->getX(), this->getY() + 1);
    }
}