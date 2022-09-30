//  Actividad 3.1 - Implementación de "Tries"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 26/09/2022
//  trie.cpp

#include "Trie.h"

// Complejidad: O(1)
Trie::Trie(){
  root = new Node();
  root->createNode();
}

// Complejidad: O(1)
Trie::Trie(Node *n){
  root = n;
  root->createNode();
}

// Complejidad: O(n)
void Trie::Add(string word){
  int index = 0;
  Node *curr = root;

  while(index < word.length()){
    int i = word[index] - 'a';

    if(!curr->children[i]->isNodeActive()){
      curr = curr->children[i];
      curr->createNode();
    } else {
      curr = curr->children[i];
    }

    index++;
  }
}

// Complejidad: O(1)
void Trie::Print(){
  cout << root->toString() << endl;  
}

// Complejidad: O(n)
bool Trie::Query(string key){
  int index = 0;
  Node *curr = root;
  string query = "";
  bool checkQuery = false;
  
  while(index < key.length()){
    int i = key[index] - 'a'; 

    if(curr->children[i]->isNodeActive()){
      curr = curr->children[i];
      query += char(i + 'a');

      if (query == key) {
        checkQuery = true;
        break;
      }

      index++;

    } else {
      break;
    }
  }

  return checkQuery;
}
