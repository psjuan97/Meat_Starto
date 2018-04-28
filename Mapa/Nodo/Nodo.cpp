/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.cpp
 * Author: dan
 * 
 * Created on 11 de abril de 2018, 3:33
 */

#include <complex>

#include "Nodo.h"
#include "NPCs/xPlotato.h"
#include "NPCs/Skull.h"
#include "Juego.h"


Nodo::Nodo() {
    
    array_funciones[0] = &Player::powerUpInmortalidad;
    array_funciones[1] = &Player::powerUpSpeed;
    array_funciones[2] = &Player::powerUpExperience;
    array_funciones[3] = &Player::powerDownJump;
    array_funciones[4] = &Player::powerDownFreeze;
    array_funciones[5] = &Player::powerDownLevelOne;
    array_funciones[6] = &Player::powerDownFish;
    
    checkPoint checkpoint;
    checkpoint.active = false;
    checkpoint.shape.setSize(70, 280);
    checkpoint.shape.setPosition(1260, 1500);
    checkpoint.shape.setOutlineThickness(2);
    checkpoint.shape.setOutlineColor('r');
    checkpoint.shape.setFillColor('t');
    maxXCheckPoint = 0;
    
    minijuego = nullptr;
}

Nodo::Nodo(const Nodo& orig) {

    for(int i = 0; i < orig.v_esprait.size(); i++)
        v_esprait.push_back(orig.v_esprait[i]);
    
    for(int i= 0; i < orig.tileRect.size(); i++)
        tileRect.push_back(orig.tileRect[i]);
    
    for(int i=0; i< orig.ground.size(); i++)
        ground.push_back(orig.ground[i]);
    
    for(int i = 0; i < orig.npcs.size(); i++)
        npcs.push_back(orig.npcs[i]);
    
    for(int i = 0; i < orig.pinchos.size(); i++)
        pinchos.push_back(orig.pinchos[i]);
    
    for(std::list<checkPoint>::const_iterator it = orig.checkpoints.begin(); it != orig.checkpoints.end(); ++it)
        checkpoints.push_back(*it);
    
    aux_pop = orig.aux_pop;
    
    maxXCheckPoint = orig.maxXCheckPoint;
}

Nodo::~Nodo() {
    std::cout << "Borrando nodo..." << std::endl;
    for(int i = 0; i <npcs.size(); i++){
        delete npcs[i];
        npcs[i] = nullptr;
    }
    delete minijuego;
}


void Nodo::setPop(int i){
    aux_pop = i;
}

int Nodo::getPop(){
    return aux_pop;
}

void Nodo::setRectVector(std::vector<renderEngine::rIntRect> rect_){
    tileRect = rect_;
}


void Nodo::addTile(int id, int x, int y){
    std::string path;
    if(Mapa::Instance().getTotalIterations()/2 > Mapa::Instance().getIterations()){
        path = "tiles_definitivo/tilesheet.png";
    }
    else{
        path = "tiles_definitivo/tilesheet2.png";
    }
    
    renderEngine::rSprite sprite;
    sprite.setTexture(AssetManager::GetTexture(path));
    sprite.setTextureRect(tileRect[id]);
    sprite.setPosition(x,y);
    
    v_esprait.push_back(sprite);
    int size = 65;
    int error = (70-size)/2;
    if(id == 36 || id == 35 || id == 34 || id == 33){
        pinchos.emplace_back();
        if(id == 33){
            pinchos.back().setFillColor('r');
            pinchos.back().setSize(size, size/2);
            pinchos.back().setPosition(x+error,y+size/2);
            
        }
        else if(id==34){
            pinchos.back().setFillColor('g');
            pinchos.back().setSize(size/2, size);
            pinchos.back().setPosition(x,y+error);
            
        }
        else if(id==35){
            pinchos.back().setFillColor('b');
            pinchos.back().setSize(size, size/2);
            pinchos.back().setPosition(x+error,y);
            
        }
        else if(id==36){
            pinchos.back().setFillColor('y');
            pinchos.back().setSize(size/2, size);
            pinchos.back().setPosition(x+size/2,y+error);
        }
    }
}

void Nodo::addGround(std::vector<std::array<int,2> > coords){
    physicsEngine* world;
    
    t = new physicsEngine::type;
    t->id = 1;
    t->data = this;
    
    ground.push_back(world->Instance().createGround(coords, t));
}

void Nodo::addxPlotato(int x_, int y_, int x_min, int x_max) {
    npcs.push_back(new xPlotato(x_, y_, x_min, x_max));
}

void Nodo::addSkull(int x_, int y_, int x_min, int x_max, int y_min, int y_max){
    npcs.push_back(new Skull(x_, y_, x_min, x_max, y_min, y_max));
}

void Nodo::addCheckPoint(int x, int y, int width, int height) {
    
    checkPoint checkpoint;
    checkpoint.active = false;
    checkpoint.shape.setSize(width, height);
    checkpoint.shape.setPosition(x, y);
    checkpoint.shape.setOutlineThickness(2);
    checkpoint.shape.setOutlineColor('r');
    checkpoint.shape.setFillColor('t');
    
    checkpoints.push_back(checkpoint);   
}

