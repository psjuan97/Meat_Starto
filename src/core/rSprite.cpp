
#include "rSprite.h"
#include "renderEngine.h"

rSprite::rSprite() {

 propiedades.scaleX = 1; 
 propiedades.scaleY = 1; 
 propiedades.originX = 0;
 propiedades.originY = 0;
propiedades.posX = 20; propiedades.posY = 20; 


}

void rSprite::setTexture  (renderEngine::rTexture &t)       {   
    texture = &t; 
    this->rect.setHeight(t.getYSize());
    this->rect.setLeft(0);
    this->rect.setTop(0);
    this->rect.setWidth(t.getXSize());
}


void rSprite::setRotation (float a)           {   
    propiedades.rotation = a;              
}
void rSprite::rotate      (float r)           {   
    propiedades.rotation = r;                   
}
float rSprite::getRotation()                  {   
    return propiedades.rotation;        
}

void rSprite::setTextureRect(renderEngine::rIntRect rect){  
    this->rect.setHeight(rect.height);
    this->rect.setLeft(rect.left);
    this->rect.setTop(rect.top);
    this->rect.setWidth(rect.widht);
}

void rSprite::setOrigin   (float x, float y)  {  
    propiedades.originX = x;
    propiedades.originY = y;
}

void rSprite::setScale    (float x, float y)  {  
    
    propiedades.scaleX = x;
    propiedades.scaleY = y;

}

void rSprite::setPosition (float x, float y)  {   
    propiedades.posX = x; 
    propiedades.posY = y;           
}


bool rSprite::intersects(rSprite sprite_){
    //return sprite.getGlobalBounds().intersects(sprite_.getSprite().getGlobalBounds());
    return false;
}
void rSprite::draw() {

    renderEngine::Instance().drawTexture(texture,propiedades,rect);

}

bool rSprite::intersects(rRectangleShape rs) {
    //return sprite.getGlobalBounds().intersects(rs.getRectShape().getGlobalBounds());
        return false;


}
bool rSprite::intersects(rCircleShape cs) {
   // return sprite.getGlobalBounds().intersects(cs.getCircleShape().getGlobalBounds());
        return false;

}

std::array<float, 2> rSprite::getPosition() {
    std::array<float,2> ret;
    ret[0] = propiedades.posX;
    ret[1] = propiedades.posY;
    
    return ret;
}



void rSprite::setColor(int r, int g, int b)   {   
// sprite.setColor(sf::Color(r, g, b));

}
void rSprite::setColor(int r, int g, int b, int alpha)   {  
//sprite.setColor(sf::Color(r, g, b, alpha));

}


