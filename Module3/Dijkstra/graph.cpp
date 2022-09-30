//  Actividad 3.2 - Implementación de "Dijkstra" y Floyd
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  graph.cpp

#include "Graph.h"

Graph::Graph(vector<Node*> _nodes, vector<Edge*> _edges){
    nodes = _nodes;
    edges = _edges;
}

/*
getNeighbors(Node *n) -> Complejidad: O(n)
Recibe:
    - Un nodo (n) que es al que se desea encontrar sus vecinos.
Regresa un vector (neighbors) con los nodos vecinos al nodo 
que recibe como parámetro.
Itera sobre el vector edges para conocer los vecinos.
*/
vector<Node*> Graph::getNeighbors(Node *n){
    vector<Node*> neighbors;
    for (int i = 0; i < edges.size(); i++){
        if (edges[i]->first == n){
            neighbors.push_back(edges[i]->second);
        }
        else if (edges[i]->second == n){
            neighbors.push_back(edges[i]->first);
        }
    }
    return neighbors;
}

/*
print() -> Complejidad: O(n+n) ?
Itera sobre los vectores nodes y edges para acceder e 
imprimir los atributos de los nodos y aristas.
*/
void Graph::print(){
    cout << "Nodes:" << endl;
    for (int i = 0; i < nodes.size(); i++){
        if(nodes[i]->prev != nullptr) {
            cout << "N: " << nodes[i]->number << " P: " << nodes[i]->prev->number << " D: " << nodes[i]->distance << endl;
        } else {
            cout << "N: " << nodes[i]->number << " P: nullptr" << " D: " << nodes[i]->distance << endl;
        }
    }

    cout << "\nEdges:" << endl;
    for (int i = 0; i < edges.size(); i++){
        cout << "N1: " << edges[i]->first->number << " N2: " << edges[i]->second->number << " D: " << edges[i]->weight << endl;
    }
}

/*
runDijkstra(Node *source) -> Complejidad:
Recibe:
    - Nodo de origen o inicio.
Lleva a cabo lógica del algoritmo.
*/
void Graph::runDijkstra(Node *source) {
    // Crear vector de nodos Q
    vector<Node*> Q;
    // Inicializar valores de los nodos dist = INF y prev = UNDF
    for (int v = 0; v < nodes.size(); v++){
        nodes[v]->distance = 1000;
        nodes[v]->prev = nullptr;
        Q.push_back(nodes[v]);
    }

    // Actualizar distancia a 0 para nodo inicial 
    source->distance = 0;

    // Ejecutar mientras Q no esté vacía
    while (!Q.empty()) {
        // Buscar nodo con la distancia más corta
        Node *u = getMinDist(Q);
        // Eliminar nodo con menor distancia del vector Q de nodos
        remove(Q, u);
        // Crear vector con los nodos vecinos a u (nodo actual) 
        vector<Node*> neighbors = getNeighbors(u);
        // Actualizar distancias
        for(int n = 0; n < neighbors.size(); n++) {
            Node *v = neighbors[n];
            int alt = u->distance + getLength(u, v);
            if (alt < v->distance) {
                v->distance = alt;
                v->prev = u;
            }
        }
    }
}

/*
getMinDist(vector<Node*> qs) -> Complejidad: O(n)
Recibe:
    - Un vector de nodos (qs)
Regresa el nodo con la menor distancia.
Compara las distancias de los nodos del vector, guardando 
el nodo con la distancia más corta.
*/
Node * Graph::getMinDist(vector<Node*> qs) {
    Node *min = qs[0];
    for (int i = 0; i < qs.size(); i++){
        if (qs[i]->distance < min->distance){
            min = qs[i];
        }
    }
    return min;
}


/*
remove(vector<Node*> &qs, Node *q) -> Complejidad: O(n)
Recibe:
    - Un vector de nodos (qs)
    - Un nodo (q) que es el que se desea eliminar.
El método itera el vector de nodos para buscar el nodo a
eliminar. En caso de encontrarlo, se realiza un erase en la
posición que se encuentra.
*/
void Graph::remove(vector<Node*> &qs, Node *q) {
    for(int i = 0; i < qs.size(); i++) {
        if(q == qs[i]){
            qs.erase(qs.begin() + i);
        }
    }
}

/* 
getLenth(Node *u, Node *v) -> Complejidad: O(n)
Recibe dos nodos:
    - Nodo u: Nodo de origen
    - Node v; Node de destino
Regresa un int que corresponde al peso (weight) de la arista.
Se itera el vector de aristas (edges) para encontrar su
respectivo peso (weight).
*/
int Graph::getLength(Node *u, Node *v) {
    for(int i = 0; i < edges.size(); i++) {
        if (edges[i]->first == u && edges[i]->second == v) {
            return edges[i]->weight;
        } else if (edges[i]->first == v && edges[i]->second == u) {
            return edges[i]->weight;
        }
    }
    return 0;
}