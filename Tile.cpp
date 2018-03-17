/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.cpp
 * Author: pablomanez
 * 
 * Created on 23 de febrero de 2018, 15:42
 */

#include <random>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <math.h>
#include <complex>
#include "Tile.h"

#define SCALE 65.f

Tile::Tile() {

    //CARGA DEL DOCUMENTO
    doc.LoadFile("tiles_definitivo/tiles_fv.tsx");
    
    //GUARDO ANCHO Y ALTO
    tinyxml2::XMLDocument *d_aux = doc.GetDocument();
    
    ancho = atoi(d_aux->FirstChildElement("tileset")->Attribute("tilewidth"));
    alto = atoi(d_aux->FirstChildElement("tileset")->Attribute("tileheight"));
    
    //ALMACENO LA INFORMACION DE LAS TILES
    tinyxml2::XMLElement *map;
    map = doc.FirstChildElement("tileset")->FirstChildElement("tile");
    
    //WHILE
    tinyxml2::XMLElement *m_aux;
    int k = 0;
    while(map){
        tiles[k] = new _tile;
        tiles[k]->id = atoi(map->Attribute("id"))+1;
        
            //std::cout << map->Attribute("id") << " -> ";
        
        m_aux = map->FirstChildElement("image");
        
        tiles[k]->path = m_aux->Attribute("source");
            //std::cout << m_aux->Attribute("source") << std::endl;
        
        map = map->NextSiblingElement("tile");
        k++;
    }
    
    //ANYADO EL PATH DE LA CARPETA
    
    int n = 37; //NUMERO TOTAL DE TILES
                //SI SE CAMBIA, CAMBIAR TAMBIEN _tile *tiles[37] EN EL .h;
    
    for(int i=0 ; i<n ; i++){
        std::string path2 = "tiles_definitivo/";
        std::string path3 = tiles[i]->path;
        
        tiles[i]->path = path2.operator +=(path3);
        
            //std::cout << tiles[i]->id << " -> " << tiles[i]->path << std::endl;
    }
    
    //INICIALIZO LA MATRIZ DE ADYACENCIA
    InitMatrix();

    //-----------VARIABLES DE CLASE-----------//
    
    //LO UTILIZO AL LEER TODOS LOS NODOS DE LA MATRIZ
    x_max = 0;
    //TETRIS
    m_tetris = false;
    
}

