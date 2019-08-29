#pragma once
#include <array>

class rView {
    friend class renderEngine;
    public:
        rView(float pos_x, float pos_y, float size_x, float size_y);        //CONSTRUCTOR
        
        void zoom(float z);                         //ZOOM A LA VISTA
        void setCenter(float x, float y);           //CENTRO DE LA VISTA
        std::array<float,2> getCenter();            //CENTRO DE LA VISTA
        void move(float x, float y);                //MOVER LA VISTA  
        void setSize(float x, float y);
        float getZoom();
    private:
        bool hasTarget_;
        float targetX;
        float targetY;
        float _zoom;
        int center_pos_x, center_pos_y, size_x, size_y;
};