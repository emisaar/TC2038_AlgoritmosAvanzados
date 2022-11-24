//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#include "cFunctionG.hpp"

// CONSTRUCTOR FUNCTIONG
// Complejidad: O(n)
FunctionG::FunctionG(int _exit_val, vector<int> _set) {
    // Copiar set
    vector<int>::iterator it;
    for (it = _set.begin(); it != _set.end(); ++it){
        set.push_back(*it);
    }
    exit_val = _exit_val;
    result = 0;
}

// FUNCIÓN TO STRING: PARA IMPRIMIR LA FUNCIÓN
// Complejidad: O(n)
string FunctionG::toString() {
    string s = "G(" + to_string(exit_val) + ", {";
    vector<int>::iterator it;
    for (it = set.begin(); it != set.end(); ++it){
        s += to_string(*it) + ", ";
    }
    s += "}) = " + to_string(result);
    return s;
}