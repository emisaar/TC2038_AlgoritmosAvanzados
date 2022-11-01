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

#include "Node.hpp"

//CONSTRUCTOR: Recibimos el id del nodo como entero
//el nodo previo lo inicializamos como nullptr y la
//distancia será igual a 1000 (número muy grande)
Node::Node(int _number){
    number = _number;
    prev = nullptr;
    distance = 1000;
}
