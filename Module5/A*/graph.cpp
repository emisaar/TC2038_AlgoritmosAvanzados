//  Actividad 5.5 Implementación A*
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 28/11/2022

#include "Graph.h"
#include "math.h"

// Constructor
// Complejidad: O(n^2)
Graph::Graph(vector<Node*> _nodes, vector<vector<int> > _matrix){
    nodes = _nodes;
    matrix = _matrix;
}

// RunAStar Method
// Complejidad: O(n^2)
vector<Node*> Graph::runAStar(Node *source, Node *goal) {
    vector<Node*> openList; // Holds potential best path nodes that have not yet been visited, starting with the source node
    vector<Node*> closedList; // Starts empty, holds nodes that have already been visited
    openList.push_back(source); // Add source node to openList

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
        Node *current = getMinF(openList); // Get node with lowest f value
        // cout << "Previous: " << endl;
        // cout << current->parent << endl;
        if (current == goal) {
            // cout << "Previous: " << endl;
            // cout << current->parent << endl;
            return constructPath(current);
        }
        remove(openList, current); // Remove current from openList
        closedList.push_back(current); // Add current to closedList
        getNodeNeighbors(current); // Get neighbors of current
        vector<Node*> currNeighbors = current->neighbors; // Get neighbors of current

        vector<Node*>::iterator ni;
        for(ni = currNeighbors.begin(); ni != currNeighbors.end(); ++ni) { // For each neighbor of current    
            Node *neighbor = *ni;
            if (find(closedList.begin(), closedList.end(), neighbor) == closedList.end()) { // if neighbor is not in closedList
                neighbor->f = neighbor->g + heuristic(neighbor, goal); 
                if (find(openList.begin(), openList.end(), neighbor) == openList.end()) { // if neighbor is not in openList
                    neighbor->parent = current; // Set current as neighbor's parent
                    openList.push_back(neighbor); // Add neighbor to openList
                } else {
                    Node* openNeighbor = *find(openList.begin(), openList.end(), neighbor); // Get neighbor from openList
                    if (neighbor->g < openNeighbor->g) {
                        openNeighbor->parent = current; // Set neighbor's parent to current    
                        openNeighbor->g = neighbor->g;
                    }
                }
            }
        }
        i++;
    }
    return vector<Node*>(); // If openList is empty, there's no path
}

// Heuristic
// Complejidad: O(1)
float Graph::heuristic(Node *a, Node *b) {
    // cout << "Heuristic: " << sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2)) << endl;
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

// Find Node
// Complejidad: O(n)
Node* Graph::findNode(int x, int y) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->x == x && nodes[i]->y == y) {
            // cout << "Node found: " << nodes[i]->number << ": (" <<  nodes[i]->x << ", " << nodes[i]->y << ")" << endl;
            return nodes[i];
        }
    }
    return NULL;
}

// IsSafe
// Complejidad: O(1)
bool Graph::isSafe(int x, int y, int rows, int columns) { // checking the boundry
    return (x >= 0 && x < rows && y >= 0 && y < columns);
}

