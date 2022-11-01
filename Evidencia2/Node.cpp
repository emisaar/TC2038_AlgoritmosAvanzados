//  Actividad 3.2
//  Implementación de "Dijkstra y Floyd"
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 06/10/2022
//
//  Referencias:

#include "Node.hpp"

//CONSTRUCTOR: Recibimos el id del nodo como entero
//el nodo previo lo inicializamos como nullptr y la
//distancia será igual a 1000 (número muy grande)
Node::Node(int _number){
    number = _number;
    prev = nullptr;
    distance = 1000;
    visited = false;
}
