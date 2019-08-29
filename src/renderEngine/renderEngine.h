/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   renderEngine.h
 * Author: pablomanez
 *
 * Created on 21 de marzo de 2018, 15:30
 */

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "../State.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../core/rView.h"



#include <array>




class renderEngine {
public:
    //<SINGLETON>
    static renderEngine& Instance(){
        static renderEngine instance;
        return instance;
    }
    //</SINGLETON>

    enum Keys{
        Up = SDLK_UP ,
        Down = SDLK_DOWN,
        Q = SDLK_q,
        Return = SDLK_SPACE,
        Left = SDLK_LEFT,
        Right = SDLK_RIGHT,
        ESC = SDLK_ESCAPE
    };

    struct texture_prop {
        int originX,originY;
        float scaleX, scaleY;
        int rotation;
        
        int posX, posY;
    };


    class rIntRect {
        friend class renderEngine;
        public:
            rIntRect();                             //CONSTRUCTOR 1 (NO UTILIZAR)
            //X,Y,W,H
            rIntRect(int x, int y, int w, int h);   //CONSTRUCTOR 2
            
            bool contains(float x, float y);        //TRUE: INTRECT CONTIENE AL PUNTO P(X,Y)
            int left;
            int top;
            int widht;
            int height;
            
            void setTop(int t);
            void setLeft(int l);
            void setWidth(int w);
            void setHeight(int h);
        private:
            SDL_Rect getIntRect();
            SDL_Rect ir;
     };
    
    //surface
    class rImage {
        friend class renderEngine;
        public:
            rImage();
            
            void loadFromFIle(std::string path);
            
        private:
            SDL_Texture* texture ;

    };
    
    //texure
    class rTexture {
        friend class renderEngine;
        public:
            rTexture();                             //CONSTRUCTOR SIN ARGUMENTOS
            rTexture(std::string path);             //CONSTRUCTOR CON ARGUMENTOS
            
            void loadFromFile(std::string path);                                        //APLICAR UNA RUTA A LA TEXTURA
            void loadFromImage(renderEngine::rImage im, renderEngine::rIntRect ir);     //APLICAR UNA IMAGEN A UNA TEXTURA, CON SU CUADRADO DE RECORTE
            int getXSize();
            int getYSize();
            
        private:
            SDL_Texture* getTexture();              //DEVUELVE LA TEXTURA (USAR SOLO INTERNAMENTE)
            SDL_Texture* texture ;

    };
    

    

    class rEvent {
        friend class renderEngine;
        public:
            rEvent();
            enum EventType{                //ENUMERACION CON LOS DISTINTOS EVENTOS (FALTA PONER LOS QUE SE VAYAN A UTILIZAR)
                KeyPressed                  = SDL_KEYDOWN,
                KeyReleased                 = SDL_KEYUP,
                Quit                    =  SDL_QUIT,
                JoystickConnected           = 99,
                JoystickDisconnected        = 100,
                JoystickButtonPressed       = 101,
                JoystickButtonReleased      = 102,
                JoystickMoved               = 103
            };
            unsigned int sfType();
            
            int getKeyCode();                                                   //DEVUELVE EL CODIGO DEL EVENTO DE TECLADO
            int getJoystickButton();                                            //DEVUELVE EL CODIGO DE EVENTO DE BOTON DEL MANDO
            float getJoystickMoveAxis();                                          //EJE DE MOVIMIENTO DEL JOYSTICK/CRUCETA
            float getJoystickMovePosition();                                      //POSICION DE MOVIMIENTO DEL JOYSTICK/CRUCETA
            int getJoystickId();                                                //ID DEL MANDO: 0,1,2,3
            
        private:
            SDL_Event event;            
    };
    
    
    
    class rFont {
        friend class renderEngine;
        public:
            rFont();
            void loadFromFile(std::string str);
        private:
            TTF_Font* font;

    };

    class rText {
        public:
            rText();
            
            void draw();
            void setPosition(float x,float y);
            void setFillColor(char c);
            void setScale(float fx, float fy);
            void setString(std::string str);
            void setCharacterSize(int s);
            void setFont(rFont &font);
            void setOrigin(float x, float y);
            std::array<float,2> getSize();
            int getFillColor(); //sf::Color
            
        private:
            std::string text;
            SDL_Texture* Message;
            renderEngine::rFont font;
            int posX, posY;
    };
    
    //METODOS PUBLICOS
    bool isOpen();                                  //TRUE SI LA VENTANA ESTA ABIERTA
    void close();                                   //CIERRA LA VENTANA
    void clear(char c);                             //CLEAR DE SFML
    void display();                                 //DIBUJA LA VENTANA
    std::array<float,2> getSize();                  //DEVUELVE LAS DIMENSIONES DE LA VENTANA
    std::array<float,2> getViewCenter();            //DEVUELVE EL CENTRO DE LA VENTANA
    std::array<float,2> getViewSize();              //DEVUELVE EL CENTRO DE LA VENTANA
    
    bool isJoystickConnected(int j);                //TRUE: SI EL JOYSTICK J ESTA CONECTADO
    void setView(rView v);                          //ESTABLECER UNA VISTA
    void moveView(float x, float y);
    bool pollEvent(rEvent &e);                      //PARA CONTROLAR LOS EVENTOS
    void ChangeState(State* pState);                //CAMBIO DE ESTADO
    
    int getTicks();
    void delay(Uint32 ms);
    void drawTexture(rTexture* texture, texture_prop propiedades, rIntRect rectOrigin);
    void setDrawColor(int r, int g, int b, int a);

private:
    
    


    //<SINGLETON>
    renderEngine();
    renderEngine(const renderEngine& orig);
    void operator=(renderEngine const& orig);
    //</SINGLETON>

    int w;
    int h;
    SDL_Window* sdl_window;
    SDL_Renderer* renderer;
    
    State* _state;                                  //ESTADO ACTUAL
    
    rView camera;
};

#endif /* RENDERENGINE_H */

