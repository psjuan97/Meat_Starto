#pragma once

class rEvent {
    friend class renderEngine;
    public:
        rEvent();

        unsigned int sfType();
        
        int getKeyCode();                                                   //DEVUELVE EL CODIGO DEL EVENTO DE TECLADO
        int getJoystickButton();                                            //DEVUELVE EL CODIGO DE EVENTO DE BOTON DEL MANDO
        float getJoystickMoveAxis();                                          //EJE DE MOVIMIENTO DEL JOYSTICK/CRUCETA
        float getJoystickMovePosition();                                      //POSICION DE MOVIMIENTO DEL JOYSTICK/CRUCETA
        int getJoystickId();                                                //ID DEL MANDO: 0,1,2,3
        
    private:
        int eventType; 
        int keyCode;
        int btnCode;
        int joyAxis;
        int joyPosition;
        int joyId;         
};