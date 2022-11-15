//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 07/11/2022

#ifndef DisjointSets_hpp
#define DisjointSets_hpp

#pragma once
#include <stdio.h>
#include "Node.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <vector>

using namespace std;

class DisjointSets{
    public:
        vector<vector<Node*>> sets;

        DisjointSets();
        void makeSet(Node* u);
        vector<Node*> findSet(Node* u);
        void do_union(vector<Node*> a, vector<Node*> b);
        string toString();
};

#endif /* DisjointSets_hpp */
