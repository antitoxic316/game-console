#include "Obj.h"

void Obj::setBitMap(const uint8_t *bitmap, int w, int h){
    this->bit_map = bitmap;
    this->w = w;
    this->h = h;
}

void Obj::move(int x, int y){
    this->x = x;
    this->y = y;
}