#include "Obj.h"

void Obj::setBitmap(const uint8_t *bitmap, int w, int h){
    this->bitMap_ = bitmap;
    w_ = w;
    h_ = h;
}

void Obj::move(int x, int y){
    x_ = x;
    y_ = y;
}

void Obj::drawCallback(GraphEnv &graphEnv){
    if (!bitMap_){
        return;
    }

    graphEnv.drawBitMap(x_, y_, bitMap_, w_, h_);
}