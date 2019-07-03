/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   renderEngine.cpp
 * Author: pablomanez
 * 
 * Created on 21 de marzo de 2018, 15:30
 */


#include "renderEngine.h"
#include <iostream>
#include <SFML/Window/WindowStyle.hpp>

#define FRAMERATE 60

renderEngine::renderEngine()
{
        this->h = 1080;
        this->w = 1920;

        if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}else{
		//Create window
		sdl_window = SDL_CreateWindow( "SCREEN_NAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
		//SDL_WINDOW_SHOWN
        //SDL_WINDOW_FULLSCREEN_DESKTOP 
        if( sdl_window == NULL ){
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}else{
            renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
                                                    //SDL_RENDERER_ACCELERATED = HARDWARE 
                                                    
  
        }
    }


    //window.setFramerateLimit(FRAMERATE);
    //window.setVerticalSyncEnabled(true);
    _state = 0;
    
}


void                renderEngine::display   ()          {   SDL_RenderPresent(renderer);



}
void                renderEngine::close     ()          {  	SDL_DestroyWindow( sdl_window );SDL_Quit();  };


bool                renderEngine::isOpen    ()          {   return true;}   //TRUE SI LA VENTANA ESTA ABIERTA
bool                renderEngine::pollEvent (rEvent &e) {   return false;}
bool renderEngine::isJoystickConnected      (int j)     {   return false;}
void renderEngine::moveView(float x, float y) {
    //FALTA IMPLEMENTACION
}

void renderEngine::ChangeState(State* pState) {
    _state = pState;
    if(NULL != _state){
        _state->Handle();
    }
}
void renderEngine::clear(char c) {              //COLOR DEL CLEAR

int r,g,b;
    switch(c){
        case 'w':   r=255; g=255; b=255;  ;       break;
        case 'r':   r=255; g=0; b=0;       break;
        case 'y':   r=255; g=255; b=0;    break;
        default:    r=0; g=0; b=0;     break;
    }

       /* Select the color for drawing. It is set to red here. */
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

        /* Clear the entire screen to our selected color. */
        SDL_RenderClear(renderer);

}
std::array<float, 2> renderEngine::getSize() {          //X: getSize()[0] , Y: getSize()[1]
    std::array<float,2> v;

    v[0] = w;
    v[1] = h;
    
    return v;
}

std::array<float, 2> renderEngine::getViewCenter() {
    std::array<float,2> v;
    
    v[0] = w/2;
    v[1] = h/2;
    
    return v;
}



std::array<float, 2> renderEngine::getViewSize() {
    std::array<float,2> v;
    
    v[0] = w;
    v[1] = h;
    
    return v;
}


renderEngine::renderEngine(const renderEngine& orig) {}


    void renderEngine::setView(rView v){


    }                        //ESTABLECER UNA VISTA

//============================= TEXTURA =============================//
renderEngine::rTexture::rTexture() {}
renderEngine::rTexture::rTexture(std::string path) {  
      loadFromFile(path);
      
      }

void renderEngine::rTexture::loadFromFile(std::string path)  {   

    texture = NULL;
    //The final texture
   

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderEngine::Instance().renderer, loadedSurface );
        if( texture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }



    }

void renderEngine::rTexture::loadFromImage(renderEngine::rImage im, renderEngine::rIntRect ir) {
   // text.loadFromImage(im.getImage(),ir.getIntRect());

}


int             renderEngine::rTexture::getXSize()                      {  
    int w, h;
SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
return w;

          }
int             renderEngine::rTexture::getYSize()                      {      int w, h;
SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
return h;           }
SDL_Texture*    renderEngine::rTexture::getTexture()                    {   return texture;               }


//============================= SPRITE =============================//
renderEngine::rSprite::rSprite() {

 this->scaleX = 1; this->scaleY = 1; 

}

void renderEngine::rSprite::setTexture  (rTexture &t)       {   texture = &t; }
void renderEngine::rSprite::setRotation (float a)           {   this->rotation = a;              }
void renderEngine::rSprite::rotate      (float r)           {   this->rotation = r;                   }
float renderEngine::rSprite::getRotation()                  {   return rotation;        }
void renderEngine::rSprite::setTextureRect(renderEngine::rIntRect rect){  
    rect.setHeight(rect.height);
    rect.setLeft(rect.left);
    rect.setTop(rect.top);
    rect.setWidth(rect.widht);
}
void renderEngine::rSprite::setOrigin   (float x, float y)  {  this->originX = x; this->originY = y;             }
void renderEngine::rSprite::setScale    (float x, float y)  {  
    this->scaleX = x; this->scaleY = y;   
               }
