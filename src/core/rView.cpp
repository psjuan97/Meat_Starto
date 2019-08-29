#include "core.h"

//============================= VISTA =============================//
rView::rView(float pos_x, float pos_y, float size_x, float size_y){ 
    hasTarget_ = false;
    center_pos_x = pos_x;
    center_pos_y =  pos_y;
    this->size_x =  size_x;
    this->size_y = size_y;
    _zoom = 1;
}

float  rView::getZoom(){
    return _zoom;
}

void rView::zoom      (float z)           {   
    //printf("zoom %f",z);
    
    this->_zoom = z;  
    this->size_x = this->size_x * z;
    this->size_y = this->size_y * z;         
}

void rView::setCenter (float x, float y)  {   
        center_pos_x = x;
        center_pos_y =  y;
}

void rView::move(float x, float y)        {  
    setCenter(center_pos_x + x, center_pos_y + y);
}

void rView::setSize(float x, float y)     {  
    size_x =  x;
    size_y = y;
}

std::array<float, 2>    rView::getCenter  () {
    std::array<float, 2> ret;
    ret[0] = this->center_pos_x;
    ret[1] = this->center_pos_y;
    
    return ret;
}

