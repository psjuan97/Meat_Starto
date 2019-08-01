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
    
    class rRectangleShape {
        friend class renderEngine;
        public:
            rRectangleShape();
            rRectangleShape(float x, float y);
            
            void draw();                                    //DIBUJAR
            void move(float x, float y);                    //MOVER
            void rotate(float a);                           //ROTAR
            
            void setOrigin(float x, float y);               //ESTABLECER EL PUNTO CENTRAL
            void setTexture(rTexture &t);                   //ESTABLECER TEXTURA
            void setPosition(float x, float y);             //ESTABLECER POSICION
            void setFillColor(char c);                          //ESTABLECER UN COLOR
            void setFillRGBAColor(int r,int g, int b, int a=255);   //ESTABLECE UN COLOR PASANDO LOS PARAMETROS RGBA
            void setSize(float x, float y);                 //ESTABLECER UN TAMANYO
            void setRotation(float a);                      //ESTABLECER UNA ROTACION
            
            void setOutlineColor(char c);
            void setOutlineThickness(float f);
            
            std::array<float,2> getSize();                  //DEVUELVE EL TAMANYO
            std::array<float,2> getPosition();              //CONSEGUIR POSICION
        private:
            renderEngine::rIntRect rect;
            renderEngine::rTexture* texture;
            int originX,originY;
            int sizeX, sizeY;
            int posX, posY;
            int rotation;
            
          };
    
    class rCircleShape {
        friend class renderEngine;
        public:
            rCircleShape(float r, int pc);
            
            void draw();
            void setFillColor(char c);
            void setPosition(float x, float y);
            void setRadius(float r);
            void setOrigin(float x, float y);
            
            std::array<float,2> getPosition();
            
        private:
            //sf::CircleShape getCircleShape();   //NO VA BIEN
            //sf::CircleShape cs;
    };
    
    class rSprite {
        public:
            rSprite();                                  //CONSTRUCTOR
            
            void draw();
            
            void setTexture(renderEngine::rTexture &t);               //APLICAR UNA TEXTURA
            void setOrigin(float x, float y);           //ESTABLECER EL PUNTO ORIGEN
            void setScale(float x, float y);            //ESTABLECER LA ESCALA
            void setPosition(float x, float y);         //ESTABLECER LA POSICION
            void setRotation(float a);                  //ESTABLECER UNA ROTACION
            bool intersects(renderEngine::rSprite sprite_);
            void rotate(float r);
            float getRotation();
            void setTextureRect(renderEngine::rIntRect rect);
            std::array<float,2> getPosition();          //DEVUELVE LA POSICION
            bool intersects(renderEngine::rRectangleShape rs);  //COLISION DE SFML PARA LOS PINCHOS
            bool intersects(renderEngine::rCircleShape cs);  //COLISION DE SFML PARA LAS EXPLOSIONES
            //sf::Sprite getSprite();
            void setColor(int r, int g, int b);
            void setColor(int r, int g, int b, int alpha);
            
        private:
            renderEngine::rIntRect rect;
            renderEngine::rTexture* texture;
            int originX,originY;
            float scaleX, scaleY;
            int posX, posY;
            int rotation;
    };
    
    
    class rView {
        friend class renderEngine;
        public:
            rView(float pos_x, float pos_y, float size_x, float size_y);        //CONSTRUCTOR
            
            void zoom(float z);                         //ZOOM A LA VISTA
            void setCenter(float x, float y);           //CENTRO DE LA VISTA
            std::array<float,2> getCenter();            //CENTRO DE LA VISTA
            void move(float x, float y);                //MOVER LA VISTA  
            void setSize(float x, float y);
            float getZoom();
        private:
            bool hasTarget_;
            float targetX;
            float targetY;
            float _zoom;
            int center_pos_x, center_pos_y, size_x, size_y;
    };
    
    class rTime {
        public:
            rTime();
            rTime(float sec);
            void setMilisec(int milisec);
            float asSeconds();                      //TIEMPO EN SEGUNDOS
            float asMilliseconds();                 //TIEMPO EN MILISEGUNDOS
            float asMicroseconds();                 //TIEMPO EN MICROSEGUNDOS
            void incrementTime(renderEngine::rTime t);
            void Zero();                            //TENER A 0 EL TIEMPO
        private:
            float _milisecond; 
    };
    
    class rClock {
        public:
            rClock();
            
            renderEngine::rTime restart();          //REINICIAR EL RELOJ
            renderEngine::rTime getElapsedTime();   //TIEMPO SIN REINICIAR EL RELOJ
        private:
            //sf::Clock clock;
            rTime start;
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
    
    class rConvexShape {
        public:
            rConvexShape();
            
            void draw();
            void setPointCount(int s);                      //NUMERO DE PUNTOS
            void setPoint(int p, float x, float y);         //ESTABLECER UN PUNTO
            void setFillColor(char c);                      //ESTABLECER UN COLOR DE FONDO
            void setOutlineColor(char c);                   //ESTABLECER UN COLOR PARA EL BORDE
            void setOutlineThickness(float f);              //ESTABLECER UN ANCHO PARA EL BORDE
            std::array<float,2> getPosition();              //CONSEGUIR POSICION
            void setPosition(float x, float y);             //ESTABLECER LA POSICION
            void move(float x, float y);                    //MOVER
            void setTexture(renderEngine::rTexture &t);                   //ESTABLECER TEXTURAS
            
        private:
            //sf::ConvexShape cs;
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
    
    void delay(Uint32 ms);

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

