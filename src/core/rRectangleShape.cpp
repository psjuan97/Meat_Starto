#include "core.h"

//============================= RECTANGLESHAPE =============================//
rRectangleShape::rRectangleShape() {
 propiedades.scaleX = 1; 
 propiedades.scaleY = 1; 
 propiedades.originX = 0;
 propiedades.originY = 0;
propiedades.posX = 20; propiedades.posY = 20; 

    texture = nullptr;
}

rRectangleShape::rRectangleShape(float x, float y){
    propiedades.scaleX = 1; 
    propiedades.scaleY = 1; 
    propiedades.originX = 0;
    propiedades.originY = 0;
    propiedades.posX = 20; propiedades.posY = 20; 

    this->texture = nullptr;

}

void rRectangleShape::draw() {

    renderEngine::Instance().drawTexture(texture,propiedades,rect);
    
}

void rRectangleShape::setTexture  (renderEngine::rTexture &t)       {   
    texture = &t;
}

void rRectangleShape::setPosition (float x, float y)  {   
    propiedades.posX = x; 
    propiedades.posY = y;
}

void rRectangleShape::setSize     (float x, float y)  {   
    rect.widht =x; 
    rect.height =y;
}

void rRectangleShape::move        (float x, float y)  {  

 }

void rRectangleShape::setOrigin   (float x, float y)  {  
    propiedades.originX = x; 
    propiedades.originY;
}

void rRectangleShape::setRotation (float a)           { 
     propiedades.rotation = a;
}

void rRectangleShape::rotate      (float a)           { 

}

std::array<float, 2> rRectangleShape::getSize() {
    std::array<float,2> ret;
    
    ret[0] = rect.widht;
    ret[1] = rect.height;
    
    return ret;
}

void rRectangleShape::setFillColor(char c) {
      
      
      int r,g,b;
        switch(c){
            case 'w':   r=255; g=255; b=255;  ;       break;
            case 'r':   r=255; g=0; b=0;       break;
            case 'y':   r=255; g=255; b=0;    break;
            default:    r=0; g=0; b=0;     break;
        }

    renderEngine::Instance().setDrawColor(r,g,b,255);


}

void rRectangleShape::setFillRGBAColor(int r, int g, int b, int a) {
    renderEngine::Instance().setDrawColor(r, g, b, a);
}

void rRectangleShape::setOutlineColor(char c) {
      /* switch(c){
        case 't':   rs.setOutlineColor(sf::Color::Transparent);    break;
        case 'r':   rs.setOutlineColor(sf::Color::Red);            break;
        case 'g':   rs.setOutlineColor(sf::Color::Green);          break;
        case 'b':   rs.setOutlineColor(sf::Color::Blue);           break;
        case 'y':   rs.setOutlineColor(sf::Color::Yellow);         break;
        case 'k':   rs.setOutlineColor(sf::Color::Black);          break;
        default:    break;
    }  */
}

void rRectangleShape::setOutlineThickness(float f) {

}

std::array<float, 2> rRectangleShape::getPosition() {
    std::array<float, 2> ret;
    ret[0] = propiedades.posX;
    ret[1] = propiedades.posY;
    
    return ret;
}
