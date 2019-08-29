#include "rTime.h"

//============================= TIEMPO =============================//
rTime::rTime() {
    _milisecond = 0;
}
rTime::rTime(float sec){
    this->_milisecond = sec * 1000.0f;
}

void rTime::setMilisec(int _milisecond){
    this->_milisecond = (float)_milisecond;
}

float rTime::asSeconds        ()  {   
    return this->_milisecond / 1000 ;

}
float rTime::asMilliseconds   ()  {   
    return this->_milisecond;
}
float rTime::asMicroseconds   ()  {  
     return this->_milisecond * 1000;
}
void rTime::Zero              ()  {   
    this->_milisecond = 0;
}
void rTime::incrementTime(rTime t){ 
    this->_milisecond += t.asMilliseconds();
}