void renderEngine::rSprite::setPosition (float x, float y)  {   this->posX = x; this->posY = y;            }
bool renderEngine::rSprite::intersects(renderEngine::rSprite sprite_){
    //return sprite.getGlobalBounds().intersects(sprite_.getSprite().getGlobalBounds());
    return false;
}
void renderEngine::rSprite::draw() {

    SDL_Rect dstrect;
    dstrect.x = this->posX - this->originX * this->scaleX;
    dstrect.y = this->posY - this->originY * this->scaleY;
    dstrect.w = (float)this->texture->getXSize() * this->scaleX;
    dstrect.h = (float)this->texture->getYSize() * this->scaleY;
    


    SDL_RenderCopy( renderEngine::Instance().renderer, texture->getTexture(), NULL, &dstrect );
}

bool renderEngine::rSprite::intersects(renderEngine::rRectangleShape rs) {
    //return sprite.getGlobalBounds().intersects(rs.getRectShape().getGlobalBounds());
        return false;


}
bool renderEngine::rSprite::intersects(renderEngine::rCircleShape cs) {
   // return sprite.getGlobalBounds().intersects(cs.getCircleShape().getGlobalBounds());
        return false;

}

std::array<float, 2> renderEngine::rSprite::getPosition() {
    std::array<float,2> ret;
    ret[0] = posX;
    ret[1] = posY;
    
    return ret;
}

//sf::Sprite renderEngine::rSprite::getSprite(){return sprite;}

//============================= VISTA =============================//
renderEngine::rView::rView(float pos_x, float pos_y, float size_x, float size_y):
view(sf::FloatRect(pos_x,pos_y,size_x,size_y)){ hasTarget_ = false;}

void renderEngine::rView::zoom      (float z)           {   view.zoom(z);           }
void renderEngine::rView::setCenter (float x, float y)  {   view.setCenter(x,y);    }
void renderEngine::rView::move(float x, float y)        {   view.move(x,y);         }
void renderEngine::rView::setSize(float x, float y)     {   view.setSize(x, y);     }
void renderEngine::rSprite::setColor(int r, int g, int b)   {   
   // sprite.setColor(sf::Color(r, g, b));
    
    }
void renderEngine::rSprite::setColor(int r, int g, int b, int alpha)   {  
     //sprite.setColor(sf::Color(r, g, b, alpha));
     
     }


sf::View                renderEngine::rView::getView    () {    return view;}
std::array<float, 2>    renderEngine::rView::getCenter  () {
    std::array<float, 2> ret;
    ret[0] = view.getCenter().x;
    ret[1] = view.getCenter().y;
    
    return ret;
}


//============================= RELOJ =============================//
renderEngine::rClock::rClock() {}

renderEngine::rTime renderEngine::rClock::restart() { return rTime(clock.restart()) ;}
renderEngine::rTime renderEngine::rClock::getElapsedTime() { return rTime(clock.getElapsedTime()) ;}

//============================= EVENTOS =============================//
renderEngine::rEvent::rEvent() {}

int renderEngine::rEvent::getKeyCode()              {return event.key.code;}
int renderEngine::rEvent::getJoystickButton()       {return event.joystickButton.button;}
float renderEngine::rEvent::getJoystickMoveAxis()     {return event.joystickMove.axis;}
float renderEngine::rEvent::getJoystickMovePosition() {return event.joystickMove.position;}
int renderEngine::rEvent::getJoystickId()           {return event.joystickConnect.joystickId;}


sf::Event*              renderEngine::rEvent::getEvent  () {    return &event;}
sf::Event::EventType    renderEngine::rEvent::sfType    () {    return event.type;}

//============================= TIEMPO =============================//
renderEngine::rTime::rTime() {}
renderEngine::rTime::rTime(float sec){
    time = sf::seconds(sec);
}
renderEngine::rTime::rTime(sf::Time tim){
    time = tim;
}


float renderEngine::rTime::asSeconds        ()  {   return time.asSeconds();}
float renderEngine::rTime::asMilliseconds   ()  {   return time.asMilliseconds();}
float renderEngine::rTime::asMicroseconds   ()  {   return time.asMicroseconds();}
void renderEngine::rTime::Zero              ()  {   time = sf::Time::Zero;}
void renderEngine::rTime::incrementTime(renderEngine::rTime t){ time += t.getTime();}
sf::Time renderEngine::rTime::getTime()         {   return time; }

//============================= CONVEXSHAPE =============================//
renderEngine::rConvexShape::rConvexShape() {
}

