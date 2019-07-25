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

#define FRAMERATE 60
#define W 1920.0f
#define H 1080.0f 
renderEngine::renderEngine() :  camera(W/2.0f,H/2.0f,W,H)
{
        zoomview = 1;
        this->h = H;
        this->w = W;

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
void                renderEngine::close     ()          {  	SDL_DestroyWindow( sdl_window );SDL_Quit();sdl_window = nullptr;  };
void                renderEngine::delay     (Uint32 ms)          {  SDL_Delay(ms);  };



bool                renderEngine::isOpen    ()          {   return sdl_window != nullptr;}   //TRUE SI LA VENTANA ESTA ABIERTA

bool                renderEngine::pollEvent (renderEngine::rEvent &e) {   
    return SDL_PollEvent(&e.event);
}
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
    
    v[0] = camera.getCenter()[0] ;
    v[1] = camera.getCenter()[1] ;
    
    return v;
}



std::array<float, 2> renderEngine::getViewSize() {
    std::array<float,2> v;
    
    v[0] = camera.size_x ;
    v[1] = camera.size_y ;
    
    return v;
}




void renderEngine::setView(renderEngine::rView v){
    this->zoomview = v._zoom;
    camera = v;
}                        //ESTABLECER UNA VISTA

//============================= TEXTURA =============================//
renderEngine::rTexture::rTexture() {
        texture = NULL;

}
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



    printf("loadFromImage(renderEngine::rImage im, renderEngine::rIntRect ir)");
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

 this->scaleX = 1; 
 this->scaleY = 1; 
 this->originX = 0;
 this->originY = 0;

  this->posX = 20; this->posY = 20; 


}

void renderEngine::rSprite::setTexture  (rTexture &t)       {   
    texture = &t; 
    this->rect.setHeight(t.getYSize());
    this->rect.setLeft(0);
    this->rect.setTop(0);
    this->rect.setWidth(t.getXSize());
}


void renderEngine::rSprite::setRotation (float a)           {   this->rotation = a;              }
void renderEngine::rSprite::rotate      (float r)           {   this->rotation = r;                   }
float renderEngine::rSprite::getRotation()                  {   return rotation;        }

void renderEngine::rSprite::setTextureRect(renderEngine::rIntRect rect){  
    this->rect.setHeight(rect.height);
    this->rect.setLeft(rect.left);
    this->rect.setTop(rect.top);
    this->rect.setWidth(rect.widht);
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
    //printf("data: zoomview %f ,  this->scaleX %f , this->originX %i\n",  renderEngine::Instance().zoomview , this->scaleX, this->originX);
    //printf("POSX(x: %i, y: %i \n", this->posX ,  this->posY);


    SDL_Rect dstrect;
    dstrect.x = (int) (this->posX - ( renderEngine::Instance().camera.getCenter()[0] - renderEngine::Instance().camera.size_x/2)) / renderEngine::Instance().zoomview - this->originX * this->scaleX  / renderEngine::Instance().zoomview;

    dstrect.y = (int) (this->posY - (  renderEngine::Instance().camera.getCenter()[1] - renderEngine::Instance().camera.size_y/2 )) / renderEngine::Instance().zoomview - this->originY * this->scaleY  / renderEngine::Instance().zoomview ;

    dstrect.w = (float) this->rect.widht * (float)this->scaleX / (float)renderEngine::Instance().zoomview ;
    dstrect.h = (float) this->rect.height * (float)this->scaleY / (float)renderEngine::Instance().zoomview;
    





    SDL_Rect srcrect;
    srcrect.x = this->rect.left ;
    srcrect.y = this->rect.top ;
    srcrect.w = (float) this->rect.widht;//
    srcrect.h = (float)this->rect.height;//* renderEngine::Instance().zoomview;

    //srcrect.w = (float)this->texture->getXSize();//
    //srcrect.h = (float)this->texture->getYSize();//* renderEngine::Instance().zoomview;

    //printf("srcrect(x: %d, y: %d, w %d, h %d \n", srcrect.x ,  srcrect.y,  srcrect.w,  srcrect.h);
    //printf("dstrect(x: %d, y: %d, w %d, h %d \n", dstrect.x ,  dstrect.y,  dstrect.w,  dstrect.h);

    SDL_RenderCopy( renderEngine::Instance().renderer, texture->getTexture(), &srcrect, &dstrect );
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
renderEngine::rView::rView(float pos_x, float pos_y, float size_x, float size_y){ 
    hasTarget_ = false;
    center_pos_x = pos_x;
    center_pos_y =  pos_y;
    this->size_x =  size_x;
    this->size_y = size_y;
    _zoom = 1;
}

void renderEngine::rView::zoom      (float z)           {   
    printf("zoom %f",z);
    
    this->_zoom = z;           
}

void renderEngine::rView::setCenter (float x, float y)  {   
        center_pos_x = x;
        center_pos_y =  y;
}

void renderEngine::rView::move(float x, float y)        {  
    setCenter(center_pos_x + x, center_pos_y + y);
}

void renderEngine::rView::setSize(float x, float y)     {  
    size_x =  x;
    size_y = y;
}



void renderEngine::rSprite::setColor(int r, int g, int b)   {   
// sprite.setColor(sf::Color(r, g, b));

}
void renderEngine::rSprite::setColor(int r, int g, int b, int alpha)   {  
//sprite.setColor(sf::Color(r, g, b, alpha));

}


std::array<float, 2>    renderEngine::rView::getCenter  () {
    std::array<float, 2> ret;
    ret[0] = this->center_pos_x;
    ret[1] = this->center_pos_y;
    
    return ret;
}


//============================= RELOJ =============================//
renderEngine::rClock::rClock() {}

renderEngine::rTime renderEngine::rClock::restart() { return rTime(clock.restart()) ;}
renderEngine::rTime renderEngine::rClock::getElapsedTime() { return rTime(clock.getElapsedTime()) ;}

//============================= EVENTOS =============================//
renderEngine::rEvent::rEvent() {}

int renderEngine::rEvent::getKeyCode()              {return event.key.keysym.sym;}
int renderEngine::rEvent::getJoystickButton()       {return 0;}
float renderEngine::rEvent::getJoystickMoveAxis()     {return 0;}
float renderEngine::rEvent::getJoystickMovePosition() {return 0;}
int renderEngine::rEvent::getJoystickId()           {return 0;}


unsigned int   renderEngine::rEvent::sfType    () {    return event.type;}

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

    texture = nullptr;
}

