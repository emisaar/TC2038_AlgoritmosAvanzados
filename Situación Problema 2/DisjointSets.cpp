//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 07/11/2022

#include "DisjointSets.hpp"
#include <iostream>

void DisjointSets::makeSet(Node *u){
    vector<Node*> set;
    set.push_back(u);
    sets.push_back(set);
}

vector<Node*> DisjointSets::findSet(Node *u){
    vector<vector<Node*>>::iterator si;
    for (si = sets.begin() ; si != sets.end() ; ++si){
        vector<Node*> set = *si;

        vector<Node*>::iterator it;
        for (it = set.begin() ; it != set.end() ; ++it){
            if ((*it) == u){
                return set;
            }
        }
    }

    vector<Node*> empty_set;
    return empty_set;

}

void DisjointSets::do_union(vector<Node *> a, vector<Node *> b){
    // UNION
    int m = max(a.size(), b.size());
    vector<Node*> vec(a.size() + b.size());

    vector<Node*>::iterator it;
    it = set_union(a.begin(), a.end(), b.begin(), b.end(), vec.begin());
    vec.resize(it - vec.begin());

    // BUSCCAR PARA REMPLAZO
    vector<vector<Node*>>::iterator si;
    for (si = sets.begin() ; si != sets.end() ; ++si){
        vector<Node*> set = *si;
        vector<Node*>::iterator ni;
        for (ni = set.begin() ; ni != set.end() ; ++ni){
            if ((*ni) == a[0])
                (*si) = vec;
            if ((*ni) == b[0])
                (*si).clear();
        }
    }
}

string DisjointSets::toString(){
    string txt = "";
    vector<vector<Node*>>::iterator setsI;
    vector<Node*>::iterator setI;
    
    for (setsI = sets.begin(); setsI != sets.end(); ++setsI){
        txt += "{";
        vector<Node*> set = *setsI;
        for (setI = set.begin(); setI != set.end(); ++setI){
            Node* n = *setI;
            txt += to_string(n->number) + " ";
        }
        txt += "}\n";
    }
    return txt;
}
