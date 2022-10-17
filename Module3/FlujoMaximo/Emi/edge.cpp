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

#include "Edge.h"

/*
Constructor de Edge (Arista)
    Recibe como parámetros:
    - Dos nodos:
        > nodo de salida (first)
        > nodo de llegada (second)
    - Ponderación o peso de la arista (weight)
*/
Edge::Edge(Node *_first, Node *_second, int _weight){
    first = _first;
    second = _second;
    weight = _weight;
}