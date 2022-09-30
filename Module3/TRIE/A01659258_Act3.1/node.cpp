//  Actividad 3.1 - Implementación de "Tries"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 26/09/2022
//  node.cpp

#include "Node.h"

// Complejidad: O(1)
Node::Node(){
  isActive = false;
}

// Complejidad: O(n)
void Node::createNode(){
  isActive = true;
  for (int i = 0; i < 26; i++){
    children.push_back(new Node());
  }
}

// Complejidad: O(1)
bool Node::isNodeActive(){
  return isActive;
}

// Complejidad: O(n)
string Node::toString(){
  string s = "";

  for(int i = 0; i < children.size(); i++){
    if (children[i]->isActive){
      s += char(i + 'a');
      s += "|";
    }
      s += children[i]->toString();
  }

  return s;
}