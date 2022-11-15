//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#include "DisjointSets.hpp"
#include <iostream>

// FUNCIÓN MAKESET: Función para crear un conjunto de nodos
// Complejidad --> O(n)
void DisjointSets::makeSet(Node *n){
   vector<Node*> set;
   set.push_back(n);
   sets.push_back(set);
}

// FUNCIÓN FINDSET: Función para encontrar el conjunto de un nodo
// Complejidad --> O(n^2)
vector<Node*> DisjointSets::findSet(Node *n){
    vector<vector<Node*>>::iterator si;
    for(si = sets.begin(); si != sets.end(); ++si) {
        vector<Node*>::iterator ni;
        for(ni = (*si).begin(); ni != (*si).end(); ++ni) {
            if((*ni) == n) {
                return (*si);
            }
        }
    }
    return vector<Node*>();
}

// FUNCIÓN UNION: Función para unir dos conjuntos
// Complejidad --> O(n^2)
void DisjointSets::do_union(vector<Node*> a, vector<Node*> b){
    // UNION
    int m = max(a.size(), b.size());
    vector<Node*> vec(a.size() + b.size());

    vector<Node*>::iterator it;
    it = set_union(a.begin(), a.end(), b.begin(), b.end(), vec.begin());
    vec.resize(it - vec.begin());

    // BUSCAR PARA REEMPLAZAR
    vector<vector<Node*>>::iterator si;
    for (si = sets.begin() ; si != sets.end() ; ++si){
        vector<Node*> set = *si;
        vector<Node*>::iterator ni;

        for (ni = set.begin() ; ni != set.end() ; ++ni){
            if ((*ni) == a[0]) (*si) = vec;
            if ((*ni) == b[0]) (*si).clear();
        }
    }
}