//INICIALIZAR LA MATRIZ DE ADYACENCIA
void Tile::InitMatrix() {
    //////////////////////////////
    // SI SE MODIFICA, ENTONCES //
    // CAMBIAR TAMBIEN EL .h !! //
    //////////////////////////////
    
    //  v es n x n
    //  n = 3
    int x;
    
    //NODO 0
    x = 0;
    // <editor-fold defaultstate="collapsed" desc="NODO 0">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 0;
    v[x][5] = 0;
    v[x][6] = 0;
    v[x][7] = 1;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 0;
    v[x][12] = 0;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 1
    x = 1;
    // <editor-fold defaultstate="collapsed" desc="NODO 1">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 1;
    v[x][6] = 1;
    v[x][7] = 1;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 0;
    v[x][13] = 0;
    v[x][14] = 1; 
    // </editor-fold>
    
    //NODO 2
    x = 2;
    // <editor-fold defaultstate="collapsed" desc="NODO 2">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 0;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 1;
    v[x][6] = 1;
    v[x][7] = 1;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 0;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>
    
    //NODO 3
    x = 3;
    // <editor-fold defaultstate="collapsed" desc="NODO 3">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 1;
    v[x][3] = 0;
    v[x][4] = 1;
    v[x][5] = 1;
    v[x][6] = 1;
    v[x][7] = 0;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 0;
    v[x][12] = 0;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 4
    x = 4;
    // <editor-fold defaultstate="collapsed" desc="NODO 4">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 0;
    v[x][6] = 1;
    v[x][7] = 1;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 1;
    v[x][12] = 0;
    v[x][13] = 1;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 5
    x = 5;
    // <editor-fold defaultstate="collapsed" desc="NODO 5">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 1;
    v[x][4] = 0;
    v[x][5] = 0;
    v[x][6] = 1;
    v[x][7] = 1;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 0;
    v[x][13] = 1;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 6 (MINIJUEGO TETRIS)
    x = 6;
    // <editor-fold defaultstate="collapsed" desc="NODO 6">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 1;
    v[x][6] = 0;
    v[x][7] = 1;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 0;
    v[x][13] = 1;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 7
    x = 7;
    // <editor-fold defaultstate="collapsed" desc="NODO 7">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 1;
    v[x][5] = 0;
    v[x][6] = 1;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 1;
    v[x][10] = 0;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 8
    x = 8;
    // <editor-fold defaultstate="collapsed" desc="NODO 8">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 1;
    v[x][5] = 0;
    v[x][6] = 0;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 1;
    v[x][10] = 0;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 9
    x = 9;
    // <editor-fold defaultstate="collapsed" desc="NODO 9">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 0;
    v[x][3] = 1;
    v[x][4] = 0;
    v[x][5] = 1;
    v[x][6] = 0;

    v[x][7] = 1;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 1;
    v[x][14] = 1; 
    // </editor-fold>

    //NODO 10
    x = 10;
    // <editor-fold defaultstate="collapsed" desc="NODO 10">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 0;
    v[x][5] = 0;
    v[x][6] = 0;

    v[x][7] = 0;
    v[x][8] = 0;
    v[x][9] = 1;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 1;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 11
    x = 11;
    // <editor-fold defaultstate="collapsed" desc="NODO 11">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 0;
    v[x][5] = 1;
    v[x][6] = 0;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 1;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 1;
    v[x][14] = 1; 
    // </editor-fold>
        
    //NODO 12
    x = 12;
    // <editor-fold defaultstate="collapsed" desc="NODO 12">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 0;
    v[x][5] = 0;
    v[x][6] = 0;

    v[x][7] = 1;
    v[x][8] = 1;
    v[x][9] = 1;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 0;
    v[x][13] = 1;
    v[x][14] = 0; 
    // </editor-fold>
        
    //NODO 13
    x = 13;
    // <editor-fold defaultstate="collapsed" desc="NODO 13">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 0;
    v[x][6] = 0;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 1;
    v[x][13] = 0;
    v[x][14] = 1; 
    // </editor-fold>
        
    //NODO 14
    x = 14;
    // <editor-fold defaultstate="collapsed" desc="NODO 14">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 0;
    v[x][5] = 1;
    v[x][6] = 1;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 1;
    v[x][14] = 1; 
    // </editor-fold>

    
    
}

