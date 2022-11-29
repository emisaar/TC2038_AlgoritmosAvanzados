//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  node.cpp

#include "Node.hpp"
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
    x = 0;
    y = 0;
    parent = nullptr;
    f = 0;
    g = 0;
    h = 0;
}
