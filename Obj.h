#ifndef _Obj_H_
#define _Obj_H_

#include <vector>
#include <string>
#include <cstdint>

class Obj
{
private:
    std::string name;
    int x = 0, y = 0;
    int w = 0, h = 0;
    bool isSolid = false;
    const uint8_t *bit_map;
public:
    Obj (const std::string &name) : name(name) {

    };
    virtual ~Obj() {};
    virtual const std::string& getName(){
        return name;
    }

    void setBitmap(const uint8_t *bitmap, int w, int h);
    const uint8_t *getBitmap(){
        return this->bit_map;
    }

    int getX(){
        return this->x;
    }


    int getY(){
        return this->y;
    }

    int getWidth(){
        return this->w;
    }

    int getHeight(){
        return this->h;
    }

    void move(int x, int y);
};

#endif