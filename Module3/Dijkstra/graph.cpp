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
    vector<Edge*>::iterator ei;
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        if((*ei)->first == n) {
            neighbors.push_back((*ei)->second);
        }

        if((*ei)->second == n) {
            neighbors.push_back((*ei)->first);
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
    vector<Node*>::iterator ni;
    for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
        if((*ni)->prev != nullptr) {
            cout << "Node: " << (*ni)->number << " Prev: " << (*ni)->prev->number << " Dist: " << (*ni)->distance << endl;
        } else {
            cout << "Node: " << (*ni)->number << " Prev: nullptr " << "Dist: " << (*ni)->distance << endl;
        }
    }
    

    cout << "\nEdges:" << endl;
    vector<Edge*>::iterator ei;
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        cout << "Node: " << (*ei)->first->number << " to node: " << (*ei)->second->number << " Dist: " << (*ei)->weight << endl;
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
    vector<Node*>::iterator ni;
    // Inicializar valores de los nodos dist = INF y prev = UNDF
    for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
        (*ni)->distance = 1000;
        (*ni)->prev = nullptr;
        Q.push_back(*ni);
    }
    // for (int v = 0; v < nodes.size(); v++){
    //     nodes[v]->distance = 1000;
    //     nodes[v]->prev = nullptr;
    //     Q.push_back(nodes[v]);
    // }


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
        vector<Node*>::iterator ni;
        // Actualizar distancias
        for(ni = neighbors.begin(); ni != neighbors.end(); ++ni) {
            Node *v = *ni;
            int alt = u->distance + getLength(u, v);
            if (alt < v->distance) {
                v->distance = alt;
                v->prev = u;
            }
        }
        // for(int n = 0; n < neighbors.size(); n++) {
        //     Node *v = neighbors[n];
        //     int alt = u->distance + getLength(u, v);
        //     if (alt < v->distance) {
        //         v->distance = alt;
        //         v->prev = u;
        //     }
        // }
    }
}

void Graph::runFloyd() {
    vector<vector<int> > matrix;
    for (int i = 0; i < nodes.size(); i++) {
        vector<int> row(nodes.size(), 10000);
        row[i] = 0;
        matrix.push_back(row);
    }

    vector<Edge*>::iterator ei;
    for (ei = edges.begin(); ei != edges.end(); ++ei) {
        int row = (*ei)->first->number - 1;
        int column = (*ei)->second->number - 1;
        int value = (*ei)->weight;
        matrix[row][column] = value;
    }

    for (int k = 0; k < nodes.size(); k++) {
        for (int i = 0; i < nodes.size(); i++) {
            for(int j = 0; j < nodes.size(); j++) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
    
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes.size(); j++) {
            if (matrix[i][j] == 10000) {
                cout << "I" << "|";
            }
            else {
                cout << matrix[i][j] << "|";
            }
        }
        cout << endl;
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