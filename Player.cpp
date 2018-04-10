/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: claudiac
 * 
 * Created on 21 de marzo de 2018, 0:47
 */

#include "Player.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Animator.h"
#include "AssetManager.h"
#include "physicsEngine/physicsEngine.h"
#include "Tile.h"

#define FRAMERATE 60.f
#define UPDATE_STEP 15.f
#define force 50.f*FRAMERATE/UPDATE_STEP
#define speed 12.f
#define jump 2500
#define stop_mult 1.2f

Player::Player(int id, std::string name, float width_, float height_, float x_, float y_, char type_, bool *keys_) : animator(sprite) {
    setId(id);
    setName(name);
    
    physicsEngine* world;
    
    keys = keys_;
    body = world->Instance().createBody(width_, height_, x_, y_, type_);
    body.setUserData(this);
    
    sprite.setScale(1.6f, 1.6f);
    sprite.setOrigin(30, 30);
    switch(id){
    //Asigna la textura con su color dependiendo del id del jugador
        case 0:
                texture="assets/player0.png";
        break;
        case 1:
                texture="assets/player1.png";
                sprite.setPosition(x_, y_);
        break;
        case 2:
                texture="assets/player2.png";    
        break;
        case 3:
                texture="assets/player3.png";                        
        break;                           
    }
   
    
    sf::Vector2i spriteSize(60,60);
    
    Animator::Animation* anim = &animator.CreateAnimation("a_bas",texture, renderEngine::rTime(3), false);
    anim->AddFrames(sf::Vector2i(0,0), sf::Vector2i(60,60), 1);
    animator.SwitchAnimation("a_bas");
    
    Animator::Animation* a_base = &animator.CreateAnimation("a_base",texture, renderEngine::rTime(3), false);
    a_base->AddFrames(sf::Vector2i(0,0), spriteSize ,1);
    
    //Giro Derecha
    Animator::Animation* a_rigth = &animator.CreateAnimation("a_rigth",texture, renderEngine::rTime(0.3), false);
    a_rigth->AddFrames(sf::Vector2i(300,0), spriteSize , 3);
    Animator::Animation* a_base_r = &animator.CreateAnimation("a_base_r",texture, renderEngine::rTime(0.2), false);
    a_base_r->AddFrames(sf::Vector2i(480,0), spriteSize , 2);
    
    //Giro Izquierda
    Animator::Animation* a_left = &animator.CreateAnimation("a_left",texture, renderEngine::rTime(0.3), false);
    a_left->AddFrames(sf::Vector2i(0,0), spriteSize , 3);
    Animator::Animation* a_base_l = &animator.CreateAnimation("a_base_l",texture, renderEngine::rTime(0.2), false);
    a_base_l->AddFrames(sf::Vector2i(180,0), spriteSize , 2);
    
    //Salto izquierda
    Animator::Animation* a_jump_l = &animator.CreateAnimation("a_jump_l",texture, renderEngine::rTime(2), false);
    a_jump_l->AddFrames(sf::Vector2i(0,60), spriteSize ,9);          
    
    //Salto derecha
    Animator::Animation*  a_jump_r = &animator.CreateAnimation("a_jump_r",texture, renderEngine::rTime(2), false);
    a_jump_r->AddFrames(sf::Vector2i(0,180), spriteSize ,9);   
    
    //Para colision
    Animator::Animation*  a_fall_l = &animator.CreateAnimation("a_fall_l",texture, renderEngine::rTime(0.5), false);
    a_fall_l->AddFrames(sf::Vector2i(0,120), spriteSize ,3);
    Animator::Animation*  a_fall_r = &animator.CreateAnimation("a_fall_r",texture, renderEngine::rTime(0.5), false);
    a_fall_r->AddFrames(sf::Vector2i(180,120), spriteSize ,3);
   
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
}

Player::~Player() {
}

void Player::setId(int i){
    id = i;
}
int Player::getId(){
    return id;
}
int Player::getLevel(){
    return level;
}
/*
void Player::setSpeed(float f){
    speed=f;
}
float Player::getSpeed(){
    return speed;
}
*/
void Player::setName(std::string n){
    name=n;
}
std::string Player::getName(){
    return name;
}

renderEngine::rSprite Player::getSprite(){
    return sprite;
}

void Player::update(renderEngine::rTime deltatime){
    animator.Update(deltatime);
}


void Player::moveRigth(){
    if(animator.GetCurrentAnimationName() != "a_rigth"){
        animator.SwitchAnimation("a_rigth");
    }
}

void Player::moveRigth_b(){
    if(animator.GetCurrentAnimationName() != "a_base_r"){
        animator.SwitchAnimation("a_base_r");
    }
}

void Player::moveLeft(){
    if(animator.GetCurrentAnimationName() != "a_left"){
        animator.SwitchAnimation("a_left");
    }
}

