
#include "renderEngine.h"

#include <iostream>

#define FRAMERATE 60
#define W 1920.0f
#define H 1080.0f 
#define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))

renderEngine::renderEngine() :  camera(W/2.0f,H/2.0f,W,H)
{
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

    if( TTF_Init() == -1 ){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    _state = 0;
    
}


void renderEngine::display() {   
    SDL_RenderPresent(renderer);
}

void                renderEngine::close     ()          {  	SDL_DestroyWindow( sdl_window );SDL_Quit();sdl_window = nullptr;  };
void                renderEngine::delay     (Uint32 ms)          {  SDL_Delay(ms);  };

int  renderEngine::getTicks(){  
return (int)SDL_GetTicks();
}

void renderEngine::drawTexture(rTexture *texture, texture_prop propiedades, rIntRect rect){


    SDL_Rect dstrect;
    dstrect.x =  ((float) ((propiedades.posX - ( renderEngine::Instance().camera.getCenter()[0] - renderEngine::Instance().camera.size_x/2) )  - propiedades.originX * propiedades.scaleX)  / renderEngine::Instance().camera.getZoom());
    dstrect.y =  ((float) ((propiedades.posY - ( renderEngine::Instance().camera.getCenter()[1] - renderEngine::Instance().camera.size_y/2) )  - propiedades.originY * propiedades.scaleY)  / renderEngine::Instance().camera.getZoom());

    dstrect.w = ROUND_2_INT( (float) rect.widht * (float)propiedades.scaleX / (float)renderEngine::Instance().camera.getZoom() ) ;
    dstrect.h = ROUND_2_INT( (float) rect.height * (float)propiedades.scaleY / (float)renderEngine::Instance().camera.getZoom());
    


    SDL_Rect srcrect;
    srcrect.x = rect.left;
    srcrect.y = rect.top ;
    srcrect.w = (float) rect.widht;
    srcrect.h = (float) rect.height;


    if(texture != nullptr){
        SDL_RenderCopy( renderEngine::Instance().renderer, texture->getTexture(), &srcrect, &dstrect );
    }else{
        SDL_RenderFillRect(renderEngine::Instance().renderer,&dstrect )   ;
    }

}

void renderEngine::setDrawColor(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderEngine::Instance().renderer, r, g, b, a);
}


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

void renderEngine::setView(rView v){
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

void renderEngine::rTexture::loadFromImage(renderEngine::rImage im, rIntRect ir) {
    printf("loadFromImage(renderEngine::rImage im, rIntRect ir)");
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









//============================= EVENTOS =============================//
renderEngine::rEvent::rEvent() {}

int renderEngine::rEvent::getKeyCode()              {return event.key.keysym.sym;}
int renderEngine::rEvent::getJoystickButton()       {return 0;}
float renderEngine::rEvent::getJoystickMoveAxis()     {return 0;}
float renderEngine::rEvent::getJoystickMovePosition() {return 0;}
int renderEngine::rEvent::getJoystickId()           {return 0;}


unsigned int   renderEngine::rEvent::sfType    () {    return event.type;}













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
    font.loadFromFile("assets/fonts/8-bit_pusab.ttf");
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

    SDL_RenderCopy(renderEngine::Instance().renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

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

     Message = SDL_CreateTextureFromSurface(renderEngine::Instance().renderer, surfaceMessage); //now you can convert it into a texture
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
    font = TTF_OpenFont(str.c_str(), 80); //this opens a font style and sets a size
 }















