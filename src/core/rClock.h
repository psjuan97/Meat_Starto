#pragma once

#include "rTime.h"
  
  class rClock {
        public:
            rClock();
            
            rTime restart();          //REINICIAR EL RELOJ
            rTime getElapsedTime();   //TIEMPO SIN REINICIAR EL RELOJ
        private:
            rTime start;
    };
    