void renderEngine::rConvexShape::draw() {
    renderEngine* sfml;
    //sfml->Instance().getWindow()->draw(cs);
}
void renderEngine::rConvexShape::setPointCount      (int s)                     {   cs.setPointCount(s);}
void renderEngine::rConvexShape::setOutlineThickness(float f)                   {   cs.setOutlineThickness(f);}
void renderEngine::rConvexShape::setPoint           (int p, float x, float y)   {   cs.setPoint(p,sf::Vector2f(x,y));}
void renderEngine::rConvexShape::move               (float x, float y)          {   cs.move(x,y);}
void renderEngine::rConvexShape::setPosition        (float x, float y)          {   cs.setPosition(x,y);}
void renderEngine::rConvexShape::setTexture         (renderEngine::rTexture &t)               { 
    //  cs.setTexture(t.getTexture());
    return;
      }
void renderEngine::rConvexShape::setFillColor(char c) {
    switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'm':   cs.setFillColor(sf::Color::Magenta);        break;
        case 'w':   cs.setFillColor(sf::Color::White);          break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    cs.setFillColor(sf::Color::Black);          break;
    }
}
void renderEngine::rConvexShape::setOutlineColor(char c) {
    switch(c){
        case 'r':   cs.setOutlineColor(sf::Color::Red);    break;
        case 'g':   cs.setOutlineColor(sf::Color::Green);  break;
        default:    break;
    }
}
std::array<float, 2> renderEngine::rConvexShape::getPosition() {
    std::array<float,2> a;
    
    a[0] = cs.getPosition().x;
    a[1] = cs.getPosition().y;
    
    return a;
}


//============================= RECTANGLESHAPE =============================//
renderEngine::rRectangleShape::rRectangleShape() {
    this->posX=0;
    this->posY=0;
    this->originX=0;
    this->originY=0;

}

renderEngine::rRectangleShape::rRectangleShape(float x, float y){
    this->sizeX=x;
    this->sizeY=y;
    this->posX=0;
    this->posY=0;
    this->originX=0;
    this->originY=0;
}

void renderEngine::rRectangleShape::draw() {
    SDL_Rect dstrect;
    dstrect.x = this->posX - this->originX ;
    dstrect.y = this->posY - this->originY ;
    dstrect.w = this->sizeX ;
    dstrect.h = this->sizeY ;
    
    SDL_RenderCopy( renderEngine::Instance().renderer, texture->getTexture(), NULL, &dstrect );
}
void renderEngine::rRectangleShape::setTexture  (rTexture &t)       {   
   texture = &t;
    
    }
void renderEngine::rRectangleShape::setPosition (float x, float y)  {   this->posX = x; this->posY = y;}
void renderEngine::rRectangleShape::setSize     (float x, float y)  {   this->sizeX =x  ; this->sizeY = y;}
void renderEngine::rRectangleShape::move        (float x, float y)  {   }
void renderEngine::rRectangleShape::setOrigin   (float x, float y)  {  this->originX = x; this->originY;}
void renderEngine::rRectangleShape::setRotation (float a)           {  this->rotation = a;}
void renderEngine::rRectangleShape::rotate      (float a)           {  }

std::array<float, 2> renderEngine::rRectangleShape::getSize() {
    std::array<float,2> ret;
    
    ret[0] =sizeX;
    ret[1] = sizeY;
    
    return ret;
}

void renderEngine::rRectangleShape::setFillColor(char c) {
      /* switch(c){
      case 't':   rs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   rs.setFillColor(sf::Color::Red);            break;
        case 'g':   rs.setFillColor(sf::Color::Green);          break;
        case 'b':   rs.setFillColor(sf::Color::Blue);           break;
        case 'y':   rs.setFillColor(sf::Color::Yellow);         break;
        case 'k':   rs.setFillColor(sf::Color::Black);          break;
        default:    break;
    }*/
}

void renderEngine::rRectangleShape::setFillRGBAColor(int r, int g, int b, int a) {
   // sf::Color color(r,g,b,a);
   // rs.setFillColor(color);
}

void renderEngine::rRectangleShape::setOutlineColor(char c) {
      /* switch(c){
        case 't':   rs.setOutlineColor(sf::Color::Transparent);    break;
        case 'r':   rs.setOutlineColor(sf::Color::Red);            break;
        case 'g':   rs.setOutlineColor(sf::Color::Green);          break;
        case 'b':   rs.setOutlineColor(sf::Color::Blue);           break;
        case 'y':   rs.setOutlineColor(sf::Color::Yellow);         break;
        case 'k':   rs.setOutlineColor(sf::Color::Black);          break;
        default:    break;
    }  */
}

