#ifndef _DUMMYPLAYEROBJ_H_
#define _DUMMYPLAYEROBJ_H_

#include <ControlableObjBase.h>

enum DefaultControlKeys {
    UP, DOWN, LEFT, RIGHT
};
const std::unordered_map<uint8_t, DefaultControlKeys> DEFAULT_KEY_MAPPING = {
    {1, DefaultControlKeys::LEFT},
    {2, DefaultControlKeys::RIGHT},
    {4, DefaultControlKeys::UP},
    {8, DefaultControlKeys::DOWN}
};


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