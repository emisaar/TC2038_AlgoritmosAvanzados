#pragma once
#include "cGraph.h"
#include "cFunctionP.h"
using namespace std;

class HeldKarp{
    vector<FunctionG*> prevResults;
    cGraph *g;

    HeldKarp(cGraph *_g);
    vector<Node*> findHamilton(Node *start);
}