// GetNodeNeighbors method
// Considers 8-way movement
// Complejidad: O(n)
void Graph::getNodeNeighbors(Node *n) {
    int rows = matrix.size();
    int columns = matrix[0].size();
    float dCost;                   
    int count = 0;
    if (matrix[n->x][n->y] == 1) { // if the current node is not a wall
        if(isSafe(n->x - 1, n->y, rows, columns)) { // up
            if(matrix[n->x - 1][n->y] == 1) {
                count ++;
                Node *node = findNode(n->x - 1, n->y);

                dCost = sqrt(pow(n->x - node->x, 2) + pow(n->y - node->y, 2));
                node->g = n->g + dCost;
                
                n->neighbors.push_back(node);
                // n->neighbors[n->neighbors.size() - 1]->direction = "L";
            }
        }

        if(isSafe(n->x - 1, n->y - 1, rows, columns)) { // left-up
            if(matrix[n->x - 1][n->y - 1] == 1) {
                count ++;
                Node *node = findNode(n->x - 1, n->y - 1);

                dCost = sqrt(pow(n->x - node->x, 2) + pow(n->y - node->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
            }
        }

        if(isSafe(n->x, n->y - 1, rows, columns)) { // left
            if(matrix[n->x][n->y - 1] == 1) {
                count ++;
                Node *node = findNode(n->x, n->y - 1);

                dCost = sqrt(pow(n->x - node->x, 2) + pow(n->y - node->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
            }
        }

        if(isSafe(n->x + 1, n->y - 1, rows, columns)) { // left-down
            if(matrix[n->x + 1][n->y - 1] == 1) {
                count ++;
                Node* node = findNode(n->x + 1, n->y - 1);

                dCost = sqrt(pow(n->x - node->x, 2) + pow(n->y - node->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
            }
        }

        if(isSafe(n->x + 1, n->y, rows, columns)) { // down
            if(matrix[n->x + 1][n->y] == 1) {
                count ++;
                Node *node = findNode(n->x + 1, n->y);

                dCost = sqrt(pow(n->x - node->x, 2) + pow(n->y - node->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
            }
        } 

        if(isSafe(n->x + 1, n->y + 1, rows, columns)) { // right-down
            if(matrix[n->x + 1][n->y + 1] == 1) {
                count ++;
                Node *node = findNode(n->x + 1, n->y + 1);

                dCost = sqrt(pow(n->x - node->x, 2) + pow(n->y - node->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
            }
        }

        if(isSafe(n->x, n->y + 1, rows, columns)) { // right
            if(matrix[n->x][n->y + 1] == 1) {
                count ++;
                Node *node = findNode(n->x, n->y + 1);

                dCost = sqrt(pow(n->x - node->x, 2) + pow(n->y - node->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
            }
        }

        if(isSafe(n->x - 1, n->y + 1, rows, columns)) { // left-down
            if(matrix[n->x - 1][n->y + 1] == 1) {
                count ++;
                Node *node = findNode(n->x - 1, n->y + 1);
                
                dCost = sqrt(pow(node->x - n->x, 2) + pow(node->y - n->y, 2));
                node->g = n->g + dCost;

                n->neighbors.push_back(node);
            }
        }
    }
}

// Construct Path
// Complejidad: O(n)
void Graph::constructStringPath(vector<Node*> &path) {
    vector<string> stringPath;
    Node *currPos, *nextPos;
    currPos->x = path[path.size() - 1]->x;
    currPos->y = path[path.size() - 1]->y;
    path.pop_back();
   
    while(!path.empty()) {
        nextPos->x = path[path.size() - 1]->x;
        nextPos->y = path[path.size() - 1]->y;
        path.pop_back();

        if(currPos->x == nextPos->x && currPos->y == nextPos->y + 1) {
            stringPath.push_back("L");
        } else if(currPos->x == nextPos->x && currPos->y == nextPos->y - 1) {
            stringPath.push_back("R");
        } else if(currPos->x == nextPos->x + 1 && currPos->y == nextPos->y) {
            stringPath.push_back("U");
        } else if(currPos->x == nextPos->x - 1 && currPos->y == nextPos->y) {
            stringPath.push_back("D");
        } else if(currPos->x == nextPos->x + 1 && currPos->y == nextPos->y + 1) {
            stringPath.push_back("UL");
        } else if(currPos->x == nextPos->x + 1 && currPos->y == nextPos->y - 1) {
            stringPath.push_back("UR");
        } else if(currPos->x == nextPos->x - 1 && currPos->y == nextPos->y + 1) {
            stringPath.push_back("DL");
        } else if(currPos->x == nextPos->x - 1 && currPos->y == nextPos->y - 1) {
            stringPath.push_back("DR");
        }

        currPos->x = nextPos->x;
        currPos->y = nextPos->y;
    }
    
    cout << "\tString Path: ";
    for (int i = 0; i < stringPath.size(); i++) {
        if (i == stringPath.size() - 1) {
            cout << stringPath[i];
        } else {
            cout << stringPath[i] << ", ";
        }
    }
}

// Construct Path
// Complejidad: O(n)
vector<Node*> Graph::constructPath(Node *node) {
    vector<Node*> path, pathCopy;
    path.push_back(node);
    pathCopy.push_back(node);
    while (node->parent != nullptr) {
        node = node->parent;
        path.push_back(node);
        pathCopy.push_back(node);
    }

    constructStringPath(path);

    reverse(pathCopy.begin(), pathCopy.end());

    return pathCopy;
}

// GetMinF
// Complejidad: O(n)
Node * Graph::getMinF(vector<Node*> qs) {
    // Iterador de nodos
    vector<Node*>::iterator ni;
    // Nodo con menor F
    Node *minF = qs[0];
    for (ni = qs.begin(); ni != qs.end(); ++ni) {
        if ((*ni)->f < minF->f) {
            minF = *ni;
        }
    }
    return minF;
}




// Remove
// Complejidad: O(n)
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