//  Actividad 3.3
//  Flujo Máximo

//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258

//  Fecha: 17/10/2022

/* Referencias:
https://brilliant.org/wiki/ford-fulkerson-algorithm/
https://emory.gitbook.io/dsa-java/network-flow/ford-fulkerson-algorithm
https://favtutor.com/blogs/ford-fulkerson-algorithm
https://github.com/fit-coder/fitcoderyoutube/blob/master/graph/ford_fulkerson.cpp
https://www.programiz.com/dsa/ford-fulkerson-algorithm
https://github.com/BedirT/Algorithms_and_DS/blob/master/Algorithms/Graph/Ford%20Fulkerson.cpp
https://www.youtube.com/watch?v=_UcOALraATY
*/

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
    distance = 1000;
    prev = nullptr;
}