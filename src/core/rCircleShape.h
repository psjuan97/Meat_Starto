#include "../renderEngine/renderEngine.h"

#pragma once


    
    class rCircleShape {
        friend class renderEngine;
        public:
            rCircleShape(float r, int pc);
            
            void draw();
            void setFillColor(char c);
            void setPosition(float x, float y);
            void setRadius(float r);
            void setOrigin(float x, float y);
            
            std::array<float,2> getPosition();
            
        private:
            //sf::CircleShape getCircleShape();   //NO VA BIEN
            //sf::CircleShape cs;
    };
    