//LEE Y CONSTRUYE EL NODO QUE LE PASES POR PARAMETRO
void Tile::LeeNodo(std::string node_path) {
    // <editor-fold defaultstate="collapsed" desc="LEO EL MAPA">
    
    //std::cout << "Leo el nodo: " << node_path << std::endl;

    int map_width;
    int map_height;

    //ABRO EL ARCHIVO
    //char const* node = node_path.c_str();
    tinyxml2::XMLDocument map_doc;
    map_doc.LoadFile(node_path.c_str());

    //CONSIGO EL ANCHO Y EL ALTO DEL NODO (MAPA)
    tinyxml2::XMLElement *map;
    map = map_doc.FirstChildElement("map");
    map_width = atoi(map->Attribute("width"));
    map_height = atoi(map->Attribute("height"));
    //std::cout << map_width << std::endl;

    //CONSIGO EL TEXTO
    std::string v_mapa = map->FirstChildElement("layer")->FirstChildElement("data")->GetText();
    //std::cout << v_mapa << std::endl;

    std::string partes;
    std::string p_aux;
    int x_max_aux = x_max;

    for (int i = 0; i < map_height; i++) {
        //std::cout << "_____|" << "i: " << i << "|_____" << std::endl;

        for (int j = 0; j < map_width; j++) {

            //ELIMINO EL SALTO DE LINEA DE CADA FILA
            v_mapa.erase(0, 1);

            //CONSIGO EL NUMERO
            partes = v_mapa.substr(0, 1);
            v_mapa.erase(0, 1);
            //std::cout << "partes:   " << partes << std::endl;

            p_aux = v_mapa.substr(0, 1);
            //std::cout << "p_aux:    " << p_aux << std::endl;

            while (p_aux != "," && p_aux != "") {
                partes = partes.operator+=(v_mapa.substr(0, 1));
                v_mapa.erase(0, 1);
                p_aux = v_mapa.substr(0, 1);
            }

            //std::cout << "j: " << j << " ->     " << partes << std::endl;

            if (stoi(partes) != 0) {
                CreaCasilla(stoi(partes), x_max + (ancho * j), alto * i);
            }

            if (x_max_aux < x_max + (ancho * j)) {
                x_max_aux = x_max + (ancho * j);
            }

        }

        partes = v_mapa.erase(0, 1);
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="LEO LOS OBJETOS(colisiones)">

    //CONSIGO LOS OBJETOS (COLISIONES)
    //NO COMPRUEBO SI NO TIENE COLISION, YA QUE SE SUPONE QUE TODOS LOS NODOS VAN A TENER COLISION, SI O SI
    tinyxml2::XMLElement *obj, *poly;
    int x, x2;
    int y, y2;
    std::string vertex, v_aux, v_aux2;

    std::vector<std::array<float, 2>> vec;
    sf::ConvexShape *cs;

    obj = map->FirstChildElement("objectgroup")->FirstChildElement("object");
        //std::cout << obj->Attribute("x") << std::endl;

    while (obj) {
        x = atoi(obj->Attribute("x")); //COORDENADA X ABSOLUTA
        y = atoi(obj->Attribute("y")); //COORDENADA Y ABSOLUTA

        //============================================//
        //PARA CREAR LOS VERTICES DEL ConvexShape
        cs = new sf::ConvexShape;

        //============================================//

        poly = obj->FirstChildElement("polyline"); //OBJETO POLYLINE
        //std::cout << poly->Attribute("points") << std::endl;

        vertex = poly->Attribute("points"); //STRING CON LAS COORDENADAS

        //CONSIGO EL NUMERO
        while (1) {
            for (int i = 0; i < 2; i++) {
                v_aux = vertex.substr(0, 1);
                vertex.erase(0, 1);
                //std::cout << "partes:   " << v_aux << std::endl;

                v_aux2 = vertex.substr(0, 1);
                //std::cout << "p_aux:    " << p_aux << std::endl;

                while (v_aux2 != "," && v_aux2 != " " && v_aux2 != "") {
                    v_aux = v_aux.operator+=(vertex.substr(0, 1));
                    vertex.erase(0, 1);
                    v_aux2 = vertex.substr(0, 1);
                }
                vertex.erase(0, 1);


                if (i == 0) {
                    x2 = x + x_max + stoi(v_aux);
                    //std::cout << "x2:" << x2 << std::endl;
                } else {
                    y2 = y + stoi(v_aux);
                    //std::cout << "y2:" << y2 << std::endl;
                    //std::cout << "vertices:" << vertex << std::endl;
                    //std::cout << "|=========================|" << std::endl;
                }
            }

            //ALMACENO EL VERTICE
            //cs->setPoint(n,sf::Vector2f(x2,y2));
            std::array<float, 2> coords = {(float)x2, (float)y2};
            vec.push_back(coords);

            
            if (vertex == "") {
                break;
            }
        }
        //std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;

        cs->setPointCount(vec.size());
        for (int i = 0; i < vec.size(); i++) {
            cs->setPoint(i, sf::Vector2f(vec[i][0], vec[i][1]));
        }
        
        //<DEBUG>
        cs->setFillColor(sf::Color::Transparent);
        cs->setOutlineColor(sf::Color::Red);
        cs->setOutlineThickness(5);
        //</DEBUG>
        
        colision.push_back(vec);    //GUARDO LOS PARES DE VERTICES
        
        /* SUPERCOMENTARIO++ */
        physicsEngine* world;
        
        world->Instance().createGround(vec, vec.size());
        
        
        
        objetos.push_back(*cs);     //GUARDO LOS ConvexShapes PARA DEBUG
        //BORRAR cs -> !IMPORTANTE
        delete cs;
        //VACIAR vec -> !IMPORTANTE
        vec.clear();

        obj = obj->NextSiblingElement("object");
        //std::cout << obj->Attribute("x") << std::endl;
    }
    // </editor-fold>

    x_max = x_max_aux+ancho;
        //std::cout << x_max << std::endl;
}

//CREA LA CASILLA
void Tile::CreaCasilla(int id, int x, int y) {
    
    sf::Texture text;
    text.loadFromFile(tiles[id-1]->path);
        //std::cout << tiles[id-1]->path << std::endl;
    
    sf::RectangleShape casilla(sf::Vector2f(ancho,alto));
    casilla.setTexture(&text);
    casilla.setPosition(x,y);
    
    _cas aux;
    aux.id = id;
    aux.text = text;
    aux.rect = casilla;
    
    vector_casillas.push_back(aux);

}

void Tile::DibujaCasillas(sf::RenderWindow &window, int x, int y) {
    //REDONDEO LA COORDENADA x
        //std::cout << x << std::endl;
    bool pos = false;
    int x_2;
    int i=0;
    int mult = ancho;
    while(!pos){
        if(mult*i>x){
            x_2 = mult*i;
            pos = true;
        }
        i++;
    }
    
    //REDONDEO LA COORDENADA y
    pos = false;
    int y_2;
    i=0;
    mult = alto;
    while(!pos){
        if(mult*i>y){
            y_2 = mult*i;
            pos = true;
        }
        i++;
    }
        //std::cout << y_2 << std::endl;

    
    int x_min = x_2 -(ancho*26);
    int x_max = x_2 +(ancho*24);
    
    int y_min = y_2 -(alto*15);
    int y_max = y_2 +(alto*12);
    
    
    sf::RectangleShape *r;
    sf::Texture *t;
        
    for(int i=0 ; i<vector_casillas.size() ; i++){
        if(     (int)vector_casillas[i].rect.getPosition().x >= x_min && (int)vector_casillas[i].rect.getPosition().x <= x_max &&
                (int)vector_casillas[i].rect.getPosition().y >= y_min && (int)vector_casillas[i].rect.getPosition().y <= y_max){
                //std::cout << i << std::endl;
            
            r = &(vector_casillas[i].rect);
            t = &(vector_casillas[i].text);

            r->setTexture(t);

            window.draw(*r);
        }
            
    }
    
    //PARA DEBUGGEAR
    /*
    for(int i=0 ; i<objetos.size() ; i++){
        window.draw(objetos[i]);
    }
    */
    
}

//LEE LA MATRIZ DE ADYACENCIA
void Tile::CreaMapa() {
    std::string path = "tiles_definitivo/nodos/";
    path = path.operator +=("0.tmx");
        std::cout << path << std::endl;
    
    LeeNodo(path);
    
    //EMPIEZA A LEER LA MATRIZ
    int n = 15;     //DIMENSION DE LA MATRIZ DE ADYACENCIA
    int nodo = 0;   //NODOS ADYACENTES A 0
    int iter = 0;   //CUENTA EL NUMERO DE ITERACIONES
    int r;          //EL NUMERO RANDOM
    while(iter != 10){
        
        bool num = false;
        while(!num){
            //GENERO EL NUMERO ALEATORIO
            std::random_device rd;
            std::default_random_engine gen(rd());
            std::uniform_int_distribution<int> distribution(0,n-1);

            r = distribution(gen);
            
            if(v[nodo][r]==1){
                num = true;
            }
        }
        if(r != 6 || (r == 6 && !m_tetris)){
            std::string path = "tiles_definitivo/nodos/";
            std::string rand = std::to_string(r);
            path = path.operator +=(rand);
            path = path.operator +=(".tmx");
                std::cout << path << std::endl;
            
            LeeNodo(path);

            nodo = r;
        }
        
        //DETECTA QUE YA SE HA DIBUJADO EL MINIJUEGO
        if(r == 6) m_tetris = true;
        
        iter++;
    }
    
    
    
}

Tile::Tile(const Tile& orig) {
}

Tile::~Tile() {
}

