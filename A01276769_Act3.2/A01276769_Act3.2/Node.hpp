//  Actividad 3.3
//  Flujo Máximo
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 17/10/2022
//
//  Referencias:
//  https://favtutor.com/blogs/ford-fulkerson-algorithm
//  https://github.com/fit-coder/fitcoderyoutube/blob/master/graph/ford_fulkerson.cpp
//  https://www.programiz.com/dsa/ford-fulkerson-algorithm
//  https://github.com/BedirT/Algorithms_and_DS/blob/master/Algorithms/Graph/Ford%20Fulkerson.cpp
//  https://www.youtube.com/watch?v=_UcOALraATY

#ifndef Node_hpp
#define Node_hpp

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
    
    //Constructor del nodo
    Node(int _number);
};

#endif /* Node_hpp */
