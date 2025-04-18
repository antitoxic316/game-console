#include <unordered_map>
#include <cstdint>
#include <type_traits>

enum DefaultControlKeys {
    UP, DOWN, LEFT, RIGHT
};
extern const std::unordered_map<uint8_t, DefaultControlKeys> DEFAULT_KEY_MAPPING;


template<typename KeysEnum>
class ControlsHandler
{
    static_assert(std::is_enum<KeysEnum>::value, 
                    "ControlKeysEnum must be the type of enum");
private:
    std::unordered_map<uint8_t, KeysEnum> key_map;
    std::unordered_map<KeysEnum, bool> pressed_keys;

    static std::unordered_map<KeysEnum, bool> 
    generatePressedKeysVector(
        std::unordered_map<uint8_t, KeysEnum> key_map
    );
public:
    ControlsHandler(std::unordered_map<uint8_t, KeysEnum> keyMap)
        : key_map(keyMap),
          pressed_keys(generatePressedKeysVector(keyMap)){
    };
    ~ControlsHandler() = default;

    void setByteToKeyMap(std::unordered_map<uint8_t, KeysEnum> map){
        this->key_map = map;
    }

    void processInputByte(uint8_t input);
    
    std::unordered_map<KeysEnum, bool> getKeysState(){
        return this->pressed_keys;
    }
};

template<typename KeysEnum>
std::unordered_map<KeysEnum, bool> 
ControlsHandler<KeysEnum>::generatePressedKeysVector(std::unordered_map<uint8_t, KeysEnum> keyMap)
{
    std::unordered_map<KeysEnum, bool> pressed_keys;

    for(auto &it: keyMap){
        pressed_keys.insert(it.first, false);
    }

    return pressed_keys;
}