void Player::moveLeft_b(){
    if(animator.GetCurrentAnimationName() != "a_base_l"){
        animator.SwitchAnimation("a_base_l");
    }
}

void Player::moveUp(){
    if(animator.GetCurrentAnimationName() == "a_base_r"){
                                
    }                     
    if(animator.GetCurrentAnimationName() == "a_left"){
        animator.SwitchAnimation("a_jump_l");
    }
    if(animator.GetCurrentAnimationName() == "a_rigth"){
        animator.SwitchAnimation("a_jump_r");
    }
}

void Player::moveDown(){
    if(animator.GetCurrentAnimationName() == "a_jump_l" || animator.GetCurrentAnimationName() == "a_base_l" || animator.GetCurrentAnimationName() == "a_left" ){
        animator.SwitchAnimation("a_fall_l");
    }
    if(animator.GetCurrentAnimationName() == "a_jump_r" || animator.GetCurrentAnimationName() == "a_base_r" || animator.GetCurrentAnimationName() == "a_rigth"){
        animator.SwitchAnimation("a_fall_r");
    }                       
}


//MOVIMIENTO
void Player::movement(){
    // TECLA A  ==================================================================
    if( keys[0])  {                                                             //
        if(body.getLinearXVelocity() > -speed)                                  //
            body.applyForceToCenter(-force, 0);                                 //
        else                                                                    //  IZQUIERDA
            body.setLinealVelocicity(-speed, body.getLinearYVelocity());        //
        moveLeft();
    }                                                                           //
    // ===========================================================================

    // TECLA D  ==================================================================
    else if( keys[3]) {                                                         //
        if(body.getLinearXVelocity() < speed)                                   //
            body.applyForceToCenter(force, 0);                                  //
        else                                                                    //  DERECHA
            body.setLinealVelocicity(speed, body.getLinearYVelocity());         //
        moveRigth();
    }                                                                           //
    // ===========================================================================

    // TECLA W / ESPACIO  ========================================================
    if(keys[57] || keys[22]){                                                   //
        keys[57] = false;                                                       //
        keys[22] = false;                                                       //  SALTO
        body.applyForceToCenter(0, -jump);                                      //
        moveUp();
    }                                                                           //
    // ===========================================================================

    //STOP CON DESLIZAMIENTO  ================================================================================
    if(!keys[0] && body.getLinearXVelocity() < -2){                                                         //
        body.applyForceToCenter(force*stop_mult, 0);                                                        //
    }                                                                                                       //
    else if(!keys[3] && body.getLinearXVelocity() > 2)                                                      //
        body.applyForceToCenter(-force*stop_mult, 0);                                                       //
                                                                                                            // FRENADO
    if(!keys[0] && !keys[3] && body.getLinearXVelocity() >= -2 && body.getLinearXVelocity() <= 2){          //
        body.applyForceToCenter(0, 0);                                                                      //
        body.setLinealVelocicity(0, body.getLinearYVelocity());                                             //
    }                                                                                                       //
    //  ======================================================================================================
    
}

void Player::interpola(float tick_){
    // CALCULO LAS POSICIONES INTERPOLADAS DE ACUERDO AL TICK
    float x = previous.x *(1-tick_) + actual.x*tick_;
    float y = previous.y *(1-tick_) + actual.y*tick_;
        // Para las rotaciones es mejor interpolar los senos y cosenos, ya que si no, al calcular el ángulo entre 350 y 10, no nos devolvería 20, que sería lo correcto
    float s = sin(previous.r * M_PI/180) * (1-tick_) + sin(actual.r * M_PI/180)*tick_;
    float c = cos(previous.r * M_PI/180) * (1-tick_) + cos(actual.r * M_PI/180)*tick_;
    
    sprite.setPosition(x, y);
    sprite.setRotation(atan2(s,c)*180/M_PI);
}

void Player::draw(){
    sprite.draw();
}

void Player::preState(){
    previous = actual;      // GUARDO EL ESTADO ANTERIOR
}

void Player::newState(){
    actual.x = body.getXPosition();
    actual.y = body.getYPosition();
    actual.r = body.getRotation();
}

float Player::getXPosition(){
    return  sprite.getPosition()[0];
}

float Player::getYPosition() {
    return  sprite.getPosition()[1];
}

void Player::intersectsPinchos() {
    Tile *tile;
    
    for(std::list<std::vector<renderEngine::rRectangleShape>>::iterator it=(*tile->Instance().getPinchos()).begin(); it!=(*tile->Instance().getPinchos()).end(); ++it){
        for(int i=0 ; i<(*it).size() ; i++){
            if(sprite.intersects( (*it)[i] )){
                //std::cout << "ZASCA" << std::endl;
            }
        }
    }
    
    
}
