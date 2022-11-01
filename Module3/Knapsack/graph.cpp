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

#include "Graph.h"
#include <queue>

/*
Constructor de Graph (Grafo)
Recibe como parámetro:
    - Vector de nodos (_nodes)
    - Vector de artistas (_edges)
*/
Graph::Graph(vector<Node*> _nodes, vector<Edge*> _edges){
    nodes = _nodes;
    edges = _edges;
}

/*
Método getNeighbors -> Complejidad: O(n)
Recibe:
    - Un nodo (n) al que se le desea encontrar sus vecinos.
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
Método printDijkstra -> Complejidad: O(n)
Itera sobre los vectores nodes y edges para acceder e 
imprimir los atributos de los nodos y aristas.
*/
void Graph::printDijkstra(){
    vector<Node*>::iterator ni;
        for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
            if((*ni)->prev != nullptr || (*ni)->distance != 0) {
                cout << "Node: " << s->number << " to node " << (*ni)->number << " Dist: " << (*ni)->distance << endl;
            }
        }
}

/*
Método printFloyd() -> Complejidad O(n^2)
Recibe:
    - Una matriz (matrix)
Recorre la matriz para imprimir los elementos de la misma en consola.
*/

void Graph::printFloyd(vector<vector<int> > matrix){
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes.size(); j++) {
                cout << matrix[i][j] << "|";
        }
        cout << endl;
    }
}

/*
Método runDijkstra -> Complejidad: O((|V| + |E|)log(|V|))
    Donde:
        |V| -> número de nodos
        |E| -> número de aristas
Recibe:
    - Nodo de origen (source).
Lleva a cabo lógica del algoritmo.
*/
void Graph::runDijkstra(Node *source) {
    // Al ejecutar Dijkstra, guardamos el Nodo inicial para ejecutar el print.
    s = source;
    // Vector de nodos Q
    vector<Node*> Q;
    // Iterador de nodos
    vector<Node*>::iterator ni;
    // Guardamos los nodos del grafo en el vector Q
    for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
        // (*ni)->distance = 1000;
        // (*ni)->prev = nullptr;
        Q.push_back(*ni);
    }


    // Actualizar distancia a 0 para nodo inicial 
    source->distance = 0;

    // Mientras Q no esté vacía...
    while (!Q.empty()) {
        // Buscar nodo con la distancia más corta (u)
        Node *u = getMinDist(Q);
        // Eliminar nodo con menor distancia (u) del vector Q
        remove(Q, u);
        // Crear vector con los nodos vecinos al Nodo u
        vector<Node*> neighbors = getNeighbors(u);

        // Itera sobre los vecinos del Nodo u
        for(ni = neighbors.begin(); ni != neighbors.end(); ++ni) {
            // Para cada Nodo v del vector neighbors
            Node *v = *ni;
            // Alt corresponde a la suma de la distancia del Nodo u y la distancia entre el Nodo u y Nodo v
            int alt = u->distance + getLength(u, v);
            // Si hay algún camino más pequeño a v a través de u
            if (alt < v->distance) {
                // Actualiza distancia de v
                v->distance = alt;
                // Actualizar apuntador prev del Nodo v al Nodo u
                v->prev = u;
            }
        }
    }
}

