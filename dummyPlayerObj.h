#ifndef _DUMMYPLAYEROBJ_H_
#define _DUMMYPLAYEROBJ_H_

#include "ControlableObjBase.h"

class dummyPlayerObj : public ControlableObjBase<dummyPlayerObj>
{
private:
    /* data */
public:
    dummyPlayerObj(const std::string &name)
        : ControlableObjBase(name){
    }
    ~dummyPlayerObj();
    void onKeyInput(ControlableObj* obj_self, ControlKeys key){
        if(key == ControlKeys::LEFT){
            this->move(this->getX() - 1, this->getY());
        }
        if(key == ControlKeys::RIGHT){
            this->move(this->getX() + 1, this->getY());
        }
        if(key == ControlKeys::UP){
            this->move(this->getX(), this->getY() - 1);
        }
        if(key == ControlKeys::DOWN){
            this->move(this->getX(), this->getY() + 1);
        }
   }
};


#endif