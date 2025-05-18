#ifndef _DUMMYPLAYEROBJ_H_
#define _DUMMYPLAYEROBJ_H_

#include <Saturn.h>


const std::unordered_map<uint16_t, PControlKeys> DEFAULT_KEY_MAPPING = {
    {1, PControlKeys::LEFT},
    {2, PControlKeys::RIGHT},
    {4, PControlKeys::UP},
    {8, PControlKeys::DOWN}
};


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

    void onInput(const PControlKeys key, const InputData i_data);
};


#endif