/*
Método runFloyd -> Complejidad: O(|V|^3)
    Donde:
        |V| -< número de nodos
Lleva a cabo lógica del algoritmo.
*/
void Graph::runFloyd() {
    // Crear matriz
    vector<vector<int> > matrix;
    for (int i = 0; i < nodes.size(); i++) {
        // Crear vector fila (row) de tamaño del vector de nodos (nodes.size()), donde cada elemento tiene un valor de 10000
        vector<int> row(nodes.size(), 10000);
        // Diagonal de la matriz en 0s
        row[i] = 0;
        // Añadir a matriz
        matrix.push_back(row);
    }

    // Iteración sobre aristas
    vector<Edge*>::iterator ei;
    for (ei = edges.begin(); ei != edges.end(); ++ei) {
        // Obtener indexes row y column para la matriz
        int row = (*ei)->first->number - 1;
        int column = (*ei)->second->number - 1;
        // Obtener peso de la arista
        int value = (*ei)->weight;
        // Asignar peso en la posición de la matriz
        matrix[row][column] = value;
    }

    // k es el vértice intermedio en el camino más corto desde el origen hasta el destino
    // i, j iteradores para recorrer matriz
    for (int k = 0; k < nodes.size(); k++) {
        for (int i = 0; i < nodes.size(); i++) {
            for(int j = 0; j < nodes.size(); j++) {
                // Actualizar la distancia menor 
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }

    printFloyd(matrix);
}

/*
Método getMinDist -> Complejidad: O(n)
Recibe:
    - Un vector de nodos (qs)
Regresa el nodo con la menor distancia.
Compara las distancias de los nodos del vector, guardando 
el nodo con la distancia más corta.
*/
Node * Graph::getMinDist(vector<Node*> qs) {
    Node *min = qs[0];
    vector<Node*>::iterator ni;
    
    // Recorrer el vector de nodos (qs)
    for (ni = qs.begin(); ni != qs.end(); ++ni) {
        // Si la distancia del nodo actual es menor a la distancia más corta encontrada anteriormente, actualiza min al Nodo actual.
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
    
    // Recorrer el vector de nodos (qs)
    for (ni = qs.begin(); ni != qs.end(); ++ni) {
        // Si encuentra el nodo q en el vector qs, elimina nodo del vector
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

    // Recorrer el vector de aristas (edges)
    for (ei = edges.begin(); ei != edges.end(); ++ei) {
        // Si el nodo first es igual al nodo u y el nodo second es igual al nodo v, regresa el peso de esa arista
        if ((*ei)->first == u && (*ei)->second == v) {
            return (*ei)->weight;
        } 
        // else if ((*ei)->first == v && (*ei)->second == u) {
        //     return (*ei)->weight;
        // }
    }

    return 0;
}

/*
runFordFulkerson -> Complejidad: O(n^3 * m)
*/

int Graph::runFordFulkerson(Node *s, Node *t) {
    int maxFlow = 0;
    // Iterar sobre el vector de aristas
    for (Edge* e : edges) {
        // Actualizar el flujo (flow) de cada arco con el valor de capacidad (weight) del mismo
        e->flow = e->weight;
        // Mientras haya un camino desde el nodo s al nodo t
        while(bfs(s, t)) {
            int pathFlow = INT_MAX;
            // Nodo temporal para recorrer el path
            Node *curr = t;
            while (curr != s) {
                // Obtener la arista que conecta el nodo previo con el nodo actual
                Edge *e = findEdge(curr->prev, curr);
                // Encontrar el flujo mínimo
                pathFlow = min(pathFlow, e->flow);
                // Actualizar el nodo actual
                curr = curr->prev;
            }
            // Se realiza el camino inverso para actualizar los flujos
            curr = t;
            // Mientras el nodo actual no sea el nodo s
            while(curr != s) {
                // Buscar arista que conecta el nodo previo con el nodo actual para actualizar el flujo
                Edge *e1 = findEdge(curr->prev, curr);
                e1->flow -= pathFlow;

                // Buscar arista que conecta el nodo actual con el nodo previo para actualizar el flujo
                Edge *e2 = findEdge(curr, curr->prev);
                if (e2 != nullptr) e2->flow += pathFlow;
                curr = curr->prev;
            }
            // Actualizar el flujo máximo
            maxFlow += pathFlow;
        }
    }
    return maxFlow;
}

void Graph::findPaths(Node *s, Node *t, vector<int> &weights, vector<int> &values) {
    int pathFlow = INT_MAX;
    vector<Edge*>::iterator ei;
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        (*ei)->flow = (*ei)->weight;
    }
    while(bfs(s, t)) {
        int pathTotalWeight = 0;
        int pathTotalValue = 0;
        Node *curr = t;
        while (curr != s) {
           if(curr != t) pathTotalValue += curr->number;
            Edge *e1 = findEdge(curr->prev, curr);
            pathTotalWeight += e1->weight;
            pathFlow = min(pathFlow, e1->flow);
            curr = curr->prev;
        }

        pathTotalValue += curr->number;
        weights.push_back(pathTotalWeight);
        values.push_back(pathTotalValue);
        curr = t;
        while(curr != s) {
            Edge *e1 = findEdge(curr->prev, curr);
            e1->flow -= pathFlow;
            Edge *e2 = findEdge(curr, curr->prev);
            if (e2 != nullptr) e2->flow += pathFlow;
            curr = curr->prev;
        }
    }
}

/*
findEdge -> Complejidad: O(n)
*/
Edge *Graph::findEdge(Node *u, Node *v) {
    // Recorrer el vector de aristas (edges) para encontrar el arco entre nodos u y v
    Edge *e = nullptr;
    for (Edge* e : edges) {
        if (e->first == u && e->second == v) {
            return e;
        }
    }
    return e;
}


/*
bfs -> Complejidad: O(n^2)
*/
bool Graph::bfs(Node *s, Node *t) {
   // Inicializar nodos como no visitados
    for (Node* n : nodes) {
        n->visited = false;
    }

    // Crear vector de nodos
    vector<Node*> q;
    // Agregar nodo source (s) al vector
    q.push_back(s);
    // Marcar nodo source (s) como visitado
    s->prev = nullptr;
    s->visited = true;

    // Mientras el vector de nodos no esté vacío
    while(q.size() > 0) {
        // Obtener primer elemento del vector
        Node *u = q[0];
        // Eliminar primer elemento del vector
        remove(q, u);
        // Iterar sobre el vector de los vecinos de u
       for (Node* v : getNeighbors(u)) {
        // Buscar el arco entre nodo u y vecino v
           Edge *e = findEdge(u, v);
           // Si el arco existe y no ha sido visitado
           if(e != nullptr){
               if(!v->visited && e->flow > 0) {
                    // Meter vecino v al vector de nodos
                   q.push_back(v);
                   // Actualizar previo
                   v->prev = u;
                   // Actualizar nodo visitado
                   v->visited = true;
               }
           }
       }
    }
    // Regresar si el nodo sink (t) ha sido visitado
    return t->visited == true;
}