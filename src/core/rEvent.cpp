
#include "rEvent.h"
//============================= EVENTOS =============================//
rEvent::rEvent() {}

int rEvent::getKeyCode()              {return keyCode;}
int rEvent::getJoystickButton()       {return 0;}
float rEvent::getJoystickMoveAxis()     {return 0;}
float rEvent::getJoystickMovePosition() {return 0;}
int rEvent::getJoystickId()           {return 0;}

unsigned int   rEvent::sfType    () {    
    return eventType;
}