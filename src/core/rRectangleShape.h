#include "../renderEngine/renderEngine.h"

#pragma once

    class rRectangleShape {
        friend class renderEngine;
        public:
            rRectangleShape();
            rRectangleShape(float x, float y);
            
            void draw();                                    //DIBUJAR
            void move(float x, float y);                    //MOVER
            void rotate(float a);                           //ROTAR
            
            void setOrigin(float x, float y);               //ESTABLECER EL PUNTO CENTRAL
            void setTexture(renderEngine::ITexture *t);                   //ESTABLECER TEXTURA
            void setPosition(float x, float y);             //ESTABLECER POSICION
            void setFillColor(char c);                          //ESTABLECER UN COLOR
            void setFillRGBAColor(int r,int g, int b, int a=255);   //ESTABLECE UN COLOR PASANDO LOS PARAMETROS RGBA
            void setSize(float x, float y);                 //ESTABLECER UN TAMANYO
            void setRotation(float a);                      //ESTABLECER UNA ROTACION
            
            void setOutlineColor(char c);
            void setOutlineThickness(float f);
            
            std::array<float,2> getSize();                  //DEVUELVE EL TAMANYO
            std::array<float,2> getPosition();              //CONSEGUIR POSICION
        private:
            rIntRect rect;
            renderEngine::ITexture* texture;
            renderEngine::texture_prop propiedades;
          };