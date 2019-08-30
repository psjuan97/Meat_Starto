#include "core.h"

//============================= CONVEXSHAPE =============================//
rConvexShape::rConvexShape() {
}

void rConvexShape::draw() {
    //sfml->Instance().getWindow()->draw(cs);
}
void rConvexShape::setPointCount      (int s)                     {   
   // cs.setPointCount(s);
}
void rConvexShape::setOutlineThickness(float f)                   {  
     //cs.setOutlineThickness(f);
    }
void rConvexShape::setPoint           (int p, float x, float y)   { 
     // cs.setPoint(p,sf::Vector2f(x,y));
    }
void rConvexShape::move               (float x, float y)          {  
    // cs.move(x,y);
     
    }
void rConvexShape::setPosition        (float x, float y)          { 
      //cs.setPosition(x,y);
      
      }
void rConvexShape::setTexture         (renderEngine::ITexture &t)               { 
    //  cs.setTexture(t.getTexture());
    return;
      }
void rConvexShape::setFillColor(char c) {
  /*  switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'm':   cs.setFillColor(sf::Color::Magenta);        break;
        case 'w':   cs.setFillColor(sf::Color::White);          break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    cs.setFillColor(sf::Color::Black);          break;
    } */
}
void rConvexShape::setOutlineColor(char c) {
   /*  switch(c){
        case 'r':   cs.setOutlineColor(sf::Color::Red);    break;
        case 'g':   cs.setOutlineColor(sf::Color::Green);  break;
        default:    break;
    }*/
}
std::array<float, 2> rConvexShape::getPosition() {
    std::array<float,2> a;
    
   // a[0] = cs.getPosition().x;
    //a[1] = cs.getPosition().y;
    
    return a;
}

