    
#pragma once

#include "../renderEngine/renderEngine.h"
#include "rRectangleShape.h"
#include "rCircleShape.h"
class rSprite {
        public:
            rSprite();                                  //CONSTRUCTOR
            
            void draw();
            
            void setTexture(renderEngine::rTexture &t);               //APLICAR UNA TEXTURA
            void setOrigin(float x, float y);           //ESTABLECER EL PUNTO ORIGEN
            void setScale(float x, float y);            //ESTABLECER LA ESCALA
            void setPosition(float x, float y);         //ESTABLECER LA POSICION
            void setRotation(float a);                  //ESTABLECER UNA ROTACION
            bool intersects(rSprite sprite_);
            void rotate(float r);
            float getRotation();
            void setTextureRect(renderEngine::rIntRect rect);
            std::array<float,2> getPosition();          //DEVUELVE LA POSICION
            bool intersects(rRectangleShape rs);  //COLISION DE SFML PARA LOS PINCHOS
            bool intersects(rCircleShape cs);  //COLISION DE SFML PARA LAS EXPLOSIONES
            //sf::Sprite getSprite();
            void setColor(int r, int g, int b);
            void setColor(int r, int g, int b, int alpha);
            
        private:
            renderEngine::rIntRect rect;
            renderEngine::rTexture* texture;
            renderEngine::texture_prop propiedades;
    };
