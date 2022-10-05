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
        // else if ((*ei)->second == n) {
        //     neighbors.push_back((*ei)->first);
        // }
    }
    return neighbors;
}

/*
print() -> Complejidad: O(n+n) ?
Itera sobre los vectores nodes y edges para acceder e 
imprimir los atributos de los nodos y aristas.
*/
void Graph::printDijkstra(){
    vector<Node*>::iterator ni;
        for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
            if((*ni)->prev != nullptr || (*ni)->distance != 0) {
                cout << "Node: " << _source->number << " to node " << (*ni)->number << " Dist: " << (*ni)->distance << endl;
            }
        }
}

void Graph::printFloyd(vector<vector<int> > matrix){
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes.size(); j++) {
                cout << matrix[i][j] << "|";
        }
        cout << endl;
    }
}

/*
runDijkstra(Node *source) -> Complejidad: O((|V| + |E|)log(|V|))
Recibe:
    - Nodo de origen o inicio.
Lleva a cabo lógica del algoritmo.
*/
void Graph::runDijkstra(Node *source) {
    _source = source;
    // Crear vector de nodos Q
    vector<Node*> Q;
    vector<Node*>::iterator ni;
    // Inicializar valores de los nodos dist = INF y prev = UNDF
    for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
        // (*ni)->distance = 1000;
        // (*ni)->prev = nullptr;
        Q.push_back(*ni);
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
        for(ni = neighbors.begin(); ni != neighbors.end(); ++ni) {
            Node *v = *ni;
            int alt = u->distance + getLength(u, v);
            if (alt < v->distance) {
                v->distance = alt;
                v->prev = u;
            }
        }
    }
}

/*
runFloyd() -> Complejidad: O(|V|^3)
*/
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

    printFloyd(matrix);
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
    vector<Node*>::iterator ni;

    for (ni = qs.begin(); ni != qs.end(); ++ni) {
        if ((*ni)->distance < min->distance) {
            min = *ni;
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
    vector<Node*>::iterator ni;
    for (ni = qs.begin(); ni != qs.end(); ++ni) {
        if (*ni == q) {
            qs.erase(ni);
            break;
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
    vector<Edge*>::iterator ei;
    for (ei = edges.begin(); ei != edges.end(); ++ei) {
        if ((*ei)->first == u && (*ei)->second == v) {
            return (*ei)->weight;
        } 
        // else if ((*ei)->first == v && (*ei)->second == u) {
        //     return (*ei)->weight;
        // }
    }

    return 0;
}