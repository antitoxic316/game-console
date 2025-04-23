#include "ControlsHandler.h"

const std::unordered_map<uint8_t, DefaultControlKeys> DEFAULT_KEY_MAPPING = {
    {1, DefaultControlKeys::LEFT},
    {2, DefaultControlKeys::RIGHT},
    {4, DefaultControlKeys::UP},
    {8, DefaultControlKeys::DOWN},
};