renderEngine::rRectangleShape::rRectangleShape(float x, float y){
    this->sizeX=x;
    this->sizeY=y;
    this->posX=0;
    this->posY=0;
    this->originX=0;
    this->originY=0;
    this->texture = nullptr;
}

void renderEngine::rRectangleShape::draw() {

    SDL_Rect dstrect;
    dstrect.x = this->posX - this->originX ;
    dstrect.y = this->posY - this->originY ;
    dstrect.w = this->sizeX ;
    dstrect.h = this->sizeY ;
    

    SDL_Rect srcrect;
    srcrect.x = 0 ;
    srcrect.y = 0 ;
    srcrect.w = this->sizeX * renderEngine::Instance().zoomview ;
    srcrect.h = this->sizeY * renderEngine::Instance().zoomview;


    if(texture != nullptr){
        SDL_RenderCopy( renderEngine::Instance().renderer, texture->getTexture(), &srcrect, &dstrect );
    }else{
        SDL_RenderFillRect(renderEngine::Instance().renderer,&dstrect )   ;
    }
    
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
      
      
      int r,g,b;
        switch(c){
            case 'w':   r=255; g=255; b=255;  ;       break;
            case 'r':   r=255; g=0; b=0;       break;
            case 'y':   r=255; g=255; b=0;    break;
            default:    r=0; g=0; b=0;     break;
        }

       /* Select the color for drawing. It is set to red here. */
        SDL_SetRenderDrawColor(renderEngine::Instance().renderer, r, g, b, 255);


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
        SDL_SetRenderDrawColor(renderEngine::Instance().renderer, r, g, b, a);

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

void renderEngine::rImage::loadFromFIle(std::string path) { 
    
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



//============================= TEXT =============================//
renderEngine::rText::rText(){    
    //font.loadFromFile("assets/fonts/8-bit_pusab.ttf");
}
void renderEngine::rText::draw() {

    //sfml->Instance().getWindow()->draw(txt);
}
void renderEngine::rText::setPosition       (float x, float y)      {  }
void renderEngine::rText::setScale          (float fx, float fy)    {  }
void renderEngine::rText::setString         (std::string str)       {  }
void renderEngine::rText::setCharacterSize  (int s)                 {  }
void renderEngine::rText::setFont           (rFont &font)           {  }
void renderEngine::rText::setOrigin         (float x, float y)      {  }

std::array<float, 2> renderEngine::rText::getSize() {
    std::array<float,2> ret;
    
    ret[0] = -1;
    ret[1] = -1;
    
    return ret;
}

void renderEngine::rText::setFillColor(char c) {
    /*switch(c){
        case 't':   txt.setFillColor(sf::Color::Transparent);    break;
        case 'r':   txt.setFillColor(sf::Color::Red);            break;
        case 'g':   txt.setFillColor(sf::Color::Green);          break;
        case 'b':   txt.setFillColor(sf::Color::Blue);           break;
        case 'y':   txt.setFillColor(sf::Color::Yellow);         break;
        case 'k':   txt.setFillColor(sf::Color::Black);          break;
        case 'w':   txt.setFillColor(sf::Color::White);          break;
        default:    break;
    } */
}

sf::Color renderEngine::rText::getFillColor() { return txt.getFillColor();};

//============================= FONT =============================//
renderEngine::rFont::rFont() {}
void renderEngine::rFont::loadFromFile  (std::string str)   {  }
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













