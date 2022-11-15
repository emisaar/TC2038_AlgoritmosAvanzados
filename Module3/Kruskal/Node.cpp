//  Actividad 3.3
//  Implementación de "Knapsack problem"
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 03/11/2022

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
