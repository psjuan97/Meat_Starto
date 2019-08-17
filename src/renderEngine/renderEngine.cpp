
#include "renderEngine.h"
#include <iostream>




#include <ppu-lv2.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <sysutil/video.h>
#include <rsx/gcm_sys.h>
#include <rsx/rsx.h>

#include <io/pad.h>



#include <sysmodule/sysmodule.h>
#include <sysutil/sysutil.h>
//#include <sysutil/events.h>


//Include SDL functions and datatypes
#include "SDL/SDL.h"
  

#include <net/net.h>
#include <netinet/in.h>

static int SocketFD;
#define DEBUG_IP "192.168.0.113"
#define DEBUG_PORT 18194



void debugPrintf(const char* fmt, ...)
{
  char buffer[0x800];
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, arg);
  va_end(arg);
  netSend(SocketFD, buffer, strlen(buffer), 0);
}

void debugInit()
{
      netInitialize();

  struct sockaddr_in stSockAddr;
  SocketFD = netSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&stSockAddr, 0, sizeof stSockAddr);

  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(DEBUG_PORT);
  inet_pton(AF_INET, DEBUG_IP, &stSockAddr.sin_addr);

  netConnect(SocketFD, (struct sockaddr *)&stSockAddr, sizeof stSockAddr);
	
  debugPrintf("network debug module initialized\n") ;
  debugPrintf("ready to have a lot of fun\n") ;
}


/* 
#else

#define BASEDIR ""




void debugPrintf(const char* fmt, ...)
{

}

void debugInit()
{

}



#endif
*/

Uint32 getpixel(SDL_Surface *surface,int x,int y){
  int bpp = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  switch(bpp) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *)p;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *)p;
    default:
      return 0;
  }
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp) {
    case 1:
        *p = pixel;
        break;
    case 2:
        *(Uint16 *)p = pixel;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void putpixel16(SDL_Surface *surface, int x, int y, Uint32 pixel){
	*((Uint16 *)surface->pixels+y*surface->pitch/2+x)=pixel;
}





void scalesurface(
	SDL_Surface *source,SDL_Surface *destination,
	float sourcex1,float sourcex2,float sourcey1,float sourcey2,
	float destx1,float destx2,float desty1,float desty2){
	
	if(sourcex1==0 && sourcex2==320-1 && destx1==0 && destx2==640-1
	&& sourcey1==0 && sourcey2==240-1 && desty1==0 && desty2==480-1
	&& source->format->BitsPerPixel==16 && destination->format->BitsPerPixel==16){
	
		SDL_Rect temprect={0,0,2,2};
		Uint16* pixelpositionsource=(Uint16*)source->pixels;
		for(int y=0;y<240;y++){
			for(int x=0;x<320;x++){
				SDL_FillRect(destination,&temprect,*pixelpositionsource);
				temprect.x += 2;
				pixelpositionsource++;
			}
			temprect.x = 0;
			temprect.y += 2;
		}
	
	}else{
	
		float xdif=(sourcex1-sourcex2)/(destx1-destx2);
		float ydif=(sourcey1-sourcey2)/(desty1-desty2);	
		float xuse=sourcex1;
		float yuse=sourcey1;
		for(int y=desty1;y<desty2+1;y++){
			xuse=sourcex1;
			for(int x=destx1;x<destx2+1;x++){
				xuse+=xdif;
				if(x>=0 && x<destination->w
				&& y>=0 && y<destination->h
				&& (int)xuse>=0 && (int)xuse<source->w
				&& (int)yuse>=0 && (int)yuse<source->h)
					putpixel(destination,x,y,getpixel(source,(int)xuse,(int)yuse));
			}
			yuse+=ydif;
		}
	
	}

}





#define FRAMERATE 60
#define W  1920.0f//1280.0f
#define H   1080.0f //720.0f 
const int SCREEN_BPP = 32;

#define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))




SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
       // optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            //SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGBA( optimizedImage->format, 0, 0, 0 ,0) );
            //SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0) );

        }
        debugPrintf("Image %s loaded!\n", filename.c_str());
    }else{

          debugPrintf("Image %s NOT loaded!\n", filename.c_str());

    }

    //Return the optimized surface
    return optimizedImage;
}




