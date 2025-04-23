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
        std::unordered_map<uint8_t, DefaultControlKeys> keyMap
    )
        : ControlableObjBase(name, keyMap){
    }
    ~dummyPlayerObj() = default;

    void onKeyInput(DefaultControlKeys key);
};


#endif