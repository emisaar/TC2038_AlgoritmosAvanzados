#include <iostream>
#include "cNode.h"

using namespace std;
/* 
             *
            / \
           a   b
          / \   \
          b  d   a
        / | \   / \
        a c d  d   g
*/


int main(){
    Node* root = new Node('*');

    Node* c = new Node('a');
    Node* c1 = new Node('b');

    Node* c2 = new Node('b');
    Node* c3 = new Node('d');

    Node* c4 = new Node('a');

    Node* c5 = new Node('a');
    Node* c6 = new Node('c');
    Node* c7 = new Node('d');

    Node* c8 = new Node('d');
    Node* c9 = new Node('g');

    root->connections.push_back(c);
    root->connections.push_back(c1);

    c->connections.push_back(c2);
    c->connections.push_back(c3);

    c1->connections.push_back(c4);
    
    c2->connections.push_back(c5);
    c2->connections.push_back(c6);
    c2->connections.push_back(c7);

    c4->connections.push_back(c8);
    c4->connections.push_back(c9);

    cout << root->toString() << endl;

    return 0;
}