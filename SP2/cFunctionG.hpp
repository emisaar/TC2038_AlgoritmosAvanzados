//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#pragma once
#include <iostream>
#include <vector>
using namespace std;

class FunctionG {
    public:
        vector<int> set; // conjunto que va a la derecha en p
        int exit_val;    // número que va a la izquierda en p
        int result;
        
        // Constructor
        FunctionG(int exit_val, vector<int> set);

        string toString();
};