renderEngine::renderEngine() :  camera(W/2.0f,H/2.0f,W,H)
{
    this->h = H;
    this->w = W;

  debugInit();

  debugPrintf("\nNET debugger working!\n");




    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
    {
        debugPrintf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }else{
        //Create window
        renderer = SDL_SetVideoMode( w, h, SCREEN_BPP, SDL_SWSURFACE );
       
        
    }

    if( TTF_Init() == -1 ){
        debugPrintf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    _state = 0;
    
}


void renderEngine::display() {   
    SDL_Flip(renderer);
}

void                renderEngine::close     ()          {  	
  
    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
    
    renderer = nullptr; 
    
     };
void                renderEngine::delay     (Uint32 ms)          {  SDL_Delay(ms);  };



bool                renderEngine::isOpen    ()          {   return renderer != nullptr;}   //TRUE SI LA VENTANA ESTA ABIERTA

bool                renderEngine::pollEvent (renderEngine::rEvent &e) {   
    return SDL_PollEvent(&e.event);
}
bool renderEngine::isJoystickConnected      (int j)     {   return false;}
void renderEngine::moveView(float x, float y) {
    //FALTA IMPLEMENTACION
}

void renderEngine::ChangeState(State* pState) {
                debugPrintf( "changing stage... \n" );

    _state = pState;
    if(NULL != _state){
        _state->Handle();
    }
            debugPrintf( "State changed Okey \n" );

}
void renderEngine::clear(char c) {              //COLOR DEL CLEAR
/* 
int r,g,b;
    switch(c){
        case 'w':   r=255; g=255; b=255;  ;       break;
        case 'r':   r=255; g=0; b=0;       break;
        case 'y':   r=255; g=255; b=0;    break;
        default:    r=0; g=0; b=0;     break;
    }

       // Select the color for drawing. It is set to red here.
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);*/

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

    std::string finalpath = BASEDIR + path;
    texture = load_image(finalpath.c_str());


    }

void renderEngine::rTexture::loadFromImage(renderEngine::rImage im, renderEngine::rIntRect ir) {



    printf("loadFromImage(renderEngine::rImage im, renderEngine::rIntRect ir)");
}


int renderEngine::rTexture::getXSize()  {  
    SDL_Rect rect;
    SDL_GetClipRect(this->texture,&rect);
    printf("rect.w = %i \n ", rect.w);

    return rect.w;
}

int renderEngine::rTexture::getYSize() {   
    SDL_Rect rect;
    SDL_GetClipRect(this->texture,&rect);
    printf("rect.h = %i \n ", rect.h);

    return rect.h;
 }
 
SDL_Surface*    renderEngine::rTexture::getTexture()                    {   return texture;               }


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
    
    this->scaleX = x; 
    this->scaleY = y;   

    printf("SetScale\n");
        printf("scaleX %f, \n", scaleX);

}

