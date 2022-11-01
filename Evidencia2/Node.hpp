//  Actividad 3.2
//  Implementación de "Dijkstra y Floyd"
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 06/10/2022

#ifndef Node_hpp
#define Node_hpp

#pragma once
#include <stdio.h>

class Node{
public:
    //Variable que sirve como identificador
    int number;
    
    //Puntero para poder recorrer en Dijkstra
    //Nos ubica en el nodo anterior
    Node* prev;
    
    //Variable que se utilizará en el recorrido de Dijkstra
    //Representa la distancia
    int distance;
    
    //Valor necesario para hacer el recorrido BFS
    bool visited;
    
    //Constructor del nodo
    Node(int _number);
};

#endif /* Node_hpp */