Minijuego* Nodo::addMinigame(int type, int x, int y, int width, int height, std::vector<int> IDs_mininodo) {
    if(type == 1)
        minijuego = new goingUp(x, y, width, height, IDs_mininodo);
    
    return minijuego;
}


void Nodo::addPower(int id, int xMin, int xMax, int y_) {
    power p;
    p.id = id;
    
    std::string sprite[7];
    sprite[0] = "assets/powerUp.png";       // Estrella
    sprite[1] = "assets/powerUp.png";       // Café
    sprite[2] = "assets/powerUp.png";       // Carne
    sprite[3] = "assets/powerDown.png";     // Flan
    sprite[4] = "assets/powerDown.png";     // Helado
    sprite[5] = "assets/powerDown.png";     // Biberón
    sprite[6] = "assets/powerDown.png";     // Pescado
    
    std::string target = sprite[id];
    
    int sizeY = AssetManager::GetTexture(target).getYSize();
    int sizeX = AssetManager::GetTexture(target).getXSize();
    int newX = physicsEngine::Instance().genIntRandom(xMin+sizeX+10, xMax-sizeX-10);
    
    p.sprite.setTexture(AssetManager::GetTexture(target));
    p.sprite.setOrigin(sizeY, sizeX);
    p.sprite.setPosition(newX, y_);
    powers.push_back(p);
}

void Nodo::draw(float tick_, renderEngine::rIntRect limit, int min, int max){

    for(int i = 0; i < v_esprait.size(); i++){
        if(limit.contains(v_esprait[i].getPosition()[0],v_esprait[i].getPosition()[1])){
            v_esprait[i].draw();
        }
    }   
    
    //------------|  ENEMIGOS  |------------//
    for(int j = 0; j < npcs.size(); j++)
        if(npcs[j]->getXPosition() > min-250 && npcs[j]->getXPosition() < max+250){
            npcs[j]->interpola(tick_);
            npcs[j]->draw();
        }

    
    for(std::list<checkPoint>::iterator it = checkpoints.begin(); it != checkpoints.end(); ++it)
        (*it).shape.draw();
    
    for(int i = 0; i < powers.size(); i++)
        powers[i].sprite.draw();
    
    if(minijuego != nullptr)
        minijuego->draw(tick_);
    
}

void Nodo::miniDraw(float tick_) {
    for(int i = 0; i < v_esprait.size(); i++)
            v_esprait[i].draw();
    
    //------------|  ENEMIGOS  |------------//
    for(int j = 0; j < npcs.size(); j++){
            npcs[j]->interpola(tick_);
            npcs[j]->draw();
        }
    for(std::list<checkPoint>::iterator it = checkpoints.begin(); it != checkpoints.end(); ++it)
        (*it).shape.draw();
    
    for(int i = 0; i < powers.size(); i++)
        powers[i].sprite.draw();
}


void Nodo::update(){

    bool flag = false;
    for(int i = 0; i < npcs.size(); i++){
        npcs[i]->update();
        
        if(!npcs[i]->isAlive()){
            delete npcs[i];
            npcs[i] = NULL;
            npcs.erase(npcs.begin()+i);
        }
    }
    
    std::vector<Player*>* players = Juego::Instance().getPlayers();
    
    for(int i = 0; i < players->size(); i++){
        
        Player* ready = (*players)[i];
        
        std::list<checkPoint>::iterator it = checkpoints.begin();
        while(it != checkpoints.end()){
            if(ready->getXPosition() > (*it).shape.getPosition()[0]){
                (*it).active = true;
                (*it).shape.setOutlineColor('g');
                maxXCheckPoint = (*it).shape.getPosition()[0];
            }

            ++it;
        }
        
        it = checkpoints.begin();
        while(it != checkpoints.end()){
            if((*it).shape.getPosition()[0] < maxXCheckPoint)
                checkpoints.erase(it++);
            else
                ++it;
        }

        // EVENTOS
        if(!ready->isInmortal())
            checkColisionsPinchos(ready);
        
        
        //Colision con powerups
        for(int j = 0; j < powers.size(); j++){
            if(ready->getSprite().intersects(powers[j].sprite)){
                //Puntero a funcion
                pFunc funcion = array_funciones[powers[j].id];   
                if(funcion != nullptr) (ready->*funcion)();
                powers.erase(powers.begin()+j);
                flag = true;
            }
        }  
    }
    
    if(minijuego != nullptr){
        minijuego->update();
    }
    
}

void Nodo::checkColisionsPinchos(Player* ready) {
    bool flag = false;
    //Colision con pinchos
    for(int j = 0; j < pinchos.size() && !flag; j++){
        if(ready->getSprite().intersects(pinchos[j])){
            Mapa::Instance().movePlayerToClosestCheckPoint(ready);
            //ready->lvlDown();
            flag = true;
        }
    }
}

void Nodo::preState(){
    for(int i = 0; i < npcs.size(); i++){
        npcs[i]->preState();
    }
}

void Nodo::newState(){
    for(int i = 0; i < npcs.size(); i++){
        npcs[i]->newState();
    }
}