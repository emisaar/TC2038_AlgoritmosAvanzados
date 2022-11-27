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

Graph::Graph(vector<Node*> _nodes, vector<vector<int> > _matrix){
    nodes = _nodes;
    matrix = _matrix;
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
        cout << endl;
        cout << "Open List (" << i << "): ";
        vector<Node*>::iterator oi;
        for(oi = openList.begin(); oi != openList.end(); ++oi) {
            cout << "Node " << (*oi)->number << ": (" << (*oi)->x << ", " << (*oi)->y << ") ";
            // cout << (*oi)->direction << ", ";
        }
        cout << endl;

        cout << "Closed List: ";
        for(oi = closedList.begin(); oi != closedList.end(); ++oi) {
            // cout << (*oi)->direction << ", ";
            cout << "Node " << (*oi)->number << ": (" << (*oi)->x << ", " << (*oi)->y << ") ";
        }
        cout << endl;

        Node *current = getMinF(openList); // Get node with lowest f value
        if (current == goal) {
            return constructPath(goal);
        }
        remove(openList, current); // Remove current from openList
        closedList.push_back(current); // Add current to closedList
        getNodeNeighbors(current); // Get neighbors of current
        vector<Node*> neighbors = current->neighbors; // Get neighbors of current

        cout << "Neighbors: ";
        cout << "Neighs from Node " << current->number << ": (" <<  current->x << ", " << current->y << ") " << endl;
        for(oi = neighbors.begin(); oi != neighbors.end(); ++oi) {
            cout << "Neigh " << (*oi)->number << ": (" <<  (*oi)->x << ", " << (*oi)->y << ") | Direction: " << (*oi)->direction << " isDiagonal? " << (*oi)->isDiagonal << endl;
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
                        openNeighbor->direction = neighbor->direction;
                        openNeighbor->isDiagonal = neighbor->isDiagonal;
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

Node* Graph::findNode(int x, int y) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->x == x && nodes[i]->y == y) {
            cout << "Node found: " << nodes[i]->number << ": (" <<  nodes[i]->x << ", " << nodes[i]->y << ")" << endl;
            return nodes[i];
        }
    }
    return NULL;
}

bool Graph::isSafe(int x, int y, int rows, int columns) { // checking the boundry
    return (x >= 0 && x < rows && y >= 0 && y < columns);
}

void Graph::getNodeNeighbors(Node *n) {
    int rows = matrix.size();
    int columns = matrix[0].size();
    float dCost;
    // Considering only 4 directions up, down , right, left                    
    int count = 0;
    if (matrix[n->x][n->y] == 1) { // if the current node is not a wall
        if(isSafe(n->x - 1, n->y, rows, columns)) { // up
            if(matrix[n->x - 1][n->y] == 1) {
                count ++;
                Node *node = findNode(n->x - 1, n->y);
                node->direction = "U";

                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;
                
                n->neighbors.push_back(node);
                // n->neighbors[n->neighbors.size() - 1]->direction = "L";
            }
        }

        if(isSafe(n->x - 1, n->y - 1, rows, columns)) { // left-up
            if(matrix[n->x - 1][n->y - 1] == 1) {
                count ++;
                Node *node = findNode(n->x - 1, n->y - 1);
                node->direction = "LU";
                node->isDiagonal = true;

                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
                // n->neighbors[n->neighbors.size() - 1]->isDiagonal = true;
                // n->neighbors[n->neighbors.size() - 1]->direction = "LU";
            }
        }

        if(isSafe(n->x, n->y - 1, rows, columns)) { // left
            if(matrix[n->x][n->y - 1] == 1) {
                count ++;
                Node *node = findNode(n->x, n->y - 1);
                node->direction = "L";
                // node->isDiagonal = false;

                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
                // n->neighbors[n->neighbors.size() - 1]->direction = "U";
            }
        }

        if(isSafe(n->x + 1, n->y - 1, rows, columns)) { // left-down
            if(matrix[n->x + 1][n->y - 1] == 1) {
                count ++;
                Node* node = findNode(n->x + 1, n->y - 1);
                node->direction = "LD";
                node->isDiagonal = true;

                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
                // n->neighbors[n->neighbors.size() - 1]->isDiagonal = true;
                // n->neighbors[n->neighbors.size() - 1]->direction = "RU";
            }
        }

        if(isSafe(n->x + 1, n->y, rows, columns)) { // down
            if(matrix[n->x + 1][n->y] == 1) {
                count ++;
                Node *node = findNode(n->x + 1, n->y);
                node->direction = "D";

                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
                // n->neighbors[n->neighbors.size() - 1]->direction = "R";
            }
        } 

        if(isSafe(n->x + 1, n->y + 1, rows, columns)) { // right-down
            if(matrix[n->x + 1][n->y + 1] == 1) {
                count ++;
                Node *node = findNode(n->x + 1, n->y + 1);
                node->direction = "RD";
                node->isDiagonal = true;

                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
                // n->neighbors[n->neighbors.size() - 1]->isDiagonal = true;
                // n->neighbors[n->neighbors.size() - 1]->direction = "RD";
            }
        }

        if(isSafe(n->x, n->y + 1, rows, columns)) { // right
            if(matrix[n->x][n->y + 1] == 1) {
                count ++;
                Node *node = findNode(n->x, n->y + 1);
                node->direction = "R";

                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
                // n->neighbors[n->neighbors.size() - 1]->direction = "D";
            }
        }

        if(isSafe(n->x - 1, n->y + 1, rows, columns)) { // left-down
            if(matrix[n->x - 1][n->y + 1] == 1) {
                count ++;
                Node *node = findNode(n->x - 1, n->y + 1);
                node->direction = "LD";
                node->isDiagonal = true;
                
                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
            }
        }
    }

    cout << "Node " << n->number << " has " << count << " neighbors" << endl;
    cout << "Neighbors of " << n->number << ": (" <<  n->x << ", " << n->y << ") are: \n";
    for (int i = 0; i < n->neighbors.size(); i++) {
        cout << n->neighbors[i]->number << ": (" <<  n->neighbors[i]->x << ", " << n->neighbors[i]->y << ") Direction: " << n->neighbors[i]->direction << " IsDiagonal " << n->neighbors[i]->isDiagonal << endl;
    }
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
        // cout << "(*ni): " << (*ni)->f << " || minF: " << minF->f << endl;
        // Si la distancia del Nodo actual es menor a la del Nodo con menor distancia
        if ((*ni)->f < minF->f) {
            // Actualiza Nodo con menor distancia
            minF = *ni;
        }
    }
    // cout << "MinF: " << minF->number << endl;
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
