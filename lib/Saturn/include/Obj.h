#ifndef _Obj_H_
#define _Obj_H_

#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>

#include <SSD1306_GraphEnv.h>

class Obj
{
private:
    char *name_;
    int x_ = 0, y_ = 0;
    int w_ = 0, h_ = 0;
    bool isSolid_ = true;
    const uint8_t *bitMap_;
public:
    Obj (const std::string &name) {
        name_ = (char*)calloc(1, name.size()+1);
        strcpy(name_, name.c_str());
    };
    ~Obj() {
        free(name_);
    };
    bool operator==(const Obj &obj) const {return obj.name_ == name_; };
    
    virtual char *getName(){
        return name_;
    }

    void setBitmap(const uint8_t *bitmap, int w, int h);
    const uint8_t *getBitmap(){
        return bitMap_;
    }

    int getX(){
        return x_;
    }
    void setX(int x){
        x_ = x;
    }

    int getY(){
        return y_;
    }
    void setY(int y){
        y_ = y;
    }

    int getWidth(){
        return w_;
    }

    int getHeight(){
        return h_;
    }

    bool isSolid(){
        return isSolid_;
    }

    void move(int x, int y);

    virtual void drawCallback(GraphEnv &graphEnv);
};

#endif