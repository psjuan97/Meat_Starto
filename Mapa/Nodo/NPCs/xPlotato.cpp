/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   xPlotato.cpp
 * Author: dan
 * 
 * Created on 9 de abril de 2018, 8:27
 */

#include <complex>
#include "../../../Juego.h"
#include "xPlotato.h"
#include "math.h"

#define velocity 2.f

xPlotato::xPlotato(int x_, int y_, int x_b, int x_e) {
    //std::cout << "Creando xPlotato" << std::endl;

    std::string sprite_name = "assets/kawaii_potato.png";
    
    int width = AssetManager::GetTexture(sprite_name).getXSize();
    int height = AssetManager::GetTexture(sprite_name).getYSize();

    sprite.setTexture(AssetManager::GetTexture(sprite_name));
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(x_, y_);
    
    physicsEngine* world;
    //body = world->Instance().createBody(width, height, x_, y_, 'K');
    body = world->Instance().createBody(width, height, x_, y_, 'd');
    t = new physicsEngine::type;
    t->id = 3;
    t->data = this;
    body.setUserData(t);
    

    //Zona en la que se puede mover teniendo en cuenta el ancho del sprite
    x_begin = x_b + width/2;
    x_end = x_e - width/2;
    
    target = x_begin;
    
    hp = 1;
    
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
    
    xplotar = false;
    alive = true;
    
    xplosion = NULL;
}

xPlotato::xPlotato(const xPlotato& orig) {
    t = orig.t;
    x_begin = orig.x_begin;
    x_end = orig.x_end;
    target = orig.target;
    
    hp = orig.hp;
    sprite = orig.sprite;
    body = orig.body;
    previous = orig.previous;
    actual = orig.actual;
}

xPlotato::~xPlotato() {
    //std::cout << "Destruyendo xPlotato..." << std::endl;
    delete t;
    t = nullptr;
}

void xPlotato::update(){
    
    if(xplotar){
        direccion();
        //std::cout << xclock.getElapsedTime().asSeconds() << std::endl;
        if(xclock.getElapsedTime().asSeconds() > 2.8){
            if(!xplosion){
                xplosion = new renderEngine::rCircleShape(140,30);
                xplosion->setPosition(sprite.getPosition()[0],sprite.getPosition()[1]);
                xplosion->setFillColor('r');
                xplosion->setOrigin(140,140);
            }
        }
        if(xclock.getElapsedTime().asSeconds() > 3){
            alive = false;
        }
    }
    
    if(!xplotar){
        persigue();
        
        if(abs(body.getLinearXVelocity()) < 1){
            body.setLinealVelocicity(-velocity, body.getLinearYVelocity());
            sprite.setScale(-1, 1);
        }

        if(target == x_begin && body.getXPosition() <= target ){
            target = x_end;
            body.setLinealVelocicity(velocity, body.getLinearYVelocity());
            sprite.setScale(1, 1);

        }
        else if(target == x_end && body.getXPosition() >= target){
            target = x_begin;
            body.setLinealVelocicity(-velocity, body.getLinearYVelocity());
            sprite.setScale(-1, 1);
        }
    }
    
    if(xplosion){
        xplosion->setPosition(sprite.getPosition()[0],sprite.getPosition()[1]);
    }
    
}

void xPlotato::persigue() {
    int np = Juego::Instance().getPlayers()->size();
    int r = physicsEngine::Instance().genIntRandom(0,np-1);

    float x_ = (Juego::Instance().getPlayers()[0][r]->getXPosition()-sprite.getPosition()[0]);
    float y_ = (Juego::Instance().getPlayers()[0][r]->getYPosition()-sprite.getPosition()[1]);

    if(sqrt((x_*x_)+(y_*y_)) < 70*5){
        std::cout << "LA PATATA TE OBSERVA: " << Juego::Instance().getPlayers()[0][r]->getName() << std::endl;
        xplotar = true;
        pj = r;
        direccion();
        xclock.restart();
    }
}

void xPlotato::direccion() {
    if(sprite.getPosition()[0] > Juego::Instance().getPlayers()[0][pj]->getXPosition()){
        body.setLinealVelocicity(-4.f,body.getLinearYVelocity());
        sprite.setScale(-1, 1);
    }
    else{
        body.setLinealVelocicity(4.f,body.getLinearYVelocity());
        sprite.setScale(1, 1);
    }
}

void xPlotato::salta(int s) {
    float imp = -15;
    if(s==1){
        //std::cout << "Salto hacia la derecha" << std::endl; 
        body.applyLinearImpulse(0,imp);
    }
    else if(s==0){
        //std::cout << "Salto hacia la izquierda" << std::endl;
        body.applyLinearImpulse(0,imp);
    }
    else if(s==-1){
        body.applyLinearImpulse(0,0);
    }
}