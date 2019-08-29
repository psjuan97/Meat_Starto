
#pragma once
    
    class rTime {
        public:
            rTime();
            rTime(float sec);
            void setMilisec(int milisec);
            float asSeconds();                      //TIEMPO EN SEGUNDOS
            float asMilliseconds();                 //TIEMPO EN MILISEGUNDOS
            float asMicroseconds();                 //TIEMPO EN MICROSEGUNDOS
            void incrementTime(rTime t);
            void Zero();                            //TENER A 0 EL TIEMPO
        private:
            float _milisecond; 
    };
    