void renderEngine::rSprite::setPosition (float x, float y)  {   this->posX = x; this->posY = y;            }
bool renderEngine::rSprite::intersects(renderEngine::rSprite sprite_){
    //return sprite.getGlobalBounds().intersects(sprite_.getSprite().getGlobalBounds());
    return false;
}
void renderEngine::rSprite::draw() {
    //printf("------------------draw-----------------------\n");

    //printf("data: zoomview %f ,  this->scaleX %f , this->originX %i\n",  (float)renderEngine::Instance().camera.getZoom() , this->scaleX, this->originX);
    //printf("POSX(x: %i, y: %i \n", this->posX ,  this->posY);


    SDL_Rect dstrect;
    dstrect.x =  ((float) ((this->posX - ( renderEngine::Instance().camera.getCenter()[0] - renderEngine::Instance().camera.size_x/2) )  - this->originX * this->scaleX)  / renderEngine::Instance().camera.getZoom());
    dstrect.y =  ((float) ((this->posY - ( renderEngine::Instance().camera.getCenter()[1] - renderEngine::Instance().camera.size_y/2) )  - this->originY * this->scaleY)  / renderEngine::Instance().camera.getZoom());

    dstrect.w = ROUND_2_INT( (float) this->rect.widht * (float)this->scaleX / (float)renderEngine::Instance().camera.getZoom() ) ;
    dstrect.h = ROUND_2_INT( (float) this->rect.height *(float)this->scaleY / (float)renderEngine::Instance().camera.getZoom() );
    





    SDL_Rect srcrect;
    srcrect.x = this->rect.left ;
    srcrect.y = this->rect.top ;
    srcrect.w = (float) this->rect.widht;//
    srcrect.h = (float)this->rect.height;//* renderEngine::Instance().zoomview;

    //srcrect.w = (float)this->texture->getXSize();//
    //srcrect.h = (float)this->texture->getYSize();//* renderEngine::Instance().zoomview;



/* 

    Uint32 rmask, gmask, bmask, amask;


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    printf("srcrect(x: %d, y: %d, w %d, h %d \n", srcrect.x ,  srcrect.y,  srcrect.w,  srcrect.h);
    printf("this->rect.widht = %i \n", this->rect.widht);
    printf("dstrect(x: %i, y: %i, w %i, h %i \n", dstrect.x ,  dstrect.y,  dstrect.w,  dstrect.h);

SDL_Surface * finalSurface = SDL_CreateRGBSurface(SDL_SRCALPHA,   dstrect.w, dstrect.h, 32, rmask, gmask, bmask, amask);
 
    if(finalSurface == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
scalesurface( texture->getTexture() ,finalSurface,
	srcrect.x, srcrect.w ,srcrect.y,srcrect.h,
	dstrect.x, dstrect.w ,dstrect.y,dstrect.h);

    srcrect.x = this->rect.left ;
    srcrect.y = this->rect.top ;
    srcrect.w = (float)dstrect.w;//
    srcrect.h = (float)dstrect.h;//* renderEngine::Instance().zoomview;


    printf("srcrect(x: %i, y: %i, w %i, h %i \n", srcrect.x ,  srcrect.y,  srcrect.w,  srcrect.h);
    printf("this->rect.widht = %i \n", this->rect.widht);
    printf("dstrect(x: %i, y: %i, w %i, h %i \n", dstrect.x ,  dstrect.y,  dstrect.w,  dstrect.h);


*/
    if(texture->getTexture()  != NULL){
        SDL_BlitSurface( texture->getTexture() ,&srcrect,renderEngine::Instance().renderer,&dstrect);
    }

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

float  renderEngine::rView::getZoom(){
    return _zoom;
}

void renderEngine::rView::zoom      (float z)           {   
    //printf("zoom %f",z);
    
    this->_zoom = z;  
    this->size_x = this->size_x * z;
    this->size_y = this->size_y * z;         
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
renderEngine::rClock::rClock() {
    this->start.Zero();
}

renderEngine::rTime renderEngine::rClock::restart() { 
    rTime timeToReturn;
    timeToReturn.setMilisec((int)SDL_GetTicks() - (int)this->start.asMilliseconds());
    start.setMilisec((int)SDL_GetTicks());
    return timeToReturn;
}

renderEngine::rTime renderEngine::rClock::getElapsedTime() { 
    return rTime((int)SDL_GetTicks() - (int)this->start.asMilliseconds());
}

//============================= EVENTOS =============================//
renderEngine::rEvent::rEvent() {}

int renderEngine::rEvent::getKeyCode()              {return event.key.keysym.sym;}
int renderEngine::rEvent::getJoystickButton()       {return 0;}
float renderEngine::rEvent::getJoystickMoveAxis()     {return 0;}
float renderEngine::rEvent::getJoystickMovePosition() {return 0;}
int renderEngine::rEvent::getJoystickId()           {return 0;}


unsigned int   renderEngine::rEvent::sfType    () {    return event.type;}

//============================= TIEMPO =============================//
renderEngine::rTime::rTime() {
    _milisecond = 0;
}
renderEngine::rTime::rTime(float sec){
    this->_milisecond = sec * 1000.0f;
}

void renderEngine::rTime::setMilisec(int _milisecond){
    this->_milisecond = (float)_milisecond;
}

float renderEngine::rTime::asSeconds        ()  {   
    return this->_milisecond / 1000 ;

}
float renderEngine::rTime::asMilliseconds   ()  {   
    return this->_milisecond;
}
float renderEngine::rTime::asMicroseconds   ()  {  
     return this->_milisecond * 1000;
}
void renderEngine::rTime::Zero              ()  {   
    this->_milisecond = 0;
}
void renderEngine::rTime::incrementTime(renderEngine::rTime t){ 
    this->_milisecond += t.asMilliseconds();
}


//============================= CONVEXSHAPE =============================//
renderEngine::rConvexShape::rConvexShape() {
}

void renderEngine::rConvexShape::draw() {
    renderEngine* sfml;
    //sfml->Instance().getWindow()->draw(cs);
}
void renderEngine::rConvexShape::setPointCount      (int s)                     {   
   // cs.setPointCount(s);
}
void renderEngine::rConvexShape::setOutlineThickness(float f)                   {  
     //cs.setOutlineThickness(f);
    }
void renderEngine::rConvexShape::setPoint           (int p, float x, float y)   { 
     // cs.setPoint(p,sf::Vector2f(x,y));
    }
void renderEngine::rConvexShape::move               (float x, float y)          {  
    // cs.move(x,y);
     
    }
void renderEngine::rConvexShape::setPosition        (float x, float y)          { 
      //cs.setPosition(x,y);
      
      }
void renderEngine::rConvexShape::setTexture         (renderEngine::rTexture &t)               { 
    //  cs.setTexture(t.getTexture());
    return;
      }
void renderEngine::rConvexShape::setFillColor(char c) {
  /*  switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'm':   cs.setFillColor(sf::Color::Magenta);        break;
        case 'w':   cs.setFillColor(sf::Color::White);          break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    cs.setFillColor(sf::Color::Black);          break;
    } */
}
void renderEngine::rConvexShape::setOutlineColor(char c) {
   /*  switch(c){
        case 'r':   cs.setOutlineColor(sf::Color::Red);    break;
        case 'g':   cs.setOutlineColor(sf::Color::Green);  break;
        default:    break;
    }*/
}
std::array<float, 2> renderEngine::rConvexShape::getPosition() {
    std::array<float,2> a;
    
   // a[0] = cs.getPosition().x;
    //a[1] = cs.getPosition().y;
    
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
    srcrect.w = this->sizeX * renderEngine::Instance().camera.getZoom() ;
    srcrect.h = this->sizeY * renderEngine::Instance().camera.getZoom();


    if(texture != nullptr){
        SDL_BlitSurface( texture->getTexture(),&srcrect,renderEngine::Instance().renderer,&dstrect);
    }else{
        //SDL_FillRect(renderEngine::Instance().renderer,&dstrect, 0)   ;
    }

    // debugPrintf("END  rRectangleShape -> draw\n");

    
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
      //  SDL_SetRenderDrawColor(renderEngine::Instance().renderer, r, g, b, 255);


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
       // SDL_SetRenderDrawColor(renderEngine::Instance().renderer, r, g, b, a);

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
    std::string finalpath = BASEDIR + path;
    texture = load_image(finalpath.c_str());
}



//============================= TEXT =============================//
renderEngine::rText::rText(){   
        std::string finalpath = "assets/fonts/8-bit_pusab.ttf";
 
    font.loadFromFile(finalpath.c_str());
}

//TODO no crear todo el rato la txtura
void renderEngine::rText::draw() {

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = posX;  //controls the rect's x coordinate 
    Message_rect.y = posY; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

   // SDL_RenderCopy(renderEngine::Instance().renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    //Don't forget too free your surface and texture


}
void renderEngine::rText::setPosition       (float x, float y)      { 
    this->posX = x;
    this->posY = y;
 }
void renderEngine::rText::setScale          (float fx, float fy)    { 


 }
void renderEngine::rText::setString         (std::string str)       { 
        SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
    this->text = str;

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->font.font, text.c_str() , White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

     //Message = SDL_CreateTextureFromSurface(renderEngine::Instance().renderer, surfaceMessage); //now you can convert it into a texture
SDL_FreeSurface(surfaceMessage);
 }
void renderEngine::rText::setCharacterSize  (int s)                 { 


 }
void renderEngine::rText::setFont           (renderEngine::rFont &font)           {
    this->font = font;

  }
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

int renderEngine::rText::getFillColor() { 
    return 0;
};

//============================= FONT =============================//
renderEngine::rFont::rFont() {
    font = nullptr;
}
void renderEngine::rFont::loadFromFile  (std::string str)   { 

    std::string finalpath = BASEDIR + str;
    font = TTF_OpenFont(finalpath.c_str(), 80); //this opens a font style and sets a size
    if(!font) {
        debugPrintf("Error loading font: %s", finalpath.c_str())    ;
        exit(0);
    }else{ 
        debugPrintf("Font %s , loaded", finalpath.c_str())    ;
    }
 }


//============================= CIRCLESHAPE =============================//

renderEngine::rCircleShape::rCircleShape(float r, int pc) {}

void renderEngine::rCircleShape::draw() {
    renderEngine* sfml;
    //sfml->Instance().getWindow()->draw(cs);
}

void renderEngine::rCircleShape::setFillColor(char c) {
    /* switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    break;
    }*/
}

void renderEngine::rCircleShape::setRadius(float r) {
   // cs.setRadius(r);
}

void renderEngine::rCircleShape::setPosition(float x, float y) {
   // cs.setPosition(x,y);
}

void renderEngine::rCircleShape::setOrigin(float x, float y) {
   // cs.setOrigin(x,y);
}



std::array<float, 2> renderEngine::rCircleShape::getPosition() {
    std::array<float,2> ret;
    
   // ret[0] = cs.getPosition().x;
   // ret[1] = cs.getPosition().y;
    
    return ret;
}













