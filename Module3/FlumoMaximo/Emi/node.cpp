//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  node.cpp

#include "Node.h"
#include <iostream>

using namespace std;

/*
Constructor de Node (Nodo || Vértice)
    - Recibe un valor de tipo int (_number) que corresponde 
    al número de nodo.
Se inicializa la distance (distancia) en 10000 para 
    representar una distancia grande.
Se inicializa el prev (Nodo previo) como nullptr ya 
    que inicialmente no apunta a otro nodo.
*/
Node::Node(int _number){
    number = _number;
    distance = 10000;
    prev = nullptr;
}