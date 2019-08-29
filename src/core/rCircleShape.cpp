#include "core.h"
//============================= CIRCLESHAPE =============================//

rCircleShape::rCircleShape(float r, int pc) {}

void rCircleShape::draw() {
    renderEngine* sfml;
    //sfml->Instance().getWindow()->draw(cs);
}

void rCircleShape::setFillColor(char c) {
    /* switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    break;
    }*/
}

void rCircleShape::setRadius(float r) {
   // cs.setRadius(r);
}

void rCircleShape::setPosition(float x, float y) {
   // cs.setPosition(x,y);
}

void rCircleShape::setOrigin(float x, float y) {
   // cs.setOrigin(x,y);
}



std::array<float, 2> rCircleShape::getPosition() {
    std::array<float,2> ret;
    
   // ret[0] = cs.getPosition().x;
   // ret[1] = cs.getPosition().y;
    
    return ret;
}

