//  Actividad 3.1 - Implementación de "Tries"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 26/09/2022
//  Trie.h

#pragma once
#include <iostream>
#include <vector>

#include "Node.h"

using namespace std;

#ifndef __TRIE
#define __TRIE

class Trie : public Node {
    private:
        Node *root;
       
    public:
        Trie();
        Trie(Node *n);
        void Add(string word);
        void Print();
        bool Query(string key);
        
};

#endif