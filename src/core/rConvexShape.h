#include "../renderEngine/renderEngine.h"


#pragma once
class rConvexShape {
        public:
            rConvexShape();
            
            void draw();
            void setPointCount(int s);                      //NUMERO DE PUNTOS
            void setPoint(int p, float x, float y);         //ESTABLECER UN PUNTO
            void setFillColor(char c);                      //ESTABLECER UN COLOR DE FONDO
            void setOutlineColor(char c);                   //ESTABLECER UN COLOR PARA EL BORDE
            void setOutlineThickness(float f);              //ESTABLECER UN ANCHO PARA EL BORDE
            std::array<float,2> getPosition();              //CONSEGUIR POSICION
            void setPosition(float x, float y);             //ESTABLECER LA POSICION
            void move(float x, float y);                    //MOVER
            void setTexture(renderEngine::rTexture &t);                   //ESTABLECER TEXTURAS
            
        private:
            //sf::ConvexShape cs;
    };
