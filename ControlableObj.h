#ifndef _ControlableObj_H_
#define _ControlableObj_H_

#include "DynamicObj.h"

#include <unordered_map>

enum ControlKeys {
    UP, DOWN, LEFT, RIGHT
};

class ControlableObj : public Obj
{
private:
    std::unordered_map<uint8_t, ControlKeys> key_map;
    std::function<void(ControlableObj*, ControlKeys)> keyInputCallback;
public:
    ControlableObj(const std::string &name) 
        : Obj(name){
    };

    void onKeyInput(ControlKeys key){
        this->keyInputCallback(this, key);
    }
    void setKeyInputCallback(std::function<void(ControlableObj*, ControlKeys)> keyInputCallback){
        this->keyInputCallback = keyInputCallback;
    }

    virtual ~ControlableObj() override;
};

#endif