void renderEngine::rRectangleShape::setOutlineThickness(float f) {

}

std::array<float, 2> renderEngine::rRectangleShape::getPosition() {
    std::array<float, 2> ret;
    ret[0] = this->posX;
    ret[1] = this->posY;
    
    return ret;
}


//============================= INTRECT =============================//
renderEngine::rIntRect::rIntRect() {
    left = 0;
    top = 0;
    widht = 0;
    height = 0;
}

renderEngine::rIntRect::rIntRect(int x, int y, int w, int h) :  ir{x,y,w,h} {
    left = x;
    top = y;
    widht = w;
    height = h;
}

void renderEngine::rIntRect::setTop(int t) {
    top = t;
    ir.y = t;
}
void renderEngine::rIntRect::setLeft(int l) {
    left = l;
    ir.x = l;
}
void renderEngine::rIntRect::setWidth(int w) {
    widht = w;
    ir.w = w;
}
void renderEngine::rIntRect::setHeight(int h) {
    height = h;
    ir.h = h;
}

bool renderEngine::rIntRect::contains(float x, float y) {

    if(ir.x - x < ir.w && ir.y - y < ir.h){
        return true;

    }
    return false;
}

SDL_Rect renderEngine::rIntRect::getIntRect() {
    return ir;
}


//============================= IMAGE =============================//
renderEngine::rImage::rImage() {}

void renderEngine::rImage::loadFromFIle(std::string path) { im.loadFromFile(path);
}

sf::Image renderEngine::rImage::getImage() {
    return im;
}

//============================= TEXT =============================//
renderEngine::rText::rText(){    
    //font.loadFromFile("assets/fonts/8-bit_pusab.ttf");
}
void renderEngine::rText::draw() {
    renderEngine* sfml;
    //sfml->Instance().getWindow()->draw(txt);
}
void renderEngine::rText::setPosition       (float x, float y)      {   txt.setPosition(x,y);}
void renderEngine::rText::setScale          (float fx, float fy)    {   txt.setScale(fx,fy);}
void renderEngine::rText::setString         (std::string str)       {   txt.setString(str);}
void renderEngine::rText::setCharacterSize  (int s)                 {   txt.setCharacterSize(s);}
void renderEngine::rText::setFont           (rFont &font)           {   txt.setFont(*font.getFont());}
void renderEngine::rText::setOrigin         (float x, float y)      {   txt.setOrigin(x,y);}

std::array<float, 2> renderEngine::rText::getSize() {
    std::array<float,2> ret;
    
    ret[0] = txt.getGlobalBounds().width;
    ret[1] = txt.getGlobalBounds().height;
    
    return ret;
}

void renderEngine::rText::setFillColor(char c) {
    switch(c){
        case 't':   txt.setFillColor(sf::Color::Transparent);    break;
        case 'r':   txt.setFillColor(sf::Color::Red);            break;
        case 'g':   txt.setFillColor(sf::Color::Green);          break;
        case 'b':   txt.setFillColor(sf::Color::Blue);           break;
        case 'y':   txt.setFillColor(sf::Color::Yellow);         break;
        case 'k':   txt.setFillColor(sf::Color::Black);          break;
        case 'w':   txt.setFillColor(sf::Color::White);          break;
        default:    break;
    }
}

sf::Color renderEngine::rText::getFillColor() {return txt.getFillColor();};

//============================= FONT =============================//
renderEngine::rFont::rFont() {}
void renderEngine::rFont::loadFromFile  (std::string str)   {   font.loadFromFile(str);}
sf::Font* renderEngine::rFont::getFont   ()                 {   return &font;}

//============================= CIRCLESHAPE =============================//

renderEngine::rCircleShape::rCircleShape(float r, int pc) : cs(r,pc) {}

void renderEngine::rCircleShape::draw() {
    renderEngine* sfml;
    //sfml->Instance().getWindow()->draw(cs);
}

void renderEngine::rCircleShape::setFillColor(char c) {
    switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    break;
    }
}

void renderEngine::rCircleShape::setRadius(float r) {
    cs.setRadius(r);
}

void renderEngine::rCircleShape::setPosition(float x, float y) {
    cs.setPosition(x,y);
}

void renderEngine::rCircleShape::setOrigin(float x, float y) {
    cs.setOrigin(x,y);
}

sf::CircleShape renderEngine::rCircleShape::getCircleShape() {
    return cs;
}

std::array<float, 2> renderEngine::rCircleShape::getPosition() {
    std::array<float,2> ret;
    
    ret[0] = cs.getPosition().x;
    ret[1] = cs.getPosition().y;
    
    return ret;
}













