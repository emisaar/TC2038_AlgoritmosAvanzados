//  Actividad 3.1 - Implementación de "Tries"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 26/09/2022
//  Node.h

#pragma once
#include <iostream>
#include<vector>

using namespace std;

#ifndef __NODE
#define __NODE

class Node {
    private:
        bool isActive;
    public:
        vector<Node*> children;
        Node();
        void createNode();
        bool isNodeActive();
        string toString();
        
};

#endif