#include "rIntRect.h"



//============================= INTRECT =============================//
rIntRect::rIntRect() {
    left = 0;
    top = 0;
    widht = 0;
    height = 0;
}

rIntRect::rIntRect(int x, int y, int w, int h)  {
    left = x;
    top = y;
    widht = w;
    height = h;
}

void rIntRect::setTop(int t) {
    top = t;
}
void rIntRect::setLeft(int l) {
    left = l;
}
void rIntRect::setWidth(int w) {
    widht = w;
}
void rIntRect::setHeight(int h) {
    height = h;
}

bool rIntRect::contains(float x, float y) {

    if(left - x < widht && top - y < height){
        return true;

    }
    return false;
}