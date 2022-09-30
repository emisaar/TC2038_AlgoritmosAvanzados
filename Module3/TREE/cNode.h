// NODE 
//     - - - PAYLOAD (Data types)
//     - - - CONNECTIONS 
#include <iostream>
#include <vector>
using namespace std;

#ifndef __NODE
#define __NODE

class Node{
    public:
        Node(char c);
        vector<Node*> connections; // Nodo tiene conexión con otros nodos 
        char getPayload();
        string toString();

    private:
        char payload;
};
#endif