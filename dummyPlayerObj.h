#ifndef _DUMMYPLAYEROBJ_H_
#define _DUMMYPLAYEROBJ_H_

#include "ControlableObjBase.h"

class dummyPlayerObj : public ControlableObjBase<dummyPlayerObj, DefaultControlKeys>
{
private:
    /* data */
public:
    dummyPlayerObj(
        const std::string &name,
        std::unordered_map<uint8_t, DefaultControlKeys> &keyMap
    )
        : ControlableObjBase(name, keyMap){
    }
    ~dummyPlayerObj();
    void onKeyInput(ControlableObj* obj_self, DefaultControlKeys key){
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
};


#endif