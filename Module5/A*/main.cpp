//  Actividad 5.5 Implementación A*
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 28/11/2022

#include <iostream>
#include "Graph.hpp"
#include <vector>
#include <algorithm>
#include "math.h"

using namespace std;

void constructStringPath(vector<Node*> &path);
vector<Node*> nodes, nodes2;

vector<vector<int> > createMatrix(int n) {
    vector<vector<int> > matrix;
    for (int i = 0; i < n; i++) {
        vector<int> row;
        for (int j = 0; j < n; j++) {
            Node *node = new Node(j);
            string value;
            cin >> value;
            row.push_back(stoi(value));
            node->x = i;
            node->y = j;
            nodes.push_back(node);
        }
        matrix.push_back(row);
    }
    return matrix;
}

int main() {
    cout << "INPUT: ";
    int n;
    cin >> n;
    vector<vector<int> > matrix = createMatrix(n);

    cout << endl;
    cout << "====== AStar ======" << endl;
    Graph *g = new Graph(nodes, matrix);
    vector<Node*> AStar = g->runAStar(nodes[0], nodes[nodes.size() - 1]);
    cout << endl;
    if (AStar.size() == 0) {
        cout << "\tTHERE IS NO EXISTING PATH!!!" << endl << endl;
    } else {
        cout << "\tCOORDENATES TO ARRIVE TO OUR DESTINATION: ";
        for (int i = 0; i < AStar.size(); i++) {
            cout << "(" << AStar[i]->x << ", " << AStar[i]->y << ") ";
        }
        reverse(AStar.begin(), AStar.end());
        constructStringPath(AStar);
        cout << endl << endl;
    }
}

// Función para imprimir las direcciones a seguir para llegar de start a end
// Compeljidad -> O(n)
// Construct Path
// Complejidad: O(n + m)
void constructStringPath(vector<Node*> &path) {
    vector<string> stringPath;
    Node *currPos = new Node(100), *nextPos = new Node(101);
    currPos->x = path.back()->x;
    currPos->y = path.back()->y;
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
    
    cout << "\n\tDIRECTIONS TO ARRIVE TO OUR DESTINATION: ";
    for (int i = 0; i < stringPath.size(); i++) {
        if (i == stringPath.size() - 1) {
            cout << stringPath[i];
        } else {
            cout << stringPath[i] << ", ";
        }
    }
}

/*
4
1 0 0 0
1 1 0 1
1 1 0 0
0 1 1 1
*/

/*

4
1, 0, 0, 0
1, 1, 0, 1
1, 1, 0, 0
0, 1, 1, 1


4
1, 0, 0, 0
1, 1, 0, 1
0, 0, 0, 0
0, 1, 1, 1
*/

/*
10
1 1 1 1 1 0 0 0 0 0
0 0 1 0 1 0 0 0 0 0
0 0 1 0 1 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 0 1 1 1 1 0 0
0 0 0 0 1 0 0 1 0 0
0 0 0 0 1 1 1 1 1 0
0 0 0 0 1 0 0 0 1 0
0 0 0 0 0 0 0 0 1 1
*/

/*
 INPUT:
 4
 1, 0, 0, 0
 1, 1, 0, 1
 1, 1, 0, 0
 0, 1, 1, 1
 
 OUTPUT:
 DR, D, DR, R
 */


/*
 INPUT:
 4
 1, 0, 0, 0
 0, 1, 0, 1
 1, 0, 0, 0
 0, 1, 1, 1
 
 OUTPUT:
 DR, DL, DR, R, R
 */


/*
 INPUT:
 4
 1, 0, 0, 0
 0, 0, 0, 1
 1, 0, 0, 0
 0, 1, 1, 1
 
 OUTPUT:
 THERE IS NO EXISTING PATH!!!
 */


/*
 INPUT:
 4
 1, 0, 0, 0
 1, 0, 0, 1
 0, 0, 1, 0
 0, 0, 0, 0
 
 OUTPUT:
 THERE IS NO EXISTING PATH!!!
 */

