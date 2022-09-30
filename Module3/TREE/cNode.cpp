#include "cNode.h"

Node::Node(char c){
    payload = c;
}

char Node::getPayload(){
    return payload;
}

string Node::toString(){
    // string s = "N: ";
    string s;
    s += payload;
    // s += " C: ";
    // for(int c = 0; c < connections.size(); c++){
    //     s += connections[c]->toString() + " ";
    // }
    for(int c = 0; c < connections.size(); c++){
        s += connections[c]->toString();
    }
    return s;
}