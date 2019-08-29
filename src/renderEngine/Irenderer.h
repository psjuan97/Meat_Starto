#ifndef IrenderEngine_H
#define IrenderEngine_H

#include <vector>
#include <array>
#include <stdint.h>
#include "../State.h"


class IrenderEngine {
public:

    
    //METODOS PUBLICOS
    virtual bool isOpen();                                  //TRUE SI LA VENTANA ESTA ABIERTA
    virtual void close();                                   //CIERRA LA VENTANA
    virtual void clear(char c);                             //CLEAR DE SFML
    virtual void display();                                 //DIBUJA LA VENTANA



};

#endif