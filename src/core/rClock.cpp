#include "rClock.h"
#include "renderEngine.h"

//============================= RELOJ =============================//
rClock::rClock() {
    this->start.Zero();
}

rTime rClock::restart() { 
    rTime timeToReturn;
    timeToReturn.setMilisec(renderEngine::Instance().getTicks() - (int)this->start.asMilliseconds());
    start.setMilisec(renderEngine::Instance().getTicks());
    return timeToReturn;
}

rTime rClock::getElapsedTime() { 
    return rTime(renderEngine::Instance().getTicks() - (int)this->start.asMilliseconds());
}


