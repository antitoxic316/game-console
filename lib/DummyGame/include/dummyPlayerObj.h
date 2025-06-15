#ifndef _DUMMYPLAYEROBJ_H_
#define _DUMMYPLAYEROBJ_H_

#include <Saturn.h>

class dummyPlayerObj : public ControlableObjBase<dummyPlayerObj, PControlKeys>
{
private:
    /* data */
public:
    dummyPlayerObj(
        const std::string &name,
        std::unordered_map<uint16_t, PControlKeys> keyMap
    )
        : ControlableObjBase(name, keyMap){
    }
    ~dummyPlayerObj() = default;

    void onKeyHeld(const PControlKeys key, const InputData i_data);
};


#endif