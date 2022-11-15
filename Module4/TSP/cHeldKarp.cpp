#include "cHeldKarp.h"

HeldKarp::HeldKarp(Graph *_g){
    g = _g;
}

vector<Node*> HeldKarp::findHamilton(Node *start){
    vector<Node*>::iterator ni;
    for(ni = g.nodes.begin(); ni != g.nodes.end(); ni++){
        if(*ni != start){
            vector<int> set;
            // set.push_back((*ni)->id);
            FunctionP *p = new FunctionP(start->number, set);
            prevResults.push_back(p);
        }
    }
}