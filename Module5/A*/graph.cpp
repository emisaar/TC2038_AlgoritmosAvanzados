//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  graph.cpp

#include "Graph.h"
#include "math.h"
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

Graph::Graph(vector<Node*> _nodes){
    nodes = _nodes;
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

vector<Node*> Graph::runAStar(Node *source, Node *goal) {
    vector<Node*> openList; // Holds potential best path nodes that have not yet been visited, starting with the source node
    vector<Node*> closedList; // Starts empty, holds nodes that have already been visited
    openList = nodes;

    source->g = 0;
    source->f = source->g + heuristic(source, goal);
    /*
    Core loop: Selects node from openList with lowest f value.
    If it is the goal node, we are done. Otherwise, move it to the closedList
    and add its neighbors to the openList.
    Nodes create a reference to their parent node
    */
   int i = 0;
    while (!openList.empty()) {
        cout << "Open List (" << i << "): ";
        vector<Node*>::iterator oi;
        for(oi = openList.begin(); oi != openList.end(); ++oi) {
            cout << (*oi)->number << " ";
        }
        cout << endl;

        cout << "Closed List: ";
        for(oi = closedList.begin(); oi != closedList.end(); ++oi) {
            cout << (*oi)->number << " ";
        }
        cout << endl;

        Node *current = getMinF(openList); // Get node with lowest f value
        if (current == goal) {
            return constructPath(goal);
        }
        remove(openList, current); // Remove current from openList
        closedList.push_back(current); // Add current to closedList
        vector<Node*> neighbors = Graph::neighbors(current); // Get neighbors of current
        cout << "Neighbors: ";
        cout << "Node " << current->number << ": (" <<  current->x << ", " << current->y << ") " << endl;
        for(oi = neighbors.begin(); oi != neighbors.end(); ++oi) {
            cout << "Node " << (*oi)->number << ": (" <<  (*oi)->x << ", " << (*oi)->y << ") " << (*oi)->parent->number <<  ": (" <<  (*oi)->x << ", " << (*oi)->y << ") " << endl;
        }
        vector<Node*>::iterator ni;
        for(ni = neighbors.begin(); ni != neighbors.end(); ++ni) { // For each neighbor in neighbors    
            Node *neighbor = *ni;
            if (find(closedList.begin(), closedList.end(), neighbor) == closedList.end()) { // if neighbor is not in closedList
                neighbor->f = neighbor->g + heuristic(neighbor, goal); 
                if (find(openList.begin(), openList.end(), neighbor) == openList.end()) { // if neighbor is not in openList
                    openList.push_back(neighbor); // Add neighbor to openList
                } else {
                    Node* openNeighbor = *find(openList.begin(), openList.end(), neighbor); // Get neighbor from openList
                    if (neighbor->g < openNeighbor->g) {
                        openNeighbor->g = neighbor->g;
                        openNeighbor->parent = neighbor->parent;
                    }
                }
            }
        }
        i++;
    }
    return vector<Node*>(); // If openList is empty, there's no path
}

float Graph::heuristic(Node *a, Node *b) {
    cout << "Heuristic: " << sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2)) << endl;
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

vector<Node*> Graph::neighbors(Node *n) {
    vector<Node*> neighbors = n->neighbors;
    vector<Node*>::iterator ni;
    for(ni = neighbors.begin(); ni != neighbors.end(); ++ni) {
        Node *neighbor = *ni;
        neighbor->g = n->g + 1;
        neighbor->parent = n;
    }
    return neighbors;
}

vector <Node*> Graph::constructPath(Node *node) {
    vector<Node*> path;
    path.push_back(node);
    while (node->parent != nullptr) {
        node = node->parent;
        path.push_back(node);
    }
    return path;
}

Node * Graph::getMinF(vector<Node*> qs) {
    // Iterador de nodos
    vector<Node*>::iterator ni;
    // Nodo con menor distancia
    Node *minF = qs[0];
    // Itera sobre los nodos del vector
    for (ni = qs.begin(); ni != qs.end(); ++ni) {
        cout << "(*ni): " << (*ni)->f << " || minF: " << minF->f << endl;
        // Si la distancia del Nodo actual es menor a la del Nodo con menor distancia
        if ((*ni)->f < minF->f) {
            // Actualiza Nodo con menor distancia
            minF = *ni;
        }
    }
    cout << "MinF: " << minF->number << endl;
    // Regresa Nodo con menor distancia
    